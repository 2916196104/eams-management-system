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
请假传输对象
*/
class ReserveDTO : public oatpp::DTO
{
    DTO_INIT(ReserveDTO, DTO);
    //课程ID
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("timetable.filed.reserve.lesson-id"), true, "")

};

#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_H
