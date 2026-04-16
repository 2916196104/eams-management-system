#pragma once
#ifndef _COURSEDTO_H_
#define _COURSEDTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class CourseDTO : public oatpp::DTO
{
	DTO_INIT(CourseDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, courseId, ZH_WORDS_GETTER("course.field.courseId"));
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("course.field.courseName"));
	API_DTO_FIELD_DEFAULT(String, subjectName, ZH_WORDS_GETTER("course.field.subjectName"));
	API_DTO_FIELD_DEFAULT(String, lessonType, ZH_WORDS_GETTER("course.field.lessonType"));
	API_DTO_FIELD_DEFAULT(String, startTime, ZH_WORDS_GETTER("course.field.startTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("course.field.endTime"));
	API_DTO_FIELD_DEFAULT(Int32, courseNum, ZH_WORDS_GETTER("course.field.courseNum"));
	API_DTO_FIELD_DEFAULT(Int32, coursePrice, ZH_WORDS_GETTER("course.field.coursePrice"));
	API_DTO_FIELD_DEFAULT(Int32, discountPrice, ZH_WORDS_GETTER("course.field.discountPrice"));
	API_DTO_FIELD_DEFAULT(Int32, actualPayment, ZH_WORDS_GETTER("course.field.actualPayment"));
	API_DTO_FIELD_DEFAULT(Int32, expireMonths, ZH_WORDS_GETTER("course.field.expireMonths"));
	API_DTO_FIELD_DEFAULT(String, tip, ZH_WORDS_GETTER("course.field.tip"));
	API_DTO_FIELD_DEFAULT(Boolean, reportType, ZH_WORDS_GETTER("course.field.reportType"));
	API_DTO_FIELD_DEFAULT(String, stuName, ZH_WORDS_GETTER("course.field.stuName"));
};

class CoursePageDTO : public PageDTO<CourseDTO::Wrapper>
{
	DTO_INIT(CoursePageDTO, PageDTO<CourseDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif