#pragma once
#ifndef COMMOMQUERY_H
#define COMMONQUERY_H
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class RegistrationPageQuery :public PageQuery {
	DTO_INIT(RegistrationPageQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("common.field.student.id"));
};

/**
 * 示例分页查询对象
 */
class FollowUprecordsQuery : public PageQuery
{
	DTO_INIT(FollowUprecordsQuery, PageQuery);


	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	// 跟进阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	// 跟进人
	API_DTO_FIELD_DEFAULT(String, follow_up_person, ZH_WORDS_GETTER("common.field.student.follow-up-person"));
	//开始日期
	API_DTO_FIELD_DEFAULT(String, startdate, ZH_WORDS_GETTER("common.field.student.startdate"));
	//结束日期
	API_DTO_FIELD_DEFAULT(String, enddate, ZH_WORDS_GETTER("common.field.student.enddate"));

	
};

#include OATPP_CODEGEN_END(DTO)
#endif