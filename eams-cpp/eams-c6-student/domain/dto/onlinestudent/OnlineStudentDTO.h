#pragma once
#ifndef _ONLINESTUDENT_DTO_
#define _ONLINESTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 导入数据传输对象
 */
class OnelineImportDTO : public oatpp::DTO
{
	DTO_INIT(OnelineImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, "excel", true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SAMPLE_DTO_