#pragma once
#ifndef _SCHEDULE_QUERY_H_
#define _SCHEDULE_QUERY_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课表列表查询参数
 */
class ScheduleQuery : public oatpp::DTO
{
	DTO_INIT(ScheduleQuery, DTO);

	// 查询日期
	API_DTO_FIELD_DEFAULT(String, queryDate, ZH_WORDS_GETTER("schedule.field.queryDate"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_SCHEDULE_QUERY_H_