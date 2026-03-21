#pragma once
#ifndef _PAGE_QUERY_
#define _PAGE_QUERY_
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "../lib-oatpp/include/ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 分页查询对象父类，后续分页查询对象可以继承它
 */
class PageQuery : public oatpp::DTO {
	DTO_INIT(PageQuery, DTO);
	// 页码，默认第1页
	API_DTO_FIELD(UInt64, pageIndex, "pageIndex", false, 1);
	// 每页条数，默认10条
	API_DTO_FIELD(UInt64, pageSize, "pageSize", false, 10);
};


// 继承自PageQuery，自动包含分页字段
class ListQuery : public PageQuery {
	DTO_INIT(ListQuery, PageQuery);
	// 查询条件
	/*API_DTO_FIELD_DEFAULT(Int32, pageIndex, "pageIndex");
	API_DTO_FIELD_DEFAULT(Int32, pageSize, "pageSize");*/
};


class DetailQuery : public PageQuery {
	DTO_INIT(DetailQuery, PageQuery);
	// 查询条件
	/*API_DTO_FIELD_DEFAULT(Int32, pageIndex, "pageIndex");
	API_DTO_FIELD_DEFAULT(Int32, pageSize, "pageSize");*/
	API_DTO_FIELD_DEFAULT(Int32, id, "id");
	API_DTO_FIELD_DEFAULT(String, title, "title");
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_PAGE_QUERY_
