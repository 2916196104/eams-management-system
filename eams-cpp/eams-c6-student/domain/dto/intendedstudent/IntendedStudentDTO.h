#pragma once

#ifndef _INTENDEDSTUDENT_DTO_
#define _INTENDEDSTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 导入数据传输对象
 */
class SampleImportDTO : public oatpp::DTO
{
	DTO_INIT(SampleImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("sample.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_