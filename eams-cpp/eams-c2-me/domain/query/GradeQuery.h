#pragma once

#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户信息的数据传输模型
 */
class GradeQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(GradeQuery, PageQuery);

};

#include OATPP_CODEGEN_END(DTO)