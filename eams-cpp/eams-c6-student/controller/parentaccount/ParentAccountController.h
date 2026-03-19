#pragma once
#ifndef _PARENT_ACCOUNT_CONTROLLER_H_
#define _PARENT_ACCOUNT_CONTROLLER_H_

#include "ApiHelper.h"
#include "Macros.h"
#include "ServerInfo.h"
#include "service/parentaccount/ParentAccountService.h"
#include "domain/query/parentaccount/ParentAccountQuery.h"
#include "domain/vo/parentaccount/ParentAccountVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
using namespace oatpp;
#define API_TAG ZH_WORDS_GETTER("parentaccount.api-tag")

/**
 * 家长账号控制器
 */
class ParentAccountController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ParentAccountController);
private:
	//ParentAccountService m_parentAccountService;
public:
	// 分页查询接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("parentaccount.interface.query-parent-account"), queryParentAccount, ParentAccountQuery, ParentAccountPageJsonVO::Wrapper, API_TAG);
	// 分页查询接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c6/parent-account/query", queryParentAccount, ParentAccountQuery, execQueryParentAccount(query));

private:
	ParentAccountPageJsonVO::Wrapper execQueryParentAccount(const ParentAccountQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PARENT_ACCOUNT_CONTROLLER_H_
