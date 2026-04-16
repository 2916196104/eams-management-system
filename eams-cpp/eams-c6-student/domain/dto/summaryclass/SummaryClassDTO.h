#pragma once
#ifndef _SUMMARYCLASS_H_
#define _SUMMARYCLASS_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class SummaryClassDTO : public oatpp::DTO
{
	DTO_INIT(SummaryClassDTO, DTO);

	// 学员姓名
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("summaryclass.field.student.student-name"));

	// 课程
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("summaryclass.field.student.course-name"));

	// 上课记录 (如：上0 假0 旷0 补0)
	API_DTO_FIELD_DEFAULT(String, attendanceRecord, ZH_WORDS_GETTER("summaryclass.field.student.attendance-record"));

	// 总课次
	API_DTO_FIELD_DEFAULT(Int32, totalLessons, ZH_WORDS_GETTER("summaryclass.field.student.total-lessons"));

	// 已上课次
	API_DTO_FIELD_DEFAULT(Int32, usedLessons, ZH_WORDS_GETTER("summaryclass.field.student.used-lessons"));

	// 剩余课次
	API_DTO_FIELD_DEFAULT(Int32, remainingLessons, ZH_WORDS_GETTER("summaryclass.field.student.remaining-lessons"));
};

class SummaryClassPageDTO : public PageDTO<SummaryClassDTO::Wrapper>
{
	DTO_INIT(SummaryClassPageDTO, PageDTO<SummaryClassDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)


#endif
