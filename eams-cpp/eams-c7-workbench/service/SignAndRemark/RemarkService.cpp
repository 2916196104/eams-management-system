#include "stdafx.h"
#include "RemarkService.h"
#include "dao/SignAndRemark/RemarkDAO.h"

RemarkPageDTO::Wrapper RemarkService::listAll(const RemarkQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = RemarkPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	RemarkDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取分页数据
	auto list = ud.selectAll(query);
	for (auto one : list)
	{
		auto user = RemarkDTO::createShared();
		//将DO的对应字段返回给DTO
		ZO_STAR_DOMAIN_DO_TO_DTO_1(user, one, remark,Remark,score,Score,remark_time,Remark_time,stu_name,Stu_name,teacher_name,Teacher_name);
		page->addData(user);
	}
	return page;
}