#pragma once
#ifndef _GETTRIALCARDLIST_SERVICE_H_
#define _GETTRIALCARDLIST_SERVICE_H_

#include "domain/vo/home/trialCard/GetTrialCardListVO.h"
#include "domain/query/home/trialCard/GetTrialCardListQuery.h"

class GetTrialCardListService
{
public:
	// 分页查询所有数据
	GetTrialCardListPageDTO::Wrapper listAll(const GetTrialCardListQuery::Wrapper& query);
};

#endif // !_GETTRIALCARDLIST_SERVICE_H_
