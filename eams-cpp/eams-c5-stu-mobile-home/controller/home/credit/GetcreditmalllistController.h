#pragma once
#ifndef _CET_CREDIT_MALL_LIST_CONTROLLER_H_
#define _CET_CREDIT_MALL_LIST_CONTROLLER_H_

#include "domain/query/home/credit/GetCreditMallListQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/home/credit/GetCreditMallListVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("get-credit-mall-list.tag")

class GetCreditMallListController : public oatpp::web::server::api::ApiController
{
	// 添加访问定义
	API_ACCESS_DECLARE(GetCreditMallListController);
public:
	// 定义查询所有积分商品信息接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("get-credit-mall-list.summary"), queryAllCreditMallList, CreditMallListQuery, CreditMallListJsonVO::Wrapper, API_TAG);
	// 定义查询所有积分商品信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c5home/credit/get_credit_mall_list", queryAllCreditMallList, CreditMallListQuery, executeQueryAll(query));
private:
	CreditMallListPageJsonVO::Wrapper executeQueryAll(const CreditMallListQuery::Wrapper& creditmallQuery);

};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // !_CET_CREDIT_MALL_LIST_CONTROLLER_H_
