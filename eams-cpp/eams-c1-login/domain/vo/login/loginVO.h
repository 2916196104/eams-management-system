#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:27:22

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
#ifndef _LOGINVO_H_
#define _LOGINVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/login/AuthDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义显示对象
 */

 /**
  * 发送验证码返回 VO
  */
class SendResetCodeJsonVO : public JsonVO<SendResetCodeRespDTO::Wrapper>
{
	DTO_INIT(SendResetCodeJsonVO, JsonVO<SendResetCodeRespDTO::Wrapper>);
};

/**
 * 修改密码返回 VO
 */
class UpdatePasswordJsonVO : public JsonVO<UpdatePasswordRespDTO::Wrapper>
{
	DTO_INIT(UpdatePasswordJsonVO, JsonVO<UpdatePasswordRespDTO::Wrapper>);
};


// 发送注册验证码返回 VO
class SendRegisterCodeJsonVO : public JsonVO<SendRegisterCodeRespDTO::Wrapper> {
	DTO_INIT(SendRegisterCodeJsonVO, JsonVO<SendRegisterCodeRespDTO::Wrapper>)
};


// 注册返回 VO
class RegisterJsonVO : public JsonVO<RegisterRespDTO::Wrapper>
{
	DTO_INIT(RegisterJsonVO, JsonVO<RegisterRespDTO::Wrapper>)
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_LOGINVO_H_