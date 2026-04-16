#pragma once
#ifndef _PAGE_QUERY_
#define _PAGE_QUERY_
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "../lib-oatpp/include/ApiHelper.h"
#include "ServerInfo.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 分页查询对象父类，后续分页查询对象可以继承它
 */
class PageQuery : public oatpp::DTO {
	DTO_INIT(PageQuery, DTO);
	// 页码，默认第1页
	API_DTO_FIELD(UInt64, pageIndex, ZH_WORDS_GETTER("help.pageIndex"), false, 1);
	// 每页条数，默认5条
	API_DTO_FIELD(UInt64, pageSize, ZH_WORDS_GETTER("help.pageSize"), false, 5);
};


// 继承自PageQuery，自动包含分页字段
class ListQuery : public PageQuery {
	DTO_INIT(ListQuery, PageQuery);
};

// 继承自PageQuery，自动包含分页字段
class DetailQuery : public oatpp::DTO {
	DTO_INIT(DetailQuery, DTO);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("help.id"));//加入id这个查询参数
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PAGE_QUERY_
