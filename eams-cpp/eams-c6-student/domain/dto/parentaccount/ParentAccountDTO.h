#pragma once
#ifndef _PARENT_ACCOUNT_DTO_H_
#define _PARENT_ACCOUNT_DTO_H_

#include "ApiHelper.h"
#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)


class ParentAccountQueryDTO : public oatpp::DTO
{
	DTO_INIT(ParentAccountQueryDTO, DTO);

	API_DTO_FIELD_DEFAULT(Int64, userId, ZH_WORDS_GETTER("parentaccount.field.parent.user-id"));
	API_DTO_FIELD_DEFAULT(String, mobile, ZH_WORDS_GETTER("parentaccount.field.parent.mobile"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("parentaccount.field.parent.name"));
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("parentaccount.field.parent.student-name"));
	API_DTO_FIELD_DEFAULT(String, wxName, ZH_WORDS_GETTER("parentaccount.field.parent.wx-name"));
	API_DTO_FIELD_DEFAULT(Int32, loginTimes, ZH_WORDS_GETTER("parentaccount.field.parent.login-times"));
	API_DTO_FIELD_DEFAULT(String, latestLoginTime, ZH_WORDS_GETTER("parentaccount.field.parent.latest-login-time"));
	API_DTO_FIELD_DEFAULT(String, latestLoginIp, ZH_WORDS_GETTER("parentaccount.field.parent.latest-login-ip"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("parentaccount.field.parent.add-time"));
	API_DTO_FIELD_DEFAULT(Int32, state, ZH_WORDS_GETTER("parentaccount.field.parent.state"));
};
class ParentAccountChangeDTO : public oatpp::DTO
{
	DTO_INIT(ParentAccountChangeDTO, DTO);

	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("parentaccount.field.parent.user-id"), true);

	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("parentaccount.field.parent.name"), true);

	API_DTO_FIELD_REQUIRE(Int32, state, ZH_WORDS_GETTER("parentaccount.field.parent.state"), true);
};

class ParentPasswordChangeDTO : public oatpp::DTO
{
	DTO_INIT(ParentPasswordChangeDTO, DTO);

	API_DTO_FIELD_REQUIRE(UInt64, id, ZH_WORDS_GETTER("parentaccount.field.parent.user-id"), true);

	API_DTO_FIELD_REQUIRE(String, oldPassword, ZH_WORDS_GETTER("parentaccount.field.parent.old-password"), true);

	API_DTO_FIELD_REQUIRE(String, newPassword, ZH_WORDS_GETTER("parentaccount.field.parent.new-password"), true);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_PARENT_ACCOUNT_DTO_H_
