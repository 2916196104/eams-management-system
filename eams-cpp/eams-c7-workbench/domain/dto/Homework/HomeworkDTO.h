#pragma once
#ifndef _HOMEWORKDTO_H_
#define _HOMEWORKDTO_H_

#include "../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 作业数据传输对象
* 封装单条作业记录的核心字段
* 核心字段：id（唯一）、其他描述字段
*/
class HomeworkDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkDTO, DTO);
	API_DTO_FIELD_REQUIRE(String, coursename, ZH_WORDS_GETTER("c7.field.course-name"), true);
	API_DTO_FIELD_REQUIRE(String, classname, ZH_WORDS_GETTER("c7.field.class-name"), true);
	API_DTO_FIELD_REQUIRE(String, wkname, ZH_WORDS_GETTER("c7.field.wk-name"), true);
	API_DTO_FIELD_REQUIRE(String, commitcnt, ZH_WORDS_GETTER("c7.field.wk-commit-count"), true);
};

/*
* 作业分页数据传输对象
* 封装作业记录的分页结果
* PageDTO的核心分页信息(total, page[当前页码], pageSize)、List<SignDTO::Wrapper>（当前页的签到记录列表）
*/
class HomeworkPageDTO : public PageDTO<HomeworkDTO::Wrapper>
{
	DTO_INIT(HomeworkPageDTO, PageDTO<HomeworkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKDTO_H_
