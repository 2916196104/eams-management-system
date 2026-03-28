#include "stdafx.h"      
#include "StuJudgeTeaService.h"
#include "dao/StuJudgeTea/TeachEvaluationDao.h"

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
	list<PtrStuJudgeTeaDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (PtrStuJudgeTeaDO& sub : result)
	{
		auto dto = StuJudgeTeaDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, sub, id, Id, lessonId, LessonId,teacherId, TeacherId, comprehensiveScore, Score1, classAtmosphere, Score2, teachingAttitude, Score3, teachingEffect, Score4, evaluateContent, Content, evaluateTime, AddTime, studentId, StudentId, anonymity, Anonymity, orgId, OrgId);
		if (sub->getLesson())
		{
			dto->lessonTitle = sub->getLesson()->getTitle();
		}
		if (sub->getOrg())
		{
			dto->orgName = sub->getOrg()->getName();
		}
		if (sub->getStaff())
		{
			dto->teacherName = sub->getStaff()->getName();
		}
		if (sub->getUser())
		{
			dto->studentName = sub->getUser()->getName();
		}
		pages->addData(dto);
	}
	return pages;
}