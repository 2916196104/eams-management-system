#pragma once


#ifndef _STUDENTQUERY_H_
#define _STUDENTQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户信息的数据传输模型
 */
class UserQuery : public PageQuery {
	DTO_INIT(UserQuery, PageQuery);

};

#include OATPP_CODEGEN_END(DTO)
#endif   


 