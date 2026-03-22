#include "stdafx.h"
#include "CourseEvaluateService.h"
#include "../../dao/CourseEvaluate/CourseEvaluateDAO.h"
#include "SimpleDateTimeFormat.h"

CourseEvaluatePageDTO::Wrapper CourseEvaluateService::listAll(const CourseEvaluateQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = CourseEvaluatePageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	CourseEvaluateDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<CourseEvaluateDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	for (CourseEvaluateDO& sub : result)
	{
		auto dto = CourseEvaluateDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,
			course_id, CourseId,
			student_id, StudentId,
			order_id, OrderId,
			content, Content,
			score, Score,
			state, State,
			creator, Creator,
			editor, Editor,
			add_time, AddTime,
			edit_time, EditTime,
			deleted, Deleted);
		pages->addData(dto);
	}
	return pages;
}

uint64_t CourseEvaluateService::saveData(const CourseEvaluateDTO::Wrapper& dto)
{
	// 组装DO数据
	CourseEvaluateDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,
		CourseId, course_id,
		StudentId, student_id,
		OrderId, order_id,
		Content, content,
		Score, score);
	// 设置默认值
	data.setState(0);
	data.setDeleted(0);
	data.setAddTime(SimpleDateTimeFormat::format());
	// 设置创建人
	if (dto->getPayload())
		data.setCreator(dto->getPayload()->getId());
	// 执行数据添加
	CourseEvaluateDAO dao;
	return dao.insert(data);
}
