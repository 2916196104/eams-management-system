#pragma once
#ifndef _REGISTER_VO_H_
#define _REGISTER_VO_H_

#include "../../GlobalInclude.h"
#include "../../dto/login/RegisterDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
 */
class RegisterJsonVO : public JsonVO<RegisterDTO::Wrapper>
{
	DTO_INIT(RegisterJsonVO, JsonVO<RegisterDTO::Wrapper>);

};

/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class RegisterPageJsonVO : public JsonVO<RegisterPageDTO::Wrapper> {
	DTO_INIT(RegisterPageJsonVO, JsonVO<RegisterPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // _REGISTER_VO_H_