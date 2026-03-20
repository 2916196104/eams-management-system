#pragma once
#include "../../GlobalInclude.h"

#ifndef _STUDENTINFORMATION_H_
#define __STUDENTINFORMATION_H_

#include OATPP_CODEGEN_BEGIN(DTO)

/**
* 定义接收学生学号姓名数据类型
*/
class StudentQuery : public DTO
{
	DTO_INIT(StudentQuery, DTO);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("student.field.name");
	}
	// 性别
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("student.field.id");
	}
	
};

#include OATPP_CODEGEN_END(DTO)
#endif