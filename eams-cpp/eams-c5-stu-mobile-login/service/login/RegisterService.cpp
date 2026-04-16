#include "stdafx.h"
#include "RegisterService.h"
#include "dao/register/RegisterDAO.h"
#include "../lib-common/include/bcrypt/bcrypt.h"
#include "Macros.h"

std::string RegisterService::insert(RegisterAddDTO::Wrapper dto)
{
    RegisterDAO dao;
    PtrRegisterDO pdo = std::make_shared<RegisterDO>();

    std::string pwd = encrpyPassword(dto->password.getValue(""));
    pdo->setPassword(pwd);
    pdo->setMobile(dto->mobile.getValue(""));
    pdo->setName(dto->name.getValue(""));

    return dao.insertUser(pdo);
}

std::string RegisterService::validate(const RegisterAddDTO::Wrapper dto)
{
	if (!checkPassword(dto->password.getValue(""))) return ZH_WORDS_GETTER("login.register.field.password.errMsg");
	if (!checkMobile(dto->mobile.getValue(""))) return ZH_WORDS_GETTER("login.register.field.telephoneNumber.errMsg");
	if (!checkVertificationCode(std::to_string(dto->vertificationCode.getValue(1))))
		return ZH_WORDS_GETTER("login.register.field.vertificationCode.errMsg");
	if (RegisterDAO().isMobileExist(dto->mobile.getValue("")))
        return ZH_WORDS_GETTER("login.register.field.telephoneNumber.errMsgExist");
    return insert(dto);
}
// 加密密码
std::string RegisterService::encrpyPassword(std::string password)
{
    return bcrypt::generateHash(password);
}

// 校验手机号
bool RegisterService::checkMobile(std::string mobile)
{
    if (mobile.length() != 11) return false;

    for (char c : mobile) 
    {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

// 校验密码
bool RegisterService::checkPassword(std::string password)
{
    if (password.length() < 8) return false;

    // 是否包含数字
    bool hasDigit = false;  
    // 是否包含字母
    bool hasLetter = false; 

    for (char c : password) 
    {
        if (std::isdigit(c)) hasDigit = true;
        else if (std::isalpha(c)) hasLetter = true;
    }

    return hasDigit && hasLetter;
}

// 校验验证码
bool RegisterService::checkVertificationCode(std::string vertificationCode)
{
	return true;
}