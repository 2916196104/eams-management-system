#pragma once
#ifndef _REGISTERCONTROLLER_H_
#define _REGISTERCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "../../domain/dto/Course/RegisterDTO.h"
#include "ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("register.field.register")

class RegisterController : public web::server::api::ApiController
{
	API_ACCESS_DECLARE(RegisterController);
public:
	
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("register.save.summary"), saveReg, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/register", saveReg,
		BODY_DTO(RegisterAddDTO::Wrapper, dto),
		execSave(dto, authObject->getPayload())
	);

private:
	StringJsonVO::Wrapper execSave(const RegisterAddDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif