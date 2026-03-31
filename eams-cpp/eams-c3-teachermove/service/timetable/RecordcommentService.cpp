#include "stdafx.h"
#include "RecordcommentService.h"
#include "dao/lesson/LessonStudentDao.h"
#include "dao/student/StudentDao.h"
#include "dao/staff/StaffDao.h"

EvaluatePageDTO::Wrapper RecordCommentService::getEvaluationList(const EvaluationQuery::Wrapper& query)
{
	auto page = EvaluatePageDTO::createShared();
	page->pageIndex = query && query->pageIndex ? query->pageIndex : oatpp::UInt64(static_cast<v_uint64>(1));
	page->pageSize = query && query->pageSize ? query->pageSize : oatpp::UInt64(static_cast<v_uint64>(10));

	if (!query || !query->lesson_id || query->lesson_id.getValue(0) <= 0)
	{
		// page->total = 0;
		page->calcPages();
		return page;
	}

	const int64_t lessonId = static_cast<int64_t>(query->lesson_id.getValue(0));

	LessonStudentDao lessonStudentDao;
	StudentDAO studentDao;
	StaffDao staffDao;

	const uint64_t total = lessonStudentDao.CountEvaluation(lessonId, query);
	page->total = static_cast<v_int64>(total);
	page->calcPages();

	if (total == 0)
	{
		return page;
	}

	const auto rows = lessonStudentDao.SelectEvaluationWithPage(lessonId, query);

	for (const auto& ls : rows)
	{
		auto dto = EvaluateDTO::createShared();
		dto->id = std::to_string(ls->getId());

		StudentDO stu = studentDao.selectById(std::to_string(ls->getStudentId()));
		dto->name = stu.getName();

		dto->score = static_cast<v_int8>(ls->getScore());
		dto->sign_state = std::to_string(ls->getSignState());
		dto->evaluation = ls->getEvaluation();

		std::string operatorName;
		int64_t tid = ls->getEvaluateTeacher();
		if (tid <= 0)
		{
			tid = ls->getTeacherId();
		}
		if (tid > 0)
		{
			PtrStaffDO staff = staffDao.selectById(static_cast<uint64_t>(tid));
			if (staff)
			{
				operatorName = staff->getName();
			}
		}
		dto->Operator = operatorName;
		dto->operationTime = ls->getEvaluateTime();

		page->addData(dto);
	}

	return page;
}
