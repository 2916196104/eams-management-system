#pragma once
#ifndef _COURSEDTO_H_
#define _COURSEDTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程列表数据传输对象
 */
class CourseDTO : public oatpp::DTO
{
	DTO_INIT(CourseDTO, DTO);
	//课程名称
	API_DTO_FIELD_DEFAULT(Boolean, reportType, ZH_WORDS_GETTER("course.field.reportType"));
	API_DTO_FIELD_DEFAULT(String, stuName, ZH_WORDS_GETTER("course.field.stuName"));
	API_DTO_FIELD_DEFAULT(String,coursename,ZH_WORDS_GETTER("course.field.courseName"));
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("course.field.startTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("course.field.endTime"));
	API_DTO_FIELD_DEFAULT(Int16, courseNum, ZH_WORDS_GETTER("course.field.courseNum"));
	API_DTO_FIELD_DEFAULT(Int16, coursePrice, ZH_WORDS_GETTER("course.field.coursePrice"));
	API_DTO_FIELD_DEFAULT(Int16, actualPayment, ZH_WORDS_GETTER("course.field.actualPayment"));
	API_DTO_FIELD_DEFAULT(Int16, discountPrice, ZH_WORDS_GETTER("course.field.discountPrice"));
	API_DTO_FIELD_DEFAULT(String, tip, ZH_WORDS_GETTER("course.field.tip"));
};
/*
* 分页课程数据查询
*/
class CoursePageDTO : public PageDTO<CourseDTO::Wrapper>
{
	DTO_INIT(CoursePageDTO, PageDTO<CourseDTO::Wrapper>);
	
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_
