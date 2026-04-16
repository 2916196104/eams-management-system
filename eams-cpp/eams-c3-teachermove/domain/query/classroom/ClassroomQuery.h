#pragma once
#ifndef _CLASSROOM_QUERY_H_
#define _CLASSROOM_QUERY_H_

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 教室分页查询对象
 */
class ClassroomQuery : public PageQuery
{
	DTO_INIT(ClassroomQuery, PageQuery);

	// 教室名称（模糊查询）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("classroom.field.name");
	}

	// 教室地址（模糊查询）
	DTO_FIELD(String, address);
	DTO_FIELD_INFO(address) {
		info->description = ZH_WORDS_GETTER("classroom.field.address");
	}

	// 学校ID（精确查询）
	DTO_FIELD(String, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("classroom.field.school_id");
	}

	// 组织ID（精确查询）
	DTO_FIELD(String, org_id);
	DTO_FIELD_INFO(org_id) {
		info->description = ZH_WORDS_GETTER("classroom.field.org_id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASSROOM_QUERY_H_
