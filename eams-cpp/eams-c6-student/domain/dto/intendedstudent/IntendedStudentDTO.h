#pragma once

#ifndef _INTENDEDSTUDENT_DTO_
#define _INTENDEDSTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 新增数据传输对象
 */
class AddDTO : public oatpp::DTO
{
	DTO_INIT(AddDTO, DTO);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("common.field.student.name");
	}
	// 年龄
	DTO_FIELD(Int32, age);
	DTO_FIELD_INFO(age) {
		info->description = ZH_WORDS_GETTER("common.field.student.age");
	}
	// 性别
	DTO_FIELD(String, sex);
	DTO_FIELD_INFO(sex) {
		info->description = ZH_WORDS_GETTER("common.field.student.sex");
	}

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		if (!age || age < 0)
			return "age invalidate.";
		if (!name || name->empty())
			return "name invalidate.";
		if (!sex || sex->empty())
			return "sex invalidate.";
		return "";
	}
};

/**
 * 导入数据传输对象
 */
class ImportDTO : public oatpp::DTO
{
	DTO_INIT(ImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, "excel", true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_