#pragma once


#ifndef _STUDENTQUERY_H_
#define _STUDENTQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户列表信息的数据传输模型 因为接口文档暂无参数所以没写参数
 */
class StudentQuery : public PageQuery {
	DTO_INIT(StudentQuery, PageQuery);

	// 继承 PageQuery，自动包含 pageIndex、pageSize 字段

};

#include OATPP_CODEGEN_END(DTO)
#endif   


 