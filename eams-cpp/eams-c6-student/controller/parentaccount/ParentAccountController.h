#pragma once
#ifndef _PARENTACCOUNTCONTROLLER_H_
#define _PARENTACCOUNTCONTROLLER_H_

#include "../../domain/GlobalInclude.h"
#include "../../domain/vo/parentaccount/ParentAccountVO.h"
#include "../../domain/dto/parentaccount/ParentAccountDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class ParentAccountController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ParentAccountController);

public:
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
	ParentAccountChangeJsonVO::Wrapper excuteParentAccountChange(const ParentAccountChangeDTO::Wrapper& dto);
	ParentPasswordChangeJsonVO::Wrapper excuteParentPasswordChange(const ParentPasswordChangeDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif