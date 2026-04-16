#pragma once
#ifndef TIMETABLE_H
#define TIMETABLE_H
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
请假传输对象
*/
class LeaveDTO :public oatpp::DTO
{
    DTO_INIT(LeaveDTO, DTO);
    // 课程ID
    API_DTO_FIELD_REQUIRE(String, lessonId, ZH_WORDS_GETTER("timetable.field.leave.lesson-id"), true);
    // 请假原因
    API_DTO_FIELD_DEFAULT(String, reason, ZH_WORDS_GETTER("timetable.field.leave.reason"));
    // 请假学员ID
    API_DTO_FIELD_DEFAULT(String, studentId, ZH_WORDS_GETTER("timetable.field.leave.student-id"));
};

/*
预约请求DTO
*/
class ReserveDTO : public oatpp::DTO
{
    DTO_INIT(ReserveDTO, DTO);
    //课程ID
    API_DTO_FIELD_REQUIRE(String, lessonId, ZH_WORDS_GETTER("timetable.field.reserve.lesson-id"), true);
    API_DTO_FIELD_DEFAULT(String, studentId, ZH_WORDS_GETTER("timetable.field.reserve.student-id"));

public:
    std::string validate()
    {
        if (!lessonId || lessonId->empty())
            return "lessonId cannot be empty.";
        if (!studentId || studentId->empty())
        {
            return "studentId cannot be empty.";
        }
        return "";
    }
};

/**
 * 签到请求DTO
 */
class TimetableSignDTO : public oatpp::DTO
{
    DTO_INIT(TimetableSignDTO, DTO);

    // 课程ID
    API_DTO_FIELD_REQUIRE(String, lessonId, ZH_WORDS_GETTER("timetable.field.sign.lesson-id"), true);
    // 把签到方式枚举说明直接写到Swagger描述里
    // 1-老师管理端操作 2-家长端学生手动签到
    API_DTO_FIELD_DEFAULT(Int32, signType, ZH_WORDS_GETTER("timetable.field.sign.sign-type"));
    // 学员ID
    API_DTO_FIELD_DEFAULT(String, studentId, ZH_WORDS_GETTER("timetable.field.sign.student-id"));

public:
    std::string validate()
    {
        if (!lessonId || lessonId->empty())
        {
            return "lessonId cannot be empty.";
        }
        if (!studentId || studentId->empty())
        {
            return "studentId cannot be empty.";
        }
        if (!signType)
        {
            return "signType cannot be empty.";
        }
        return "";
    }
};

/**
 * 通用操作响应DTO
 * 用于签到/预约/请假
 */
class TimetableActionResultDTO : public oatpp::DTO
{
    DTO_INIT(TimetableActionResultDTO, DTO);

    API_DTO_FIELD(Boolean, success, ZH_WORDS_GETTER("timetable.field.action.success"), false, false);
    API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("timetable.field.action.message"));
    API_DTO_FIELD_DEFAULT(String, lessonId, ZH_WORDS_GETTER("timetable.field.action.lesson-id"));
    API_DTO_FIELD_DEFAULT(String, actionType, ZH_WORDS_GETTER("timetable.field.action.action-type"));
};

/**
 * 签到专用响应DTO
 * 用于签到接口的响应Schema展示
 */
class TimetableSignResultDTO : public oatpp::DTO
{
    DTO_INIT(TimetableSignResultDTO, DTO);

    // 是否签到成功
    API_DTO_FIELD(Boolean, success, ZH_WORDS_GETTER("timetable.field.sign-result.success"), false, false);
    // 提示信息
    API_DTO_FIELD_DEFAULT(String, message, ZH_WORDS_GETTER("timetable.field.sign-result.message"));
    // 课程ID
    API_DTO_FIELD_DEFAULT(String, lessonId, ZH_WORDS_GETTER("timetable.field.sign-result.lesson-id"));
    // 签到方式：1老师管理端操作 2家长端学生手动签到
    API_DTO_FIELD(Int32, signType, ZH_WORDS_GETTER("timetable.field.sign-result.sign-type"), false, 2);
    // 签到结果状态：0未签到 1已签到 2补签 3请假 4旷课
    API_DTO_FIELD(Int32, signState, ZH_WORDS_GETTER("timetable.field.sign-result.sign-state"), false, 0);
    // 签到结果状态文本
    API_DTO_FIELD_DEFAULT(String, signStateText, ZH_WORDS_GETTER("timetable.field.sign-result.sign-state-text"));
    // 签到时间
    API_DTO_FIELD_DEFAULT(String, signTime, ZH_WORDS_GETTER("timetable.field.sign-result.sign-time"));
};

/**
 * 月历计数项
 * 示例：{ "date": "2026-03-25", "count": 1 }
 */
class TimetableCalendarItemDTO : public oatpp::DTO
{
    DTO_INIT(TimetableCalendarItemDTO, DTO);
    // 日期
    API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("timetable.field.calendar.date"));
    // 当天课次数量
    API_DTO_FIELD(Int32, count, ZH_WORDS_GETTER("timetable.field.calendar.count"), false, 0);
};

/**
 * 月历数据DTO
 */
class TimetableMonthDTO : public oatpp::DTO
{
    DTO_INIT(TimetableMonthDTO, DTO);
    // 年份
    API_DTO_FIELD(Int32, year, ZH_WORDS_GETTER("timetable.field.query.year"), false, 0);
    // 月份
    API_DTO_FIELD(Int32, month, ZH_WORDS_GETTER("timetable.field.query.month"), false, 0);
    // 日期计数列表
    API_DTO_FIELD(List<Object<TimetableCalendarItemDTO>>, dateList, ZH_WORDS_GETTER("timetable.field.query.date-list"), false, {});
};

/**
 * 通用课程卡片DTO
 * 已入班课和可预约课共用
 * 
 */
class TimetableCourseItemDTO : public oatpp::DTO
{
    DTO_INIT(TimetableCourseItemDTO, DTO);

    // 课程ID
    API_DTO_FIELD_DEFAULT(String, lessonId, ZH_WORDS_GETTER("timetable.field.item.lesson-id"));
    // 课程标题
    API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("timetable.field.item.title"));
    // 班级ID
    API_DTO_FIELD_DEFAULT(String, classId, ZH_WORDS_GETTER("timetable.field.item.class-id"));
    // 班级名称
    API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("timetable.field.item.class-name"));
    // 教室ID
    API_DTO_FIELD_DEFAULT(String, roomId, ZH_WORDS_GETTER("timetable.field.item.room-id"));
    // 教室名称
    API_DTO_FIELD_DEFAULT(String, roomName, ZH_WORDS_GETTER("timetable.field.item.room-name"));
    // 教师ID
    API_DTO_FIELD_DEFAULT(String, teacherId, ZH_WORDS_GETTER("timetable.field.item.teacher-id"));
    // 教师姓名
    API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("timetable.field.item.teacher-name"));
    // 上课日期
    API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("timetable.field.item.date"));
    // 开始时间
    API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("timetable.field.item.start-time"));
    // 结束时间
    API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("timetable.field.item.end-time"));
    // 备注
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("timetable.field.item.remark"));

    // 课程状态：1进行中（未开始+正在上课都归这里）2已结课
    API_DTO_FIELD(Int32, lessonState, ZH_WORDS_GETTER("timetable.field.item.lesson-state"), false, 1);
    API_DTO_FIELD_DEFAULT(String, lessonStateText, ZH_WORDS_GETTER("timetable.field.item.lesson-state-text"));

    // 卡片类型：lesson课表分组里的课 reservable预约分组里的课
    API_DTO_FIELD_DEFAULT(String, cardType, ZH_WORDS_GETTER("timetable.field.item.card-type"));

    // 签到状态：0未签到 1已签到 2补签 3请假 4旷课
    // 对于可预约课，固定给0，同时signStateText置空
    API_DTO_FIELD(Int32, signState, ZH_WORDS_GETTER("timetable.field.item.sign-state"), false, 0);
    API_DTO_FIELD_DEFAULT(String, signStateText, ZH_WORDS_GETTER("timetable.field.item.sign-state-text"));

    // 动作控制
    API_DTO_FIELD(Boolean, canSign, ZH_WORDS_GETTER("timetable.field.item.can-sign"), false, false);
    API_DTO_FIELD(Boolean, canLeave, ZH_WORDS_GETTER("timetable.field.item.can-leave"), false, false);
    API_DTO_FIELD(Boolean, canReserve, ZH_WORDS_GETTER("timetable.field.item.can-reserve"), false, false);

    // 右侧按钮
    // actionType: sign/leave/reserve/none
    // actionText: 签到/请假/预约/空
    API_DTO_FIELD_DEFAULT(String, actionType, ZH_WORDS_GETTER("timetable.field.item.action-type"));
    API_DTO_FIELD_DEFAULT(String, actionText, ZH_WORDS_GETTER("timetable.field.item.action-text"));
};

/**
 * 单个分组DTO
 * 例如：3.30 课表、3.30 预约课
 */
class TimetableSectionDTO : public oatpp::DTO
{
    DTO_INIT(TimetableSectionDTO, DTO);

    // 分组标题
    API_DTO_FIELD_DEFAULT(String, sectionTitle, ZH_WORDS_GETTER("timetable.field.section.section-title"));
    // 节数
    API_DTO_FIELD(Int32, total, ZH_WORDS_GETTER("timetable.field.section.total"), false, 0);
    // 课程列表
    API_DTO_FIELD(List<Object<TimetableCourseItemDTO>>, courseList, ZH_WORDS_GETTER("timetable.field.section.course-list"), false, {}); 
    // 空态提示,只有分组为空时才返回文案
    API_DTO_FIELD_DEFAULT(String, emptyTip, ZH_WORDS_GETTER("timetable.field.section.empty-tip"));
};

/**
 * 按天课表响应DTO
 */
class TimetableListDTO : public oatpp::DTO
{
    DTO_INIT(TimetableListDTO, DTO);

    // 查询日期
    API_DTO_FIELD_REQUIRE(String, queryDate, ZH_WORDS_GETTER("timetable.field.query.query-date"), true);

    // 月历每天课表数量列表
    API_DTO_FIELD(List<Object<TimetableCalendarItemDTO>>, calendarList, ZH_WORDS_GETTER("timetable.field.query.calendar-list"), false, {});

    // 课表分组：包含已入班正式课 + 已提交预约待审核/审核通过的课
    API_DTO_FIELD_DEFAULT(Object<TimetableSectionDTO>, lessonSection, ZH_WORDS_GETTER("timetable.field.query.lesson-section"));

    // 预约分组：只包含还能预约的课
    API_DTO_FIELD_DEFAULT(Object<TimetableSectionDTO>, reserveSection, ZH_WORDS_GETTER("timetable.field.query.reserve-section"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_H
