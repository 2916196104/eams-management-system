#include "stdafx.h"
#include "freeCoursesArrangeService.h"
#include "dao/Schedule/lesson/LessonDAO.h"
#include "dao/Schedule/lesson/LessonTeacherDAO.h"
#include "dao/Schedule/lesson/LessonStudentDAO.h"
#include "dao/Schedule/course/CourseDAO.h"
#include "dao/Schedule/class_student/ClassStudentDAO.h"
#include "SimpleDateTimeFormat.h"
#include "id/SnowFlake.h"
#include "ServerInfo.h"
#include <set>
#include <map>
#include <unordered_map>

static std::string formatTime(const std::string& time) 
{
    if (time.length() == 5 && time[2] == ':') 
    {
        return time + ":00";
    }
    return time;
}

uint64_t FreeCoursesArrangeService::saveFreeCoursesArrange(const freeCoursesArrangeDTO::Wrapper& dto)
{
    //1.前置准备
    std::string currentTime = SimpleDateTimeFormat::format();
    int64_t userId = std::stoll(dto->getPayload()->getId());
    
    //通过course_id从数据库中获取课程名称
    std::string courseName = CourseDAO().selectNameById(dto->course_id.getValue(0));
    
    //2.收集所有日期
    std::set<std::string> dateSet;
    for (auto& date : *dto->dates) 
    {
        dateSet.insert(date.getValue(""));
    }
    
    //3.检查冲突
    if (dto->check_conflict.getValue(false))
    {
        int64_t roomId = dto->classroom_id.getValue(0);
        std::string startTime = dto->start_time.getValue("");
        std::string endTime = dto->end_time.getValue("");
        
        auto conflicts = LessonDAO().checkConflictBatch(roomId, dateSet, startTime, endTime);
        
        if (!conflicts.empty())
        {
            std::string conflictMsg = ZH_WORDS_GETTER("freecourses.conflict.prefix")
                + std::to_string(conflicts.size())
                + ZH_WORDS_GETTER("freecourses.conflict.suffix")
                + ZH_WORDS_GETTER("freecourses.conflict.specific_info_tip");
            for (const auto& c : conflicts)
            {
                conflictMsg += "    " + c.title + ": " + c.date + " " + c.startTime + "-" + c.endTime;
            }
            throw std::runtime_error(conflictMsg);
        }
    }
    
    //检查限制人数
    if (dto->limit_person_num && !dto->limit_person_num->empty())
    {
        int limitPersonNum = std::stoi(dto->limit_person_num.getValue(""));
        if (limitPersonNum > 0)
        {
            int studentCount = ClassStudentDAO().getStudentCountByClassId(dto->class_id.getValue(0));
            if (studentCount > limitPersonNum)
            {
                throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.student_count_exceed_limit"));
            }
        }
    }
    
    //查询班级中该课程的最大节次
    int maxSn = LessonDAO().getMaxSnByClassIdAndCourseId(dto->class_id.getValue(0), dto->course_id.getValue(0));
    
    //4.组装课程列表
    std::list<LessonDO> lessonList;
    int decCount = dto->dec_class_time.getValue(1);
    int currentSn = maxSn;
    
    for (const auto& date : dateSet) 
    {
        LessonDO& lessonData = lessonList.emplace_back();
        
        //使用宏定义转换DTO字段到DO
        ZO_STAR_DOMAIN_DTO_TO_DO(lessonData, dto, 
            ClassId, class_id, 
            CourseId, course_id,
            RoomId, classroom_id
        );
        
        lessonData.setTitle(courseName);
        lessonData.setDate(date);
        lessonData.setStartTime(formatTime(dto->start_time.getValue("")));
        lessonData.setEndTime(formatTime(dto->end_time.getValue("")));
        lessonData.setDecCount(decCount);
        lessonData.setTeacherId(std::stoll(dto->teacher_id.getValue("")));
        lessonData.setBookable(dto->open_appointment.getValue(false) ? 1 : 0);
        
        currentSn++;
        lessonData.setSn(currentSn);
        lessonData.setCreator(userId);
        lessonData.setAddTime(currentTime);
        lessonData.setDeleted(0);
        lessonData.setTeachType(1);
        lessonData.setOnTrial(0);
        lessonData.setState(0);
    }
    
    //如果经过排课后仍然没有数据不进行插入
    if (lessonList.empty())
    {
        throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.no_lessons"));
    }
    
    //5.逐条插入课程并使用雪花算法生成ID,并建立课程id与消课课时的映射
    LessonDAO lessonDao;
    SnowFlake snowflake(ServerInfo::getInstance().getDatacenterId(), ServerInfo::getInstance().getMachineId());
    std::unordered_map<uint64_t, int> lessonDecCountMap;
    int lessonRows = 0;
    
    for (auto& lesson : lessonList) 
    {
        uint64_t lessonId = snowflake.nextId();
        if (lessonId == 0) {
            throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.id_generate_failed"));
        }
        lesson.setId(lessonId);
        int rows = lessonDao.insert(lesson);
        if (rows > 0) 
        {
            lessonDecCountMap[lessonId] = decCount;
            lessonRows++;
        }
    }
    
    if (lessonRows <= 0) return 0;
    
    //6.插入教师关联表
    LessonTeacherDAO teacherDao;
    
    for (const auto& kv : lessonDecCountMap) 
    {
        uint64_t lessonId = kv.first;
        if (dto->teacher_id && !dto->teacher_id->empty()) 
        {
            uint64_t teacherId = snowflake.nextId();
            if (teacherId == 0) {
                throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.id_generate_failed"));
            }
            LessonTeacherDO teacherData;
            teacherData.setId(teacherId);
            teacherData.setLessonId(static_cast<int64_t>(lessonId));
            teacherData.setTeacherId(std::stoll(dto->teacher_id.getValue("")));
            teacherData.setTypeNum(1);
            teacherDao.insert(teacherData);
        }
        
        if (dto->assistant_id && !dto->assistant_id->empty()) 
        {
            uint64_t assistantId = snowflake.nextId();
            if (assistantId == 0) {
                throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.id_generate_failed"));
            }
            LessonTeacherDO assistantData;
            assistantData.setId(assistantId);
            assistantData.setLessonId(static_cast<int64_t>(lessonId));
            assistantData.setTeacherId(std::stoll(dto->assistant_id.getValue("")));
            assistantData.setTypeNum(2);
            teacherDao.insert(assistantData);
        }
    }
    
    //7.获取班级学生列表并插入学生关联表
    int64_t classId = dto->class_id.getValue(0);
    std::list<int64_t> studentIds = ClassStudentDAO().selectStudentIdsByClassId(classId);
    
    if (!studentIds.empty()) 
    {
        LessonStudentDAO studentDao;
        
        for (const auto& kv : lessonDecCountMap) 
        {
            uint64_t lessonId = kv.first;
            int lessonDecCount = kv.second;
            for (int64_t studentId : studentIds) 
            {
                uint64_t studentRecordId = snowflake.nextId();
                if (studentRecordId == 0) {
                    throw std::runtime_error(ZH_WORDS_GETTER("freecourses.wrong.id_generate_failed"));
                }
                LessonStudentDO studentData;
                studentData.setId(studentRecordId);
                studentData.setLessonId(static_cast<int64_t>(lessonId));
                studentData.setClassId(static_cast<int>(classId));
                studentData.setStudentId(studentId);
                studentData.setDecLessonCount(0);
                studentData.setLessonCount(lessonDecCount);
                studentData.setSignState(0);
                studentData.setAddTime(currentTime);
                studentDao.insert(studentData);
            }
        }
    }
    
    return lessonRows;
}
