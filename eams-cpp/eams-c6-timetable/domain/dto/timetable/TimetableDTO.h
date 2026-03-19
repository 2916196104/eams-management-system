#pragma once
#ifndef TIMETABLE_H
#define TIMETABLE_H
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/*
课程表传输对象
*/

class TimetableDTO :public oatpp::DTO
{

    DTO_INIT(TimetableDTO, DTO);
    //教室名字
    API_DTO_FIELD_DEFAULT(String, className, ZH_WORDS_GETTER("filed.timetable.classname"))
        //课程名字
        API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("filed.timetable.coursename"))
        //教师名字
        API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("filed.timetable.teachername"))
        //开始时间
        API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("filed.timetable.starttime"))
        //结束时间
        API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("filed.timetable.endtime"))
        //课程状态
        API_DTO_FIELD_DEFAULT(String, status, ZH_WORDS_GETTER("filed.timetable.status"))
        //是否预约
        API_DTO_FIELD_DEFAULT(Boolean, canReserve, ZH_WORDS_GETTER("filed.timetable.can-reserve"))
        //是否请假
        API_DTO_FIELD_DEFAULT(Boolean, canLeave, ZH_WORDS_GETTER("filed.timetable.can-leave"))
   

	
};
//分页传输
class TimetablePageDTO : public  PageDTO<TimetableDTO::Wrapper>
{
    DTO_INIT(TimetablePageDTO, PageDTO<TimetableDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // TIMETABLE_H
