#include "stdafx.h"
#include "repeatCoursesArrangeService.h"
#include "dao/Schedule/lesson/LessonDAO.h"
#include "dao/Schedule/lesson/LessonTeacherDAO.h"
#include "dao/Schedule/lesson/LessonStudentDAO.h"
#include "dao/Schedule/course/CourseDAO.h"
#include "dao/Schedule/holiday/HolidayDAO.h"
#include "dao/Schedule/class_student/ClassStudentDAO.h"
#include "SimpleDateTimeFormat.h"
#include "id/SnowFlake.h"
#include "ServerInfo.h"
#include <ctime>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>

// 课程信息结构体，只包含数据表相关字段
struct LessonInfo
{
    std::string date;           
    std::string start_time;
    std::string end_time;
    int dec_class_time;
};

void addOneDay(std::tm& date) 
{
    date.tm_mday++;
    std::mktime(&date);  // 自动处理溢出（如 1月32日 -> 2月1日）
}

// 获取星期几（1=周一，7=周日）
int getBusinessWeekday(const std::tm& date) 
{
    int wday = date.tm_wday;  // 0=周日，1=周一，...，6=周六
    return (wday == 0) ? 7 : wday;  // 转换为 1=周一，7=周日
}

// 格式化日期为字符串 "YYYY-MM-DD"
std::string formatDate(const std::tm& date) 
{
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    return std::string(buf);
}

// 补全时间格式为 HH:MM:SS
static std::string formatTime(const std::string& time) 
{
    if (time.length() == 5 && time[2] == ':') {
        return time + ":00";
    }
    return time;
}

// 解析逗号分隔的星期字符串，设置对应位置为1
void parseWeekdays(const std::string& weeksStr, std::vector<int>& result) 
{
    result.assign(8, 0);  // 初始化8个元素为0，索引1-7对应周一到周日
    std::stringstream ss(weeksStr);
    std::string item;
    while (std::getline(ss, item, ',')) 
    {
        if (!item.empty()) 
        {
            int wd = std::stoi(item);
            if (wd >= 1 && wd <= 7) {
                result[wd] = 1;
            }
        }
    }
}

int64_t RepeatCoursesArrangeService::saveRepeatCoursesArrange(const repeatCoursesArrangeDTO::Wrapper& dto)
{
    //1.前置准备
    //获取当前时间和用户
    std::string currentTime = SimpleDateTimeFormat::format();
    int64_t userId = std::stoll(dto->getPayload()->getId());
    
    //通过class_id从数据库中获取课程名称
    std::string courseName = CourseDAO().selectNameById(dto->course_id.getValue(0));
    
    //从holiday表中获取假期的信息
    std::set<std::string> holidayDates;     //用set保存假期信息
    if (dto->skip_holiday.getValue(false))
    {
        //根据当前时间段查找存在的假期的日期
        auto holidays = HolidayDAO().selectDatesByRange(dto->start_date.getValue(""), dto->end_date.getValue(""));
        for (const auto& h : holidays)
        {
            holidayDates.insert(h);
        }
    }
    
    //从dto中解析出开始和结束日期
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;
    sscanf(dto->start_date.getValue("").c_str(), "%d-%d-%d", &startYear, &startMonth, &startDay);
    sscanf(dto->end_date.getValue("").c_str(), "%d-%d-%d", &endYear, &endMonth, &endDay);



    // 2.根据传递的周期段和日期范围确定课程具体日期及对应时间段
    // 2.1 收集上课时段信息（包含星期、时间、消课课时、教室id）
    std::vector<std::vector<int>> weekdaysList;
    std::vector<std::string> startTimes;
    std::vector<std::string> endTimes;
    std::vector<int> decClassTimes;
    
    for (auto& period : *dto->class_period) 
    {
        std::vector<int> weekdays;
        parseWeekdays(period->weeks.getValue(""), weekdays);
        weekdaysList.push_back(weekdays);
        startTimes.push_back(period->start_time.getValue(""));
        endTimes.push_back(period->end_time.getValue(""));
        decClassTimes.push_back(period->dec_class_time.getValue(1));
    }
    
    // 3.根据日期范围确定课程具体日期及对应时间段
    std::list<LessonInfo> lessonInfoList;
    
    // 初始化起始日期
    std::tm currentDate = {};
    currentDate.tm_year = startYear - 1900;
    currentDate.tm_mon = startMonth - 1;
    currentDate.tm_mday = startDay;
    std::mktime(&currentDate);
    
    // 初始化结束日期
    std::tm endDate = {};
    endDate.tm_year = endYear - 1900;
    endDate.tm_mon = endMonth - 1;
    endDate.tm_mday = endDay;
    std::mktime(&endDate);
    
    // 遍历日期范围内每一天
    while (std::mktime(&currentDate) <= std::mktime(&endDate)) 
    {
        // 获取当前日期
        std::string dateStr = formatDate(currentDate);
        
        //满足需要检查假期且存储假期的set中存在假期，则检查下一天
        if (dto->skip_holiday.getValue(false) && holidayDates.count(dateStr))
        {
            addOneDay(currentDate);
            continue;
        }
        
        int businessWeekday = getBusinessWeekday(currentDate);  
        
        for (size_t i = 0; i < weekdaysList.size(); ++i) 
        {
            if (weekdaysList[i][businessWeekday]) 
            {
                LessonInfo lessonInfo;
                lessonInfo.date = dateStr;
                lessonInfo.start_time = startTimes[i];
                lessonInfo.end_time = endTimes[i];
                lessonInfo.dec_class_time = decClassTimes[i];
                lessonInfoList.push_back(lessonInfo);
            }
        }        
        //将当前日期增加一天，继续遍历下一天
        addOneDay(currentDate);
    }
    
    // 4.组装课程列表中数据为DO列表
    //如果需要检查冲突，需要从lesson数据表表中查看冲突的课程
    if (dto->check_confilct.getValue(false))
    {
        //获取教室id
        int64_t roomId = dto->classroom_id.getValue(0);
        
        //建立map映射，key为时间槽，值表示该时间槽对应的具体日期
        std::map<std::string, std::set<std::string>> timeSlotDates;
        for (const auto& info : lessonInfoList)
        {
            std::string timeKey = info.start_time + "_" + info.end_time;
            timeSlotDates[timeKey].insert(info.date);
        }
        
        //用List保存冲突信息并且返回
        std::list<ConflictInfo> allConflicts;
        for (const auto& kv : timeSlotDates)
        {
            size_t pos = kv.first.find('_');
            std::string startTime = kv.first.substr(0, pos);
            std::string endTime = kv.first.substr(pos + 1);
            
            auto conflicts = LessonDAO().checkConflictBatch(roomId, kv.second, startTime, endTime);
            allConflicts.insert(allConflicts.end(), conflicts.begin(), conflicts.end());
        }
        
        //list非空，则存在冲突，返回冲突
        if (!allConflicts.empty())
        {
            std::string conflictMsg = ZH_WORDS_GETTER("repeatcourses.conflict.prefix")
                + std::to_string(allConflicts.size())
                + ZH_WORDS_GETTER("repeatcourses.conflict.suffix")
                + ZH_WORDS_GETTER("repeatcourses.conflict.specific_info_tip");
            for (const auto& c : allConflicts)
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
                throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.student_count_exceed_limit"));
            }
        }
    }
    
    //查询班级中该课程的最大节次
    int maxSn = LessonDAO().getMaxSnByClassIdAndCourseId(dto->class_id.getValue(0), dto->course_id.getValue(0));
    
    //按日期排序课程信息列表
    lessonInfoList.sort([](const LessonInfo& a, const LessonInfo& b) {
        if (a.date != b.date) return a.date < b.date;
        return a.start_time < b.start_time;
    });

    std::list<LessonDO> lessonList;
    int currentSn = maxSn;
    for (auto& lessonInfo : lessonInfoList) 
    {
        LessonDO& lessonData = lessonList.emplace_back();
        
        //1.dto中所有相关字段转换到do
        // 使用宏定义转换DTO字段到DO
        ZO_STAR_DOMAIN_DTO_TO_DO(lessonData, dto, 
            ClassId, class_id, 
            CourseId, course_id,
            RoomId, classroom_id
        );

        lessonData.setDecCount(lessonInfo.dec_class_time);              // 设置消课课时
        lessonData.setTeacherId(stoll(dto->teacher_id.getValue("")));   //教师id
        lessonData.setBookable(dto->open_appointment.getValue(false) ? 1 : 0);          //是否开放预约

        //与日期相关的字段
        lessonData.setDate(lessonInfo.date);
        lessonData.setStartTime(formatTime(lessonInfo.start_time));
        lessonData.setEndTime(formatTime(lessonInfo.end_time));

        //通过课程id获取课程信息：课程名title，课程节次暂定为1
        lessonData.setTitle(courseName);

        //注意前面有关于检查冲突实现和跳过节假日的实现

        //2.其他字段
        currentSn++;
        lessonData.setSn(currentSn);       //设置课程节次，递增
        lessonData.setCreator(userId);      //创建人id
        lessonData.setAddTime(currentTime); //创建时间
        lessonData.setDeleted(0);       //删除标记
        lessonData.setTeachType(1);     //设置授课方式，默认为1，可能需要根据课程表调整
        lessonData.setOnTrial(0);       //设置是否试听，默认为否
        lessonData.setState(0);         //设置课次状态，默认为0，可能需要根据课程表调整
        // lessonData.setEditor(userId);        编辑字段不考虑
        // lessonData.setEditTime(currentTime);
    }
    
    //如果经过排课后仍然没有数据不进行插入
    if (lessonList.empty())throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.no_lessons"));

    // 5.逐条插入课程并使用雪花算法生成ID,并建立课程id与消课课时的映射,用于后续插入教师表和学生表
    LessonDAO lessonDao;
    SnowFlake snowflake(ServerInfo::getInstance().getDatacenterId(), ServerInfo::getInstance().getMachineId());
    std::unordered_map<uint64_t, int> lessonDecCountMap;
    int lessonRows = 0;
    
    for (auto& lesson : lessonList) 
    {
        uint64_t lessonId = snowflake.nextId();
        if (lessonId == 0) {
            throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.id_generate_failed"));
        }
        lesson.setId(lessonId);
        int rows = lessonDao.insert(lesson);
        if (rows > 0) 
        {   //建立id和消课课时的映射，用作后续插入lesson_student表中
            lessonDecCountMap[lessonId] = lesson.getDecCount();
            lessonRows++;
        }
    }
    
    if (lessonRows <= 0) return 0;
    
    //获取教师列表
    LessonTeacherDAO teacherDao;
    
    //遍历课程id与消课课时映射，查找教师和助教并设置数据
    for (const auto& kv : lessonDecCountMap) 
    {
        uint64_t lessonId = kv.first;
        if (dto->teacher_id && !dto->teacher_id->empty()) 
        {
            uint64_t teacherId = snowflake.nextId();
            if (teacherId == 0) {
                throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.id_generate_failed"));
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
                throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.id_generate_failed"));
            }
            LessonTeacherDO assistantData;
            assistantData.setId(assistantId);
            assistantData.setLessonId(static_cast<int64_t>(lessonId));
            assistantData.setTeacherId(std::stoll(dto->assistant_id.getValue("")));
            assistantData.setTypeNum(2);
            teacherDao.insert(assistantData);
        }
    }
    
    //获取班级id，并且根据班级id获取学生id列表
    int64_t classId = dto->class_id.getValue(0);
    std::list<int64_t> studentIds = ClassStudentDAO().selectStudentIdsByClassId(classId);
    
    //7.执行向课程学生表中插入数据
    if (!studentIds.empty()) 
    {
        LessonStudentDAO studentDao;
        
        //为每个学生和课程一一对应分配课程
        for (const auto& kv : lessonDecCountMap) 
        {
            uint64_t lessonId = kv.first;
            int decCount = kv.second;
            for (int64_t studentId : studentIds) 
            {
                uint64_t studentRecordId = snowflake.nextId();
                if (studentRecordId == 0) {
                    throw std::runtime_error(ZH_WORDS_GETTER("repeatcourses.wrong.id_generate_failed"));
                }
                LessonStudentDO studentData;
                studentData.setId(studentRecordId);
                studentData.setLessonId(static_cast<int64_t>(lessonId));
                studentData.setClassId(static_cast<int>(classId));
                studentData.setStudentId(studentId);
                studentData.setDecLessonCount(0);
                studentData.setLessonCount(decCount);
                studentData.setSignState(0);
                studentData.setAddTime(currentTime);
                studentDao.insert(studentData);
            }
        }
    }
    
    return lessonRows;
}
