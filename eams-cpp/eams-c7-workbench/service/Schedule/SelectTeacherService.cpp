#include "stdafx.h"
#include "SelectTeacherService.h"

SelectTeacherPageDTO::Wrapper SelectTeacherService::listAll(const SelectTeacherQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = SelectTeacherPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	SelectTeacherDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<SelectTeacherViewDOPtr> list = dao.selectWithPage(query, pages->pageIndex, pages->pageSize);
	for (auto one : list)
	{
		auto dto = SelectTeacherDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, one,
			id, Id,
			name, Name
		);

		pages->addData(dto);
	}
	return pages;
}