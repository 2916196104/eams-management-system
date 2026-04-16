
#include "stdafx.h"
#include "StlistService.h"
#include "../eams-c7-workbench/dao/StudentRecord/StlistDAO.h"

StlistPageDTO::Wrapper StlistService::listAll(const StlistQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = StlistPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	StlistDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<StlistViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (StlistViewDO& sub : result)
	{
		auto dto = StlistDTO::createShared();
		// 如果 DO 字段是首字母大写
		// 学生基本信息字段
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, name, Name, mobile, Mobile, closeTime, CloseTime);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, gender, Gender);
		pages->addData(dto);
	}
	return pages;
}
