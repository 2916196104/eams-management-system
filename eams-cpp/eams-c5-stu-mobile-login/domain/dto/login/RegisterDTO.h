#pragma once
#ifndef _REGISTER_DTO_H_
#define _REGISTER_DTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
* 注册数据传输对象
*/
class RegisterAddDTO : public oatpp::DTO
{
	DTO_INIT(RegisterAddDTO, DTO);
	// 手机号
	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile){
		info->description = ZH_WORDS_GETTER("register.field.telephoneNumber.info");
	}
	// 验证码
	DTO_FIELD(Int32, vertificationCode);
	DTO_FIELD_INFO(vertificationCode) {
		info->description = ZH_WORDS_GETTER("register.field.verificationCode.info");
	}
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("register.field.name.info");
	}
	// 密码
	DTO_FIELD(String, password);
	DTO_FIELD_INFO(password) {
		info->description = ZH_WORDS_GETTER("register.field.password.info");
	}
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

class RegisterDTO : public RegisterAddDTO
{
	DTO_INIT(RegisterDTO, RegisterAddDTO);
	// id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id){
		info->description = ZH_WORDS_GETTER("register.field.id");
	}
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_REGISTER_DTO_H_
