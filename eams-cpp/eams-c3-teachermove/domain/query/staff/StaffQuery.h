#pragma once
#ifndef _STAFF_QUERY_H_
#define _STAFF_QUERY_H_

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 员工分页查询对象
 */
class StaffQuery : public PageQuery
{
	DTO_INIT(StaffQuery, PageQuery);

	// 姓名（模糊查询）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("staff.field.name");
	}

	// 手机号（精确查询）
	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile) {
		info->description = ZH_WORDS_GETTER("staff.field.mobile");
	}

	// 状态（精确查询）
	DTO_FIELD(String, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("staff.field.state");
	}

	// 是否负责人（精确查询）
	DTO_FIELD(String, is_manager);
	DTO_FIELD_INFO(is_manager) {
		info->description = ZH_WORDS_GETTER("staff.field.is_manager");
	}

	// 组织ID（精确查询）
	DTO_FIELD(String, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("staff.field.org_id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_STAFF_QUERY_H_
