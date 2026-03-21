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
    //课程ID
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("timetable.filed.leave.lesson-id"), true, "")
        //请假原因
        API_DTO_FIELD_DEFAULT(String, reason, ZH_WORDS_GETTER("timetable.filed.leave.reason"))
        //请假学员ID
        API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("timetable.filed.leave.student-id"))
};
/*
预约传输对象
*/
class ReserveDTO : public oatpp::DTO
{
    DTO_INIT(ReserveDTO, DTO);
    //课程ID
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("timetable.filed.reserve.lesson-id"), true, "")

};

/**
 * 单条课表项
 */
class TimetableItemDTO : public oatpp::DTO
{
    DTO_INIT(TimetableItemDTO, DTO);

    // 课程ID
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("timetable.filed.item.lesson-id"));
    // 课程标题
    API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("timetable.filed.item.title")); 
    // 班级名称
    API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("timetable.filed.item.class-name"));
    // 教室名称
    API_DTO_FIELD_DEFAULT(String, roomName, ZH_WORDS_GETTER("timetable.filed.item.room-name"));
    // 教师姓名
    API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("timetable.filed.item.teacher-name"));
    // 上课日期
    API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("timetable.filed.item.date"));
    // 开始时间
    API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("timetable.filed.item.start-time"));
    // 结束时间
    API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("timetable.filed.item.end-time"));
    // 课程状态
    API_DTO_FIELD(Int32, state, ZH_WORDS_GETTER("timetable.filed.item.state"), false, 0);
    // 备注
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("timetable.filed.item.remark"));
    // 签到状态
    API_DTO_FIELD(Int32, signState, ZH_WORDS_GETTER("timetable.filed.item.sign-state"), false, 0);
    // 是否可签到
    API_DTO_FIELD(Boolean, canSign, ZH_WORDS_GETTER("timetable.filed.item.can-sign"), false, false);
};

/**
 * 课表列表数据体
 */
class TimetableListDTO : public oatpp::DTO
{
    DTO_INIT(TimetableListDTO, DTO);

    // 查询日期
    API_DTO_FIELD_DEFAULT(String, queryDate, ZH_WORDS_GETTER("timetable.field.query.query-date"));
    // 当天课表总数
    API_DTO_FIELD_DEFAULT(UInt32, total, ZH_WORDS_GETTER("timetable.field.query.total"));
    // 课表列表
    API_DTO_FIELD(List<Object<TimetableItemDTO>>, lessonList, ZH_WORDS_GETTER("timetable.field.query.lesson-list"), false, {});
};


/**
 * 签到请求DTO
 */
class TimetableSignDTO : public oatpp::DTO
{
    DTO_INIT(TimetableSignDTO, DTO);

    // 课程ID
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("timetable.field.lesson-id"));
    // 签到方式
    API_DTO_FIELD_DEFAULT(Int32, signType, ZH_WORDS_GETTER("timetable.sign.sign-type"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_H
