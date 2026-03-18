#include "stdafx.h"
#include "RegisterDTO.h"

bool RegisterAddDTO::checkPassword()
{
	int numCnt = 0, charCnt = 0;
	std::string p = password->c_str();
	for (char c : p)
	{
		if (c >= '0' && c <= '9') numCnt++;
		else charCnt++;
	}
	return numCnt && charCnt && numCnt + charCnt >= 10;
}

std::string RegisterAddDTO::validate()
{
	if (!password||!checkPassword()) return ZH_WORDS_GETTER("register.field.password.errMsg");
	else if(!vertificationCode || !checkVertificationCode()) return ZH_WORDS_GETTER("register.field.vertificartionCode.errMsg");
	else if(!telephoneNumber || !checkTelephoneNumber()) return ZH_WORDS_GETTER("register.field.telephoneNumber.errMsg");
	else if(!name||name->empty()) return ZH_WORDS_GETTER("register.field.name.errMsg");
	return "";
}

bool RegisterAddDTO::checkTelephoneNumber()
{
	int num = 0;
	std::string t = telephoneNumber->c_str();
	for (auto c : t)
	{
		if (c <= '9' && c >= '0') num++;
	}
	return num == 11 && telephoneNumber->length() == 11;
}

bool RegisterAddDTO::checkVertificationCode()
{
	return true;
}