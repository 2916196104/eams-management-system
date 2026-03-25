
#include "stdafx.h"
#include "HomeworkService.h"
#include "../../dao/homework/HomeworkRecordDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

GetHomeworkListPageDTO::Wrapper HomeworkService::gethomeworklist(const GetHomeworkListQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = GetHomeworkListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HomeworkRecordDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<HomeworkDO> result = dao.gethomeworklist(query);
	// 将DO转换成DTO
	for (HomeworkDO& sub : result)
	{
		auto dto = GetHomeworkListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);
		pages->addData(dto);
	}
	return pages;
	//return{};
}

GetHomeworkDetailDTO::Wrapper HomeworkService::gethomeworkdetail(std::string id)
{
	return {};
}

std::string HomeworkService::saveHomework(const SaveHomeworkDTO::Wrapper& dto)
{
    
	return {};
}
