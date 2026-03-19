#pragma once
#ifndef _PARENT_ACCOUNT_DTO_H_
#define _PARENT_ACCOUNT_DTO_H_

#include "ApiHelper.h"
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 家长账号DTO
 */
class ParentAccountDTO : public oatpp::DTO
{
	DTO_INIT(ParentAccountDTO, DTO);

	API_DTO_FIELD_DEFAULT(Int64, userId, ZH_WORDS_GETTER("parentaccount.field.parent-query.user-id"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("parentaccount.field.parent-query.mobile"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("parentaccount.field.parent-query.name"));
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("parentaccount.field.parent-query.student-name"));
	API_DTO_FIELD_DEFAULT(String, wxName, ZH_WORDS_GETTER("parentaccount.field.parent-query.wx-name"));
	API_DTO_FIELD_DEFAULT(Int32, loginTimes, ZH_WORDS_GETTER("parentaccount.field.parent-query.login-times"));
	API_DTO_FIELD_DEFAULT(String, latestLoginTime, ZH_WORDS_GETTER("parentaccount.field.parent-query.latest-login-time"));
	API_DTO_FIELD_DEFAULT(String, latestLoginIp, ZH_WORDS_GETTER("parentaccount.field.parent-query.latest-login-ip"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("parentaccount.field.parent-query.add-time"));
	API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("parentaccount.field.parent-query.state"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PARENT_ACCOUNT_DTO_H_
