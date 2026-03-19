#pragma once

#ifndef _REGISTER_QEURY_H_
#define _REGISTER_QEURY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 注册查询对象
 */
class RegisterQuery : public PageQuery
{
	DTO_INIT(RegisterQuery, PageQuery);
	// id
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("c5.register.field.id");
	}
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("c5.register.field.name.info");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_REGISTER_QEURY_H_