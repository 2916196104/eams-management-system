#pragma once
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 自由排课请求模型
 */
class FreeSchedulingQuery : public oatpp::DTO {

    DTO_INIT(FreeSchedulingQuery, DTO);

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
    //上课日期
    API_DTO_FIELD_DEFAULT(String, date, ZH_WORDS_GETTER("schedule.field.date"));
    //开始上课时间
    API_DTO_FIELD_DEFAULT(String, start_time, ZH_WORDS_GETTER("schedule.field.startTime"));
    //上课结束时间
    API_DTO_FIELD_DEFAULT(String, end_time, ZH_WORDS_GETTER("schedule.field.endTime"));
    //人数限制
    API_DTO_FIELD(Int32, limitNum, ZH_WORDS_GETTER("schedule.field.limitNum"), false, 0);
};

#include OATPP_CODEGEN_END(DTO)