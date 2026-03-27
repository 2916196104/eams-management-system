#pragma once
#ifndef _GET_CREDIT_MALL_LIST_QUERY_H_
#define _GET_CREDIT_MALL_LIST_QUERY_H_

#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询积分礼品信息的数据传输模型
 */
class CreditMallListQuery : public PageQuery
{
	// 定义初始化
	DTO_INIT(CreditMallListQuery, PageQuery);
	// 昵称
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("get-credit-mall-list.name"));

};


#include OATPP_CODEGEN_END(DTO)

#endif // !_GET_CREDIT_MALL_LIST_QUERY_H_
