#pragma once
#ifndef _SUMMARYCLASSQUERY_H_
#define _SUMMARYCLASSQUERY_H_

#include "../../GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 课时汇总查询类
*/
class SummaryClassQuery : public PageQuery
{
	DTO_INIT(SummaryClassQuery, PageQuery);

	//1.学员姓名
	API_DTO_FIELD_REQUIRE(String, studentName, ZH_WORDS_GETTER("summaryclass.field.student.student-name"), false);

	//2.课程名称
	API_DTO_FIELD_REQUIRE(String, courseName, ZH_WORDS_GETTER("summaryclass.field.student.course-name"), false);
};


#include OATPP_CODEGEN_END(DTO)


#endif



