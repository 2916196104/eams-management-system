#pragma once
#ifndef _REMARKQUERY_H_
#define _REMARKQUERY_H_

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 签到查询类
* 封装查询条件：支持分页和过滤
* 核心字段：分页参数、查询参数
* 接收前端传递的查询参数，并将其传递给服务层或数据库层
*/
class RemarkQuery :public PageQuery
{
	DTO_INIT(RemarkQuery, PageQuery);
	/*API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("c7.field.stu-id"));
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("c7.field.stu-name"), true);
	API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("c7.field.remark"), true);
	API_DTO_FIELD_REQUIRE(UInt64, remarkstar, ZH_WORDS_GETTER("c7.field.remark-star"), true);
	API_DTO_FIELD_REQUIRE(String, remarker, ZH_WORDS_GETTER("c7.field.remarker"), true);
	API_DTO_FIELD_REQUIRE(String, remarktime, ZH_WORDS_GETTER("c7.field.remark-time"), true);
	*/
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_REMARKQUERY_H_
