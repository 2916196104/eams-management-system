#pragma once
#ifndef _SIGNDTO_H_
#define _SIGNDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 签到数据传输对象
* 封装单条签到记录的核心字段
* 核心字段：id（唯一）、其他描述字段
*/
class SignDTO : public oatpp::DTO
{
	DTO_INIT(SignDTO, DTO);
	//API_DTO_FIELD_DEFAULT(UInt64, stu_id, ZH_WORDS_GETTER("sign.field.stu-id"));
	API_DTO_FIELD_REQUIRE(String, stu_name, ZH_WORDS_GETTER("sign.field.stu-name"), true);
	API_DTO_FIELD_REQUIRE(String, sign, ZH_WORDS_GETTER("sign.field.stu-sign"), true);
	API_DTO_FIELD_REQUIRE(String, date, ZH_WORDS_GETTER("sign.field.date"), true);
};


/*
* 签到分页数据传输对象
* 封装签到记录的分页结果
* PageDTO的核心分页信息(total, page[当前页码], pageSize)、List<SignDTO::Wrapper>（当前页的签到记录列表）
*/
class SignPageDTO : public PageDTO<SignDTO::Wrapper>
{
	DTO_INIT(SignPageDTO, PageDTO<SignDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SIGNDTO_H_

