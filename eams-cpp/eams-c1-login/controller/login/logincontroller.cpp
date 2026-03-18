/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/08 21:19:14

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
#include "stdafx.h"
#include "logincontroller.h"
//#include "service/login/loginService.h"
//实现接口执行函数

// 发送验证码
SendResetCodeJsonVO::Wrapper loginController::executeSendResetCode(const SendResetCodeDTO::Wrapper& dto)
{
	/*loginService ls;
	auto vo = SendResetCodeJsonVO::createShared();
	vo->success(ls.sendResetCode(dto));
	return vo;*/
	return {};
}

// 修改密码
UpdatePasswordJsonVO::Wrapper loginController::executeModifyPassword(const UpdatePasswordDTO::Wrapper& dto)
{
	//loginService ls;
	//auto vo = UpdatePasswordJsonVO::createShared();
 //   vo->success(ls.resetPassword(dto));
	//return vo;
	return {};
}

//发送注册短信验证
SendRegisterCodeJsonVO::Wrapper loginController::executeSendRegisterCode(const SendResetCodeDTO::Wrapper& dto)
{
	/*loginService ls;
	auto vo = SendRegisterCodeJsonVO::createShared();
	vo->data = (ls.sendRegisterCode(dto));
	return vo;*/
	return {};
}

//注册账号
RegisterJsonVO::Wrapper loginController::executeRegister(const RegisterDTO::Wrapper& dto)
{
	/*loginService ls;
	auto vo = RegisterJsonVO::createShared();
	vo->data = (ls.registerAccount(dto));
	return vo;*/
	return {};
}
