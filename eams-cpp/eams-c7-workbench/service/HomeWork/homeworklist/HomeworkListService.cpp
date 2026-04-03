

#include "stdafx.h"
#include "HomeworkListService.h"
#include "dao/Homework/homeworklist/HomeworkListDAO.h"

HomeworkListPageDTO::Wrapper HomeworkListService::listAll(const HomeworkListQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = HomeworkListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HomeworkListDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<HomeworkListViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (HomeworkListViewDO& sub : result)
	{
		auto dto = HomeworkListDTO::createShared();
		// 课程信息与状态字段
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title, number, Number, className, ClassName);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, courseName, CourseName);
		pages->addData(dto);
	}
	return pages;
}