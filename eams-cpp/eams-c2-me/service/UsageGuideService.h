#pragma once
#include "domain/dto/parent/ParentDTO.h"
#include "domain/query/PageQuery.h"

class UsageGuideService
{
public:
	UsageListDTO::Wrapper UsageGuideService::listAll(const ListQuery::Wrapper& query);
	UsageGuideDetailDto::Wrapper UsageGuideService::getById(std::string id);
};
//调用dao查数据库
//do转换为dto