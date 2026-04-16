#pragma once
#ifndef __GRADE_MANAGE_QUERY_H__
#define __GRADE_MANAGE_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	成绩查询类
*/

class GradeManageQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(GradeManageQuery, PageQuery);

	// 考核项 (必填，用于精准查询某次考核的成绩)
	API_DTO_FIELD_REQUIRE(String, item, ZH_WORDS_GETTER("Grade.field.item"), true);

	// 如果后续需要按学生姓名模糊查询，可以加在这里（非必填）
	// API_DTO_FIELD(String, name, ZH_WORDS_GETTER("Grade.field.name"));
};

#include OATPP_CODEGEN_END(DTO)

#endif