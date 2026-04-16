package com.zeroone.star.j1.console.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j1.console.entity.*;
import com.zeroone.star.j1.console.mapper.*;
import com.zeroone.star.j1.console.service.IConsoleService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j1.console.*;
import com.zeroone.star.project.vo.j1.console.*;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

/**
 * <p>
 * 描述：控制台服务实现
 * </p>
 * <p>版权：&copy;01 星球</p>
 * <p>地址：01 星球总部</p>
 * @author hxb
 * @version 1.0.0
 */
@Service
public class ConsoleServiceImpl implements IConsoleService {

    @Resource
    private StudentMapper studentMapper;
    @Resource
    private StaffMapper staffMapper;
    @Resource
    private LessonMapper lessonMapper;
    @Resource
    private StudentCourseMapper studentCourseMapper;
    @Resource
    private ContactRecordMapper contactRecordMapper;
    @Resource
    private CashoutMapper cashoutMapper;
    @Resource
    private NoticeMapper noticeMapper;
    @Resource
    private CourseMapper courseMapper;
    @Resource
    private ClassMapper classMapper;
    @Resource
    private ClassroomMapper classroomMapper;
    @Resource
    private UserMapper userMapper;

    @Override
    public ConsoleStatisticsVO getStatistics() {
        ConsoleStatisticsVO vo = new ConsoleStatisticsVO();
        
        vo.setTotalStudents(studentMapper.countTotalStudents());
        vo.setTotalLessons(lessonMapper.countTotalLessons());
        vo.setTotalTeachers(staffMapper.countTotalTeachers());
        
        String yearMonth = java.time.LocalDate.now().format(DateTimeFormatter.ofPattern("yyyy-MM"));
        Double monthAmount = studentCourseMapper.countMonthEnrollmentAmount(yearMonth);
        vo.setMonthEnrollmentAmount(monthAmount != null ? Math.round(monthAmount / 10000.0 * 10.0) / 10.0 : 0.0);
        
        return vo;
    }
    
    @Override
    public MonthEnrollmentVO getMonthEnrollment(MonthEnrollmentQuery query) {
        MonthEnrollmentVO vo = new MonthEnrollmentVO();
        
        String yearMonth = String.format("%d-%02d", query.getYear(), query.getMonth());
        vo.setMonth(yearMonth);
        
        Integer totalEnrollments = studentCourseMapper.countMonthEnrollments(yearMonth);
        vo.setTotalEnrollments(totalEnrollments != null ? totalEnrollments : 0);
        
        double completionRate = totalEnrollments != null ? totalEnrollments * 100.0 / 300 : 0;
        vo.setTargetCompletionRate(Math.round(completionRate * 10.0) / 10.0);
        
        List<Map<String, Object>> dailyData = studentCourseMapper.countDailyEnrollments(yearMonth);
        List<MonthEnrollmentVO.DailyEnrollmentData> dailyList = new ArrayList<>();
        if (dailyData != null) {
            for (Map<String, Object> data : dailyData) {
                MonthEnrollmentVO.DailyEnrollmentData item = new MonthEnrollmentVO.DailyEnrollmentData();
                item.setDate((String) data.get("date"));
                item.setCount(((Number) data.get("count")).intValue());
                dailyList.add(item);
            }
        }
        vo.setDailyData(dailyList);
        
        return vo;
    }
    
    @Override
    public List<CourseEnrollmentRankVO> getCourseEnrollmentRank() {
        List<Map<String, Object>> rankData = studentCourseMapper.selectCourseEnrollmentAmountRank(5);
        List<CourseEnrollmentRankVO> result = new ArrayList<>();
        if (rankData != null) {
            for (Map<String, Object> data : rankData) {
                CourseEnrollmentRankVO item = new CourseEnrollmentRankVO();
                item.setCourseName((String) data.get("courseName"));
                item.setAmount(((Number) data.get("amount")).doubleValue());
                result.add(item);
            }
        }
        return result;
    }
    
    @Override
    public TimetableCalendarVO getTimetableCalendar(TimetableCalendarQuery query) {
        TimetableCalendarVO vo = new TimetableCalendarVO();
        
        LambdaQueryWrapper<LessonDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(LessonDO::getDeleted, 0);
        wrapper.orderByAsc(LessonDO::getDate, LessonDO::getStartTime);
        
        if (query.getStartDate() != null && !query.getStartDate().isEmpty()) {
            wrapper.ge(LessonDO::getDate, java.sql.Date.valueOf(query.getStartDate()));
        }
        if (query.getEndDate() != null && !query.getEndDate().isEmpty()) {
            wrapper.le(LessonDO::getDate, java.sql.Date.valueOf(query.getEndDate()));
        }
        if (query.getCourseId() != null) {
            wrapper.eq(LessonDO::getCourseId, query.getCourseId());
        }
        if (query.getClassId() != null) {
            wrapper.eq(LessonDO::getClassId, query.getClassId());
        }
        if (query.getTeacherId() != null) {
            wrapper.eq(LessonDO::getTeacherId, query.getTeacherId());
        }
        
        List<LessonDO> lessons = lessonMapper.selectList(wrapper);
        
        List<TimetableCalendarVO.ScheduleItem> scheduleList = new ArrayList<>();
        for (LessonDO lesson : lessons) {
            TimetableCalendarVO.ScheduleItem item = new TimetableCalendarVO.ScheduleItem();
            item.setId(lesson.getId());
            item.setCourseName(courseMapper.getNameById(lesson.getCourseId()));
            item.setClassName(classMapper.getNameById(lesson.getClassId()));
            item.setTeacherName(staffMapper.getNameById(lesson.getTeacherId()));
            item.setClassroom(classroomMapper.getNameById(lesson.getRoomId()));
            
            if (lesson.getDate() != null && lesson.getStartTime() != null) {
                item.setStartTime(lesson.getDate().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime());
            }
            scheduleList.add(item);
        }
        
        vo.setList(scheduleList);
        vo.setTotal((long) scheduleList.size());
        return vo;
    }

    @Override
    public MyCustomerVO getMyCustomerList(MyCustomerQuery query) {
        Page<StudentDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentDO::getDeleted, 0);
        wrapper.eq(StudentDO::getStage, 0); // 意向学员
        
        if (query.getStudentName() != null && !query.getStudentName().isEmpty()) {
            wrapper.like(StudentDO::getName, query.getStudentName());
        }
        if (query.getStage() != null) {
            wrapper.eq(StudentDO::getStage, query.getStage());
        }
        if (query.getGender() != null) {
            wrapper.eq(StudentDO::getGender, query.getGender());
        }
        wrapper.orderByDesc(StudentDO::getAddTime);
        
        com.baomidou.mybatisplus.core.metadata.IPage<StudentDO> studentPage = studentMapper.selectPage(page, wrapper);
        
        List<MyCustomerVO.CustomerItem> voList = studentPage.getRecords().stream().map(student -> {
            MyCustomerVO.CustomerItem item = new MyCustomerVO.CustomerItem();
            item.setId(student.getId());
            item.setStudentName(student.getName());
            item.setStage(student.getStage());
            item.setStageName(getLearnStageName(student.getStage()));
            item.setGender(student.getGender());
            item.setGenderName(getGenderName(student.getGender()));
            item.setAge(calculateAge(student.getBirthday()));
            item.setSourceName(getSourceName(student.getJoinWay()));
            item.setRemark(student.getRemark());
            item.setAddTime(student.getAddTime() != null ?
                student.getAddTime().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime() : null);
            
            // 获取家长信息
            if (student.getUserId() != null) {
                item.setParentName(userMapper.getNameById(student.getUserId()));
                item.setContactPhone(userMapper.getMobileById(student.getUserId()));
            }
            item.setFamilyRel(student.getFamilyRel());
            item.setFamilyRelName(getFamilyRelName(student.getFamilyRel()));
            
            // 计算剩余课次
            LambdaQueryWrapper<StudentCourseDO> courseWrapper = new LambdaQueryWrapper<>();
            courseWrapper.eq(StudentCourseDO::getStudentId, student.getId())
                        .eq(StudentCourseDO::getDeleted, 0);
            List<StudentCourseDO> courses = studentCourseMapper.selectList(courseWrapper);
            int remainCount = 0;
            for (StudentCourseDO course : courses) {
                if (course.getCountLessonTotal() != null && course.getCountLessonComplete() != null) {
                    remainCount += course.getCountLessonTotal() - course.getCountLessonComplete();
                }
            }
            item.setRemainLessonCount(remainCount);
            item.setDeficiencyStatus(remainCount < 0 ? 1 : 0);
            
            // 获取最近跟进记录
            LambdaQueryWrapper<ContactRecordDO> recordWrapper = new LambdaQueryWrapper<>();
            recordWrapper.eq(ContactRecordDO::getStudentId, student.getId())
                        .eq(ContactRecordDO::getDeleted, 0)
                        .orderByDesc(ContactRecordDO::getContactTime)
                        .last("LIMIT 1");
            ContactRecordDO record = contactRecordMapper.selectOne(recordWrapper);
            
            if (record != null) {
                item.setLastFollowTime(record.getContactTime() != null ?
                    record.getContactTime().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime() : null);
                item.setLastFollowContent(record.getInfo());
                item.setNextFollowTime(record.getContactNextTime() != null ?
                    record.getContactNextTime().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime() : null);
            }
            return item;
        }).collect(Collectors.toList());
        
        MyCustomerVO vo = new MyCustomerVO();
        vo.setTotal(studentPage.getTotal());
        vo.setList(voList);
        return vo;
    }

    @Override
    public PageDTO<MyEnrollmentVO> getMyEnrollment(MyEnrollmentQuery query) {
        Page<StudentCourseDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<StudentCourseDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(StudentCourseDO::getDeleted, 0);
        if (query.getStartDateBegin() != null && !query.getStartDateBegin().isEmpty()) {
            wrapper.ge(StudentCourseDO::getStartDate, query.getStartDateBegin());
        }
        if (query.getStartDateEnd() != null && !query.getStartDateEnd().isEmpty()) {
            wrapper.le(StudentCourseDO::getStartDate, query.getStartDateEnd());
        }
        wrapper.orderByDesc(StudentCourseDO::getAddTime);

        Page<StudentCourseDO> resultPage = studentCourseMapper.selectPage(page, wrapper);
        return PageDTO.create(resultPage, doItem -> {
            MyEnrollmentVO vo = new MyEnrollmentVO();
            vo.setId(doItem.getId());
            vo.setEnrollmentTime(doItem.getAddTime() != null ? doItem.getAddTime().toString() : null);
            vo.setPurchaseLessonCount(doItem.getCountLessonTotal());
            vo.setUnitPrice(doItem.getUnitPrice());
            vo.setContractAmount(doItem.getAmount());
            vo.setPaidAmount(doItem.getPaidAmount());
            if (doItem.getAmount() != null && doItem.getPaidAmount() != null) {
                vo.setArrearsAmount(doItem.getAmount().subtract(doItem.getPaidAmount()));
            }
            vo.setStartDate(doItem.getStartDate() != null ? doItem.getStartDate().toString() : null);
            vo.setExpireDate(doItem.getExpireDate() != null ? doItem.getExpireDate().toString() : null);
            return vo;
        });
    }

    @Override
    public PageDTO<AnnouncementVO> getAnnouncement(AnnouncementQuery query) {
        Page<NoticeDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<NoticeDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(NoticeDO::getDeleted, 0);
        if (query.getTitle() != null && !query.getTitle().isEmpty()) {
            wrapper.like(NoticeDO::getTitle, query.getTitle());
        }
        wrapper.orderByDesc(NoticeDO::getAddTime);

        Page<NoticeDO> resultPage = noticeMapper.selectPage(page, wrapper);
        return PageDTO.create(resultPage, doItem -> {
            AnnouncementVO vo = new AnnouncementVO();
            vo.setId(doItem.getId());
            vo.setTitle(doItem.getTitle());
            vo.setAddTime(doItem.getAddTime() != null ? doItem.getAddTime().toString() : null);
            vo.setEditTime(doItem.getEditTime() != null ? doItem.getEditTime().toString() : null);
            return vo;
        });
    }

    @Override
    public PageDTO<MyFollowVO> getMyFollow(MyFollowQuery query) {
        Page<ContactRecordDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<ContactRecordDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(ContactRecordDO::getDeleted, 0);
        if (query.getStage() != null) {
            wrapper.eq(ContactRecordDO::getStage, query.getStage());
        }
        wrapper.orderByDesc(ContactRecordDO::getContactTime);

        Page<ContactRecordDO> resultPage = contactRecordMapper.selectPage(page, wrapper);
        return PageDTO.create(resultPage, doItem -> {
            MyFollowVO vo = new MyFollowVO();
            vo.setId(doItem.getId());
            vo.setFollowTime(doItem.getContactTime() != null ? doItem.getContactTime().toString() : null);
            vo.setStage(doItem.getStage());
            vo.setContactType(doItem.getContactType());
            vo.setNextFollowTime(doItem.getContactNextTime() != null ? doItem.getContactNextTime().toString() : null);
            vo.setRecordTime(doItem.getAddTime() != null ? doItem.getAddTime().toString() : null);
            vo.setContent(doItem.getInfo());
            return vo;
        });
    }

    @Override
    public PageDTO<MyPaymentVO> getMyPayment(MyPaymentQuery query) {
        Page<CashoutDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<CashoutDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(CashoutDO::getDeleted, 0);
        if (query.getTitle() != null && !query.getTitle().isEmpty()) {
            wrapper.like(CashoutDO::getTitle, query.getTitle());
        }
        if (query.getType() != null) {
            wrapper.eq(CashoutDO::getType, query.getType());
        }
        if (query.getPayeeName() != null && !query.getPayeeName().isEmpty()) {
            wrapper.like(CashoutDO::getPayeeName, query.getPayeeName());
        }
        wrapper.orderByDesc(CashoutDO::getAddTime);

        Page<CashoutDO> resultPage = cashoutMapper.selectPage(page, wrapper);
        return PageDTO.create(resultPage, doItem -> {
            MyPaymentVO vo = new MyPaymentVO();
            vo.setId(doItem.getId());
            vo.setTitle(doItem.getTitle());
            vo.setType(doItem.getType());
            vo.setPayeeName(doItem.getPayeeName());
            vo.setAmount(doItem.getAmount());
            vo.setApplyTime(doItem.getAddTime() != null ? doItem.getAddTime().toString() : null);
            vo.setAccount(doItem.getAccount());
            vo.setInfo(doItem.getInfo());
            vo.setVerifyState(doItem.getVerifyState());
            vo.setVerifyRemark(doItem.getVerifyRemark());
            return vo;
        });
    }

    @Override
    public PageDTO<ScheduleCalendarVO> getScheduleCalendar(ScheduleCalendarQuery query) {
        Page<LessonDO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        LambdaQueryWrapper<LessonDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(LessonDO::getDeleted, 0);
        if (query.getDateBegin() != null && !query.getDateBegin().isEmpty()) {
            wrapper.ge(LessonDO::getDate, query.getDateBegin());
        }
        if (query.getDateEnd() != null && !query.getDateEnd().isEmpty()) {
            wrapper.le(LessonDO::getDate, query.getDateEnd());
        }
        if (query.getClassId() != null) {
            wrapper.eq(LessonDO::getClassId, query.getClassId());
        }
        if (query.getCourseId() != null) {
            wrapper.eq(LessonDO::getCourseId, query.getCourseId());
        }
        wrapper.orderByAsc(LessonDO::getDate).orderByAsc(LessonDO::getStartTime);

        Page<LessonDO> resultPage = lessonMapper.selectPage(page, wrapper);
        return PageDTO.create(resultPage, doItem -> {
            ScheduleCalendarVO vo = new ScheduleCalendarVO();
            vo.setId(doItem.getId());
            String classTime = "";
            if (doItem.getDate() != null) {
                classTime = doItem.getDate().toString();
                if (doItem.getStartTime() != null) {
                    classTime += " " + doItem.getStartTime().toString();
                }
            }
            vo.setClassTime(classTime);
            vo.setTeachType(doItem.getTeachType());
            vo.setDecCount(doItem.getDecCount());
            vo.setState(doItem.getState());
            return vo;
        });
    }

    /**
     * 获取学习阶段名称
     */
    private String getLearnStageName(Integer stage) {
        if (stage == null) return "未知";
        switch (stage) {
            case 0: return "意向学员";
            case 1: return "在读学员";
            case 2: return "结业学员";
            default: return "未知";
        }
    }

    /**
     * 获取性别名称
     */
    private String getGenderName(Integer gender) {
        if (gender == null) return "未知";
        switch (gender) {
            case 0: return "未知";
            case 1: return "男";
            case 2: return "女";
            default: return "未知";
        }
    }

    /**
     * 获取来源名称
     */
    private String getSourceName(Long joinWay) {
        if (joinWay == null) return "未知";
        return "其他";
    }

    /**
     * 获取家庭关系名称
     */
    private String getFamilyRelName(Integer familyRel) {
        if (familyRel == null) return "未知";
        switch (familyRel) {
            case 1: return "爸爸";
            case 2: return "妈妈";
            case 3: return "爷爷";
            case 4: return "奶奶";
            case 5: return "外公";
            case 6: return "外婆";
            case 7: return "其他";
            default: return "未知";
        }
    }

    /**
     * 根据生日计算年龄
     */
    private Integer calculateAge(Date birthday) {
        if (birthday == null) return null;
        java.time.LocalDate birthDate = birthday.toInstant().atZone(ZoneId.systemDefault()).toLocalDate();
        return java.time.Period.between(birthDate, java.time.LocalDate.now()).getYears();
    }
}
