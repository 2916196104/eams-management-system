#pragma once
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 重复排课请求模型
 */
class RepeatedSchedulingQuery : public oatpp::DTO {

    DTO_INIT(RepeatedSchedulingQuery, DTO);

public:
    //班级id
    API_DTO_FIELD(Int64, id, ZH_WORDS_GETTER("schedule.field.classId"), true, 1);
    //课程id
    API_DTO_FIELD(Int64, course_id, ZH_WORDS_GETTER("schedule.field.courseId"), true, 1);
    //教师id
    API_DTO_FIELD(Int64, teacher_ids, ZH_WORDS_GETTER("schedule.field.teacherId"), true, 1);
    //助教id
    API_DTO_FIELD_DEFAULT(Int64, assistant_ids, ZH_WORDS_GETTER("schedule.field.assistantId"));
    //教室id
    API_DTO_FIELD(Int64, classroom_id, ZH_WORDS_GETTER("schedule.field.classroomId"), true, 1);
    //开始课程日期
    API_DTO_FIELD_DEFAULT(String, start_date, ZH_WORDS_GETTER("schedule.field.startDate"), true);
    //结束课程日期
    API_DTO_FIELD_DEFAULT(String, end_date, ZH_WORDS_GETTER("schedule.field.endDate"), true);
    //每周上课天
    API_DTO_FIELD_DEFAULT(List<Int32>, weekDays, ZH_WORDS_GETTER("schedule.field.weekDays"));
    //课程开始时间
    API_DTO_FIELD(String, start_time, ZH_WORDS_GETTER("schedule.field.startTime"), true, "08:00");
    //课程结束时间
    API_DTO_FIELD(String, end_time, ZH_WORDS_GETTER("schedule.field.endTime"), true, "10:00");
    //限制人数
    API_DTO_FIELD(Int32, limitNum, ZH_WORDS_GETTER("schedule.field.limitNum"), false, 0);
    //跳过节日
    API_DTO_FIELD(Boolean, exclude_holiday, ZH_WORDS_GETTER("schedule.field.skipHolidays"), false, true);
    //预约
    API_DTO_FIELD(Boolean, bookable, ZH_WORDS_GETTER("schedule.field.enableReservation"), false, false);
    //冲突
    API_DTO_FIELD(Boolean, conflict, ZH_WORDS_GETTER("schedule.field.checkExamConflict"), false, true);
};

#include OATPP_CODEGEN_END(DTO)