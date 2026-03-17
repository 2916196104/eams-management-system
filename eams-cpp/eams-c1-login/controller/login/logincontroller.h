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

	/**
	 * 1. 发送验证码
	 * 请求参数：
	 * {
	 *   "mobile": "13800138000",
	 *   "email": "123456@qq.com"
	 * }
	 *
	 * 业务逻辑：
	 * 1) 校验手机号与邮箱格式
	 * 2) 查询数据库中是否存在对应账号
	 * 3) 生成6位验证码
	 * 4) 将验证码存入 Redis：pwd:reset:{mobile}:{email}，TTL=300秒
	 * 5) 通过 QQ 邮箱发送验证码
	 */
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.send-code.summary"),
		sendResetCode,
		SendResetCodeJsonVO::Wrapper,
		API_TAG
	);

	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c1/login/send-code",
		sendResetCode,
		BODY_DTO(SendResetCodeDTO::Wrapper, dto),
		executeSendResetCode(dto)
	);


	/**
 * 2. 找回密码
 * 请求参数：
 * {
 *   "mobile": "13800138000",
 *   "email": "123456@qq.com",
 *   "verifyCode": "123456",
 *   "newPassword": "new123456"
 * }
 *
 * 业务逻辑：
 * 1) 校验请求参数
 * 2) 根据 Redis Key：pwd:reset:{mobile}:{email} 读取验证码
 * 3) 验证验证码是否存在、是否一致
 * 4) 查询数据库确认用户存在
 * 5) 加密新密码并更新数据库
 * 6) 删除 Redis 中验证码，防止重复使用
 */
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("login.reset-password.summary"),
		resetPassword,
		ResetPasswordJsonVO::Wrapper,
		API_TAG
	);

	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"/c1/login/reset-password",
		resetPassword,
		BODY_DTO(ResetPasswordDTO::Wrapper, dto),
		executeResetPassword(dto)
	);


private: // 定义接口执行函数
	/**
	 * 执行：发送验证码
	 * 这里在 .cpp 中建议实现以下逻辑：
	 * 1. 判空与格式校验
	 * 2. 校验 mobile + email 对应用户是否存在
	 * 3. 生成验证码
	 * 4. Redis.setex("pwd:reset:" + mobile + ":" + email, 300, verifyCode)
	 * 5. 邮件发送
	 * 6. 组装返回值
	 */
	SendResetCodeJsonVO::Wrapper executeSendResetCode(const SendResetCodeDTO::Wrapper& dto);

	/**
	 * 执行：找回密码
	 * 这里在 .cpp 中建议实现以下逻辑：
	 * 1. 判空与格式校验
	 * 2. 从 Redis 获取验证码
	 * 3. 比较验证码是否一致
	 * 4. 校验用户是否存在
	 * 5. 更新密码
	 * 6. 删除 Redis key
	 * 7. 返回结果
	 */
	ResetPasswordJsonVO::Wrapper executeResetPassword(const ResetPasswordDTO::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_LOGINCONTROLLER_H_