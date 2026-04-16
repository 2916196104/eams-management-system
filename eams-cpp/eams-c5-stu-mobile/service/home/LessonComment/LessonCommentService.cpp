#include "stdafx.h"
#include "LessonCommentService.h"
#include "dao/home/LessonComment/LessonCommentDAO.h"
#include<iostream>



LessonCommentPageDTO::Wrapper LessonCommentService::listAll(const LessonCommentQuery::Wrapper& query)
{
	auto pages = LessonCommentPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	LessonCommentDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	std::cout << count << std::endl;
	pages->calcPages();
	list<LessonCommentDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (LessonCommentDO& sub : result)
	{
		auto dto = LessonCommentDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,
			lesson_id, LessonId,
			class_id, ClassId,
			student_id, StudentId,
			dec_lesson_count, DecLessonCount,
			lesson_count, LessonCount,
			teacher_id, TeacherId,
			sign_time, SignTime,
			sign_type, SignType,
			sign_state, SignState,
			score, Score,
			evaluation, Evaluation,
			evaluate_time, EvaluateTime,
			evaluate_teacher_id, EvaluateTeacherId,
			evaluate_teacher, EvaluateTeacher,
			consume_course_id, ConsumeCourseId,
			consume_student_course_id, ConsumeStudentCourseId,
			counselor, Counselor,
			add_time, AddTime,
			org_id, OrgId
		);
		pages->addData(dto);
	}
	return pages;
}