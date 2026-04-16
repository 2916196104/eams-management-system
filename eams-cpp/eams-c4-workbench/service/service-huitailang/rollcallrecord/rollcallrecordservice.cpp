#include "stdafx.h"
#include "rollcallrecordservice.h"
#include "../../../dao/dao-huitailang/rollcallrecord/rollcallrecordDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"



rollcallPageDTO::Wrapper RollcallrecordService::listAll(const RollcallQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = rollcallPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	RollcallrecordDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<RollcallrecordViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (RollcallrecordViewDO& sub : result)
	{
		auto dto = rollcallDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, studentName, StudentName, checkinDate, Sign_time, checkinResult, Sign_state);
		
		pages->addData(dto);
	}
	return pages;
}

