#pragma once
#ifndef _HOMEWORKQUERY_H_
#define _HOMEWORKQUERY_H_

#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"


#include OATPP_CODEGEN_BEGIN(DTO)

/*
* 作业查询类
* 封装查询条件：支持分页和过滤
* 核心字段：分页参数、查询参数
* 接收前端传递的查询参数，并将其传递给服务层或数据库层
*/
class HomeworkQuery :public PageQuery
{
	DTO_INIT(HomeworkQuery, PageQuery);
	API_DTO_FIELD_REQUIRE(String, coursename, ZH_WORDS_GETTER("c7.course-name"), true);
	API_DTO_FIELD_REQUIRE(String, classname, ZH_WORDS_GETTER("c7.class-name"), true);
	API_DTO_FIELD_REQUIRE(String, wkname, ZH_WORDS_GETTER("c7.wk-name"), true);
	API_DTO_FIELD_REQUIRE(String, dateTime, ZH_WORDS_GETTER("c7.field.wk-commit-count"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKQUERY_H_
