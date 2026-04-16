#pragma once
#pragma once
#ifndef _REMARKDTO_H_
#define _REMARKDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 点评数据传输对象
* 封装单条点评记录的核心字段
* 核心字段：id（唯一）、其他描述字段
*/
class RemarkDTO : public oatpp::DTO
{
	DTO_INIT(RemarkDTO, DTO);
	//API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("remark.field.stu-id"));
	API_DTO_FIELD_REQUIRE(String, stu_name, ZH_WORDS_GETTER("remark.field.stu-name"), true);
	API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("remark.field.remark"), true);
	API_DTO_FIELD_REQUIRE(UInt64, score, ZH_WORDS_GETTER("remark.field.score"), true);
	API_DTO_FIELD_REQUIRE(String, teacher_name, ZH_WORDS_GETTER("remark.field.teacher-name"), true);
	API_DTO_FIELD_REQUIRE(String, remark_time, ZH_WORDS_GETTER("remark.field.remark-time"), true);
};


/*
* 点评分页数据传输对象
* 封装点评记录的分页结果
* PageDTO的核心分页信息(total, page[当前页码], pageSize)、List<SignDTO::Wrapper>（当前页的签到记录列表）
*/
class RemarkPageDTO : public PageDTO<RemarkDTO::Wrapper>
{
	DTO_INIT(RemarkPageDTO, PageDTO<RemarkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_REMARKDTO_H_

