#pragma once
#ifndef _MONTHLYDATASERVICE_H_
#define _MONTHLYDATASERVICE_H_
#include "domain/dto/UserRelated/MonthlyDataDTO.h"
#include "domain/query/UserRelated/MonthlyDataQuery.h"
#include "domain/do/UserRelated/MonthlyDataDO.h"
#include "dao/UserRelated/MonthlyDataDAO.h"
#include "dao/UserRelated/MonthlyDataWrapper.h"
class MonthlyDataService
{
public:
	// 不分页查询所有数据
	MonthlyDataDTO::Wrapper listAll(const MonthlyDataQuery::Wrapper& query);
};
#endif