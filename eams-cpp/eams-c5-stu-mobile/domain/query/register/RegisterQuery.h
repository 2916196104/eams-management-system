#pragma once

#ifndef _REGISTER_QEURY_H_
#define _REGISTER_QEURY_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 注册查询对象
 */
class RegisterQuery : public oatpp::DTO
{
	DTO_INIT(RegisterQuery, DTO);
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
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_REGISTER_QEURY_H_