#include "stdafx.h"
#include "ClassroomService.h"
#include "dao/Schedule/ClassroomDAO.h"

ClassroomPageDTO::Wrapper ClassroomService::listAll(const ClassroomQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = ClassroomPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	ClassroomDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取分页数据
	auto list = ud.selectAll(query);
	for (auto one : list)
	{
		auto user = ClassroomDTO::createShared();
		//将DO的对应字段返回给DTO
		ZO_STAR_DOMAIN_DO_TO_DTO_1(user, one, name, ClsName, address, ClsAddress);
		page->addData(user);
	}
	return page;
}