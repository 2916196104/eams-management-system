#pragma once
#ifndef __GRADE_MANAGE_QUERY_H__
#define __GRADE_MANAGE_QUERY_H__

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	成绩查询类
*/

class GradeManageQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(GradeManageQuery, PageQuery);
	// 考核项 (必须)
	API_DTO_FIELD_REQUIRE(String, item, ZH_WORDS_GETTER("Grade.field.item"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif