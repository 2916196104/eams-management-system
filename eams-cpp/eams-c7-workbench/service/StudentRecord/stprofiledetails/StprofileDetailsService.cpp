
#include "stdafx.h"
#include "StprofileDetailsService.h"
#include "../eams-c7-workbench/dao/StudentRecord/StprofileDetailsDAO.h"


StprofileDetailsPageDTO::Wrapper StprofileDetailsService::listAll(const StlistQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = StprofileDetailsPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	StprofileDetailsDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<StprofileDetailsViewDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (StprofileDetailsViewDO& sub : result)
	{
		auto dto = StprofileDetailsDTO::createShared();
		// 学生基本信息字段
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, name, Name, mobile, Mobile, closeTime, CloseTime, credit, Credit);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, lessonCount, LessonCount, stage, Stage, familyName, FamilyName, familyRel, FamilyRel);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, className, ClassName, gender, Gender, birthday, Birthday, idcard, Idcard);
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, joinDate, JoinDate, addTime, AddTime, grade, Grade);
		pages->addData(dto);
	}
	return pages;
}