#pragma once
#ifndef _INTENDEDSTUDENT_QUERY_
#define _INTENDEDSTUDENT_QUERY_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Excel 导出查询对象
 * stage: 0 意向成员
 */
class IntendExcelQuery : public oatpp::DTO
{
	DTO_INIT(IntendExcelQuery, DTO);

	// 状态
	DTO_FIELD(UInt8, stage);
	DTO_FIELD_INFO(stage) {
		info->description = ZH_WORDS_GETTER("onlinestudent.field.student.stage");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif