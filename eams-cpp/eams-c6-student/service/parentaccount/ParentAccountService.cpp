#include "stdafx.h"
#include "ParentAccountService.h"

ParentAccountPageDTO ParentAccountService::listParentAccount(const ParentAccountQuery::Wrapper& query)
{
	auto pages = ParentAccountPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	uint64_t count = m_parentAccountDAO.countParentAccount(query);
	if (count == 0) {
		return pages;
	}

	auto list = m_parentAccountDAO.listParentAccount(query);
	for (const auto& item : list) {
		auto dto = ParentAccountDTO::createShared();
		
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, item, userId, UserId, mobile, Mobile, name, Name, studentName, StudentName, wxName, WxName, loginTimes, LoginTimes, latestLoginTime, LatestLoginTime, latestLoginIp, LatestLoginIp,addTime, AddTime, state, State);
	}
    return pages;
}
