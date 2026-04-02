#pragma once
#ifndef _SIGNQUERY_H_
#define _SIGNQUERY_H_

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 签到查询类
* 封装查询条件：支持分页和过滤
* 核心字段：分页参数、查询参数
* 接收前端传递的查询参数，并将其传递给服务层或数据库层
*/
class SignQuery :public PageQuery
{
	DTO_INIT(SignQuery, PageQuery);

	//API_DTO_FIELD_REQUIRE(UInt64, t_id, ZH_WORDS_GETTER("sign.field.teacher-id"), true);

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SIGNQUERY_H_
