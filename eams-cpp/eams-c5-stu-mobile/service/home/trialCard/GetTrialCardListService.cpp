#include "stdafx.h"
#include "GetTrialCardListService.h"
#include "dao/home/trialCard/GetTrialCardListDAO.h"
#include "domain/dto/home/trialCard/GetTrialCardListDTO.h"

GetTrialCardListPageDTO::Wrapper GetTrialCardListService::listAll(const GetTrialCardListQuery::Wrapper& query)
{
	auto pages = GetTrialCardListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	GetTrialCardListDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<GetTrialCardListDO> res = dao.selectWithPage(query);
	// DO -> DTO
	for (auto& sub : res)
	{
		auto dto = GetTrialCardListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, name,Name,courseName,CourseName, lessonCount,LessonCount,remainingQuantity,RemainingQuantity, endTime, EndTime);
		pages->addData(dto);
	}

	return pages;
}