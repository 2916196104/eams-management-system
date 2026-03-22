#include "stdafx.h"      
#include "StuJudgeTea.h"
#include "dao/StuJudgeTeaDao/StuJudgeTeaDao.h"

StuJudgeTeaPageDTO::Wrapper StuJudgeTeaService::listAll(const StuJudgeTeaQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = StuJudgeTeaPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	StuJudgeTeaDao dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<StuJudgeTeaDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (StuJudgeTeaDO& sub : result)
	{
		auto dto = StuJudgeTeaDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, lessonId, LessonId, teacherId, TeacherId, comprehensiveScore, Score1, classAtmosphere, Score2, teachingAttitude, Score3, teachingEffect, Score4, evaluateContent,Content, evaluateTime,AddTime, studentId,StudentId, anonymity, Anonymity, orgId, OrgId);
		pages->addData(dto);
	}
	return pages;
}