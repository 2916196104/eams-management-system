#pragma once
#ifndef _GETTRIALCARDLISTDO_H_
#define _GETTRIALCARDLISTDO_H_

#include "BaseDAO.h"
#include "domain/do/home/trialCard/GetTrialCardListDO.h"
#include "domain/query/home/trialCard/GetTrialCardListQuery.h"

class GetTrialCardListDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const GetTrialCardListQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const GetTrialCardListQuery::Wrapper& query);
	// 分页查询数据
	std::list<GetTrialCardListDO> selectWithPage(const GetTrialCardListQuery::Wrapper& query);
	//// 通过ID查询数据
	//PtrGetTrialCardListDO selectById(std::string id);
};
#endif // _GETTRIALCARDLISTDO_H_