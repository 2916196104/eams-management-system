#pragma once
#ifndef _PARENT_ACCOUNT_CONTROLLER_H_
#define _PARENT_ACCOUNT_CONTROLLER_H_

#include "ApiHelper.h"
#include "Macros.h"
#include "ServerInfo.h"
#include "service/parentaccount/ParentAccountService.h"
#include "domain/query/parentaccount/ParentAccountQuery.h"
#include "domain/vo/parentaccount/ParentAccountVO.h"
#include "domain/dto/parentaccount/ParentAccountDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
using namespace oatpp;
#define API_TAG ZH_WORDS_GETTER("parentaccount.api-tag")


class ParentAccountController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ParentAccountController);
private:
	ParentAccountService m_parentAccountService;
public:
	// page-query
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("parentaccount.interface.query-parent-account"), queryParentAccount, ParentAccountQuery, ParentAccountPageJsonVO::Wrapper, API_TAG);

	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c6/parent-account/query", queryParentAccount, ParentAccountQuery, execQueryParentAccount(query));

	ENDPOINT_INFO(parentAccountChange) {

		info->summary = ZH_WORDS_GETTER("parentaccount.interface.modify-parent-account");

		info->addTag(ZH_WORDS_GETTER("parentaccount.api-tag"));

		API_DEF_ADD_AUTH();

		API_DEF_ADD_RSP_JSON(ParentAccountChangeJsonVO::Wrapper);

		info->addConsumes<Object<ParentAccountChangeDTO>>("application/json");
	}

	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"c6/parentAccountChange",
		parentAccountChange,
		BODY_DTO(Object<ParentAccountChangeDTO>, dto),
		excuteParentAccountChange(dto)
	);

	ENDPOINT_INFO(parentPasswordChange) {

		info->summary = ZH_WORDS_GETTER("parentaccount.interface.modify-parent-password");

		info->addTag(ZH_WORDS_GETTER("parentaccount.api-tag"));

		API_DEF_ADD_AUTH();

		API_DEF_ADD_RSP_JSON(ParentPasswordChangeJsonVO::Wrapper);

		info->addConsumes<Object<ParentPasswordChangeDTO>>("application/json");
	}

	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"c6/parentPasswordChange",
		parentPasswordChange,
		BODY_DTO(Object<ParentPasswordChangeDTO>, dto),
		excuteParentPasswordChange(dto)
	);
private:
	ParentAccountPageJsonVO::Wrapper execQueryParentAccount(const ParentAccountQuery::Wrapper& query);
	ParentAccountChangeJsonVO::Wrapper excuteParentAccountChange(const ParentAccountChangeDTO::Wrapper& dto);
	ParentPasswordChangeJsonVO::Wrapper excuteParentPasswordChange(const ParentPasswordChangeDTO::Wrapper& dto);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PARENT_ACCOUNT_CONTROLLER_H_
