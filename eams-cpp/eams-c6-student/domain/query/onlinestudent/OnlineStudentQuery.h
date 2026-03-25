#pragma once
#ifndef _ONLINESTUDENT_QUERY_
#define _ONLINESTUDENT_QUERY_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Excel 导出查询对象
 * stage: 1 在线成员
 */
class OnlineExcelQuery : public oatpp::DTO
{
	DTO_INIT(OnlineExcelQuery, DTO);

	// 状态
	DTO_FIELD(UInt8, stage);
	DTO_FIELD_INFO(stage) {
		info->description = ZH_WORDS_GETTER("onlinestudent.field.student.stage");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif