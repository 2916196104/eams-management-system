#pragma once
#include "domain/dto/manual/ManualDTO.h"
#include "domain/query/PageQuery.h"

//调用dao查数据库
//do转换为dto

class UsageGuideService
{
public:
	//查询数据库，将所有列表信息封装为dto返回
	UsageListDTO::Wrapper listAll(const ListQuery::Wrapper& query);

	//查询数据库，将某一详细信息封装为dto返回
	UsageGuideDetailDto::Wrapper getById(std::string id);
};
