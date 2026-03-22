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

	return pages;
}
