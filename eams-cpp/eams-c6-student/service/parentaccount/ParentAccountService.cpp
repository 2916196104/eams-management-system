#include "stdafx.h"
#include "ParentAccountService.h"
//ParentAccountPageDTO is wrapped
ParentAccountPageDTO ParentAccountService::listParentAccount(const ParentAccountQuery::Wrapper& query)
{
	auto pages = ParentAccountPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	uint64_t count = m_parentAccountDAO.countParentAccount(query);
	if (count == 0) {
		return pages;
	}
	list<ParentAccountQueryDO>datas = m_parentAccountDAO.listParentAccount(query);
	for (auto& data : datas) {
		auto dto = ParentAccountQueryDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto,data,userId,UserId,mobile,Mobile,name,Name,studentName,StudentName,wxName,WxName);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto,data,loginTimes,LoginTimes,latestLoginTime,LatestLoginTime,latestLoginIp,LatestLoginIp,addTime,AddTime,state,State);
		pages->addData(dto);
	}
	return pages;
}
