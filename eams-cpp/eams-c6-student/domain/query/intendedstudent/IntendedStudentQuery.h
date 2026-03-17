#pragma once
#ifndef _INTENDEDSTUDENT_QUERY_
#define _INTENDEDSTUDENT_QUERY_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Excel 导出查询对象
 */
class IntendExcelQuery : public oatpp::DTO
{
	DTO_INIT(IntendExcelQuery, DTO);

	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("common.field.student.name");
	}

	// 性别
	DTO_FIELD(String, sex);
	DTO_FIELD_INFO(sex) {
		info->description = ZH_WORDS_GETTER("common.field.student.sex");
	}

	// 年龄
	DTO_FIELD(UInt32, age);
	DTO_FIELD_INFO(age) {
		info->description = ZH_WORDS_GETTER("common.field.student.age");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif