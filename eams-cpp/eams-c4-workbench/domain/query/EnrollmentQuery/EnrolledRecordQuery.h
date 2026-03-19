#pragma once
#ifndef _ENROLLEDRECORD_QUERY_
#define _ENROLLEDRECORD_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 报名记录分页查询对象
 */
class EnrolledQuery : public PageQuery
{
	DTO_INIT(EnrolledQuery, PageQuery);
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("sample.field.name");
	}
	
};
/*
 * 报名记录详情查询对象
 */
class EnrolledDetailQuery : public EnrolledQuery
{
	DTO_INIT(EnrolledDetailQuery, EnrolledQuery);
	// 其他报名记录详情查询字段
};
#endif // !_ENROLLEDRECORD_QUERY_
