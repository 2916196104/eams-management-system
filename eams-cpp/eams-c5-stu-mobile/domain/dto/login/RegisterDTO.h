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
	DTO_FIELD(String, telephoneNumber);
	DTO_FIELD_INFO(telephoneNumber){
		info->description = ZH_WORDS_GETTER("c5.login.register.field.telephoneNumber.info");
	}
	// 验证码
	DTO_FIELD(Int32, vertificationCode);
	DTO_FIELD_INFO(vertificationCode) {
		info->description = ZH_WORDS_GETTER("c5.login.register.field.verificationCode.info");
	}
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("c5.login.register.field.name.info");
	}
	// 密码
	DTO_FIELD(String, password);
	DTO_FIELD_INFO(password) {
		info->description = ZH_WORDS_GETTER("c5.login.register.field.password.info");
	}
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate();
private:
	bool checkPassword();
	bool checkTelephoneNumber();
	bool checkVertificationCode();
};

class RegisterDTO : public RegisterAddDTO
{
	DTO_INIT(RegisterDTO, RegisterAddDTO);
	// id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id){
		info->description = ZH_WORDS_GETTER("c5.login.register.field.id");
	}
};

/**
 * 注册分页传输对象
 */
class RegisterPageDTO : public PageDTO<RegisterDTO::Wrapper>
{
	DTO_INIT(RegisterPageDTO, PageDTO<RegisterDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_REGISTER_DTO_H_
