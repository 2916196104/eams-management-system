#include "stdafx.h"
#include "SignService.h"
#include "dao/SignAndRemark/SignDAO.h"

SignPageDTO::Wrapper SignService::listAll(const SignQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = SignPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	SignDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取分页数据
	auto list = ud.selectAll(query);
	for (auto one : list)
	{
		auto user = SignDTO::createShared();
		//将DO的对应字段返回给DTO
		ZO_STAR_DOMAIN_DO_TO_DTO_1(user, one,  sign, Sign, date, Date, stu_name, Stu_name);
		page->addData(user);
	}
	return page;
}