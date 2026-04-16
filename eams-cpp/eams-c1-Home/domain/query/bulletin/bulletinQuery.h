#pragma once
#ifndef _BULLETINQUERY_H_
#define _BULLETINQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义查询类
 */
class listQuery : public PageQuery
{
	DTO_INIT(listQuery, PageQuery);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_BULLETINQUERY_H_