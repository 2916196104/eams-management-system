

#include "stdafx.h"
#include "StclassRecordService.h"
#include "../eams-c7-workbench/dao/StudentRecord/StclassRecordDAO.h"

StclassRecordPageDTO::Wrapper StclassRecordService::listAll(const StlistQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = StclassRecordPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	StclassRecordDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<StclassRecordViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (StclassRecordViewDO& sub : result)
	{
		auto dto = StclassRecordDTO::createShared();
		// 课程信息与状态字段
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title, state, State, signType, SignType, startTime, StartTime);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, endTime, EndTime);
		pages->addData(dto);
	}
	return pages;
}