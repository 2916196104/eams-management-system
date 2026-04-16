#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:10:30

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _LOGINCONTRULLER_H_
#define _LOGINCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/dto/login/AuthDTO.h"
#include "domain/vo/login/loginVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("login.tag")

//登陆模块控制器
class loginController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(loginController);
public: // 定义接口

	// 定义发送验证码接口信息
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.send-code.summary"),
		sendResetCode,
		SendResetCodeJsonVO::Wrapper,
		API_TAG
	);
	// 发送验证码接口
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c1login/common/open/sendSms",
		sendResetCode,
		BODY_DTO(SendResetCodeDTO::Wrapper, dto),
		executeSendResetCode(dto)
	);

	// 定义修改密码接口信息
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.modify-password.summary"),
		resetPassword,
		UpdatePasswordJsonVO::Wrapper,
		API_TAG
	);

	// 修改密码接口
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"/c1login/common/open/forgetPwd",
		resetPassword,
		BODY_DTO(UpdatePasswordDTO::Wrapper, dto),
		executeModifyPassword(dto)
	);
	
	// 定义发送注册验证码接口信息
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.send-register-code.summary"),
		sendRegisterCode,
		SendRegisterCodeJsonVO::Wrapper,
		API_TAG
	);
	// 发送注册验证码接口
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c1login/common/open/regist/sendSms",
		sendRegisterCode,
		BODY_DTO(SendRegisterCodeDTO::Wrapper, dto),
		executeSendRegisterCode(dto)
	);
	// 定义注册接口信息
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.register.summary"),
		registerAccount,
		RegisterJsonVO::Wrapper,
		API_TAG
	);
	// 注册接口
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c1login/common/open/register",
		registerAccount,
		BODY_DTO(RegisterDTO::Wrapper, dto),
		executeAddAccount(dto)
	);
	

private: // 定义接口执行函数
	// 发送验证码
	SendResetCodeJsonVO::Wrapper executeSendResetCode(const SendResetCodeDTO::Wrapper& dto);
	// 修改密码
	UpdatePasswordJsonVO::Wrapper executeModifyPassword(const UpdatePasswordDTO::Wrapper& dto);
	// 发送注册短信验证
	SendRegisterCodeJsonVO::Wrapper executeSendRegisterCode(const SendRegisterCodeDTO::Wrapper& dto);
	// 注册账号
	RegisterJsonVO::Wrapper executeAddAccount(const RegisterDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_LOGINCONTROLLER_H_