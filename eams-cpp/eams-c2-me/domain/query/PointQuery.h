#pragma once


#include "../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户信息的数据传输模型
 */
class PointQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(PointQuery, PageQuery);
	// 昵称
	API_DTO_FIELD_DEFAULT(Int32, student_id, "student's id");
};

#include OATPP_CODEGEN_END(DTO)




