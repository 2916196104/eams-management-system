#pragma once
#ifndef _STUDENT_QUERY_
#define _STUDENT_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学生分页查询对象
 */
class StudentQuery : public PageQuery
{
	DTO_INIT(StudentQuery, PageQuery);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("student.field.name");
	}
	// 阶段（意向、在学、结业）
	DTO_FIELD(Int8, stage);
	DTO_FIELD_INFO(stage) {
		info->description = ZH_WORDS_GETTER("student.field.stage");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_QUERY_