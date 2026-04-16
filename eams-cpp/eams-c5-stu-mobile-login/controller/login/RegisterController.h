#pragma once
#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/register/RegisterQuery.h"
#include "domain/dto/login/RegisterDTO.h"
#include OATPP_CODEGEN_BEGIN(ApiController) 

// 注册控制器
class RegisterController : public oatpp::web::server::api::ApiController
{
	// 定义访问入口
	API_ACCESS_DECLARE(RegisterController);
public:

	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("login.register.summary"), Register, StringJsonVO::Wrapper, ZH_WORDS_GETTER("login.summary"));
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c5login/register", Register, BODY_DTO(RegisterAddDTO::Wrapper, dto), executeRegister(dto, authObject->getPayload()));

private:
	StringJsonVO::Wrapper executeRegister(const RegisterAddDTO::Wrapper& dto, const PayloadDTO& payload);

};

#include OATPP_CODEGEN_END(ApiController)
#endif // REGISTERCONTROLLER_H