#include "stdafx.h"
#include "GradeService.h"
#include "id/UuidFacade.h"
#include "dao/GradeDAO.h"
#include "domain/do/GradeDO.h"
#include "domain/dto/student/GradeDTO.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

GradePageDTO::Wrapper GradeService::listAllGrade(const GradeQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = GradePageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	GradeDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	//std::string urlPrefix = getDfsServerAddrssUrl();
	// 获取分页数据
	auto list = ud.selectWithPage(query);
	for (auto& one : list)
	{
		auto grade = GradeDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(grade, one, name,Name);

		page->addData(grade);
	}
	return page;
}