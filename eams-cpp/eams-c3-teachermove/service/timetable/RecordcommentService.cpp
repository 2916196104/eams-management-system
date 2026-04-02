#include "stdafx.h"
#include "RecordcommentService.h"
#include "dao/lesson/LessonStudentDao.h"
#include "dao/timetable/GetEvaluation/GetCourseEvaluationDAO.h"
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



EvaluateRspJsonVO::Wrapper RecordcommentService::modifyEvaluation(const EvaluationDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = EvaluateRspJsonVO::createShared();
	auto rsp = EvaluateRspDTO::createShared();

	if (!dto || !dto->id || !dto->score)
	{
		rsp->id = dto && dto->id ? dto->id : "";
		rsp->code = static_cast<v_int8>(1);
		rsp->message = "paramInvalid";
		jvo->init(rsp, RS_PARAMS_INVALID);
		return jvo;
	}

	uint64_t lessonStudentId = 0;
	int64_t teacherId = 0;
	try
	{
		lessonStudentId = static_cast<uint64_t>(std::stoull(dto->id.getValue("0")));
		if (!payload.getId().empty())
		{
			teacherId = std::stoll(payload.getId());
		}
	}
	catch (...)
	{
		rsp->id = dto->id;
		rsp->code = static_cast<v_int8>(1);
		rsp->message = "idInvalid";
		jvo->init(rsp, RS_PARAMS_INVALID);
		return jvo;
	}

	LessonStudentDao dao;
	const auto affected = dao.UpdateEvaluation(
		lessonStudentId,
		static_cast<int32_t>(dto->score.getValue(0)),
		dto->evaluation ? dto->evaluation.getValue("") : std::string(),
		teacherId);

	rsp->id = dto->id;
	if (affected > 0)
	{
		rsp->code = static_cast<v_int8>(0);
		rsp->message = "success";
		jvo->success(rsp);
	}
	else
	{
		rsp->code = static_cast<v_int8>(1);
		rsp->message = "updateFailed";
		jvo->fail(rsp);
	}

	return jvo;
}



EvaluatePageJsonVO::Wrapper RecordcommentService::queryEvaluation(const EvaluationQuery::Wrapper& query)
{
	auto jvo = EvaluatePageJsonVO::createShared();
	auto page = EvaluatePageDTO::createShared();

	const auto pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : 1;
	const auto pageSize = query && query->pageSize ? query->pageSize.getValue(10) : 10;

	page->pageIndex = pageIndex == 0 ? 1 : pageIndex;
	page->pageSize = pageSize == 0 ? 10 : pageSize;

	if (!query || !query->lesson_id)
	{
		jvo->init(page, RS_PARAMS_INVALID);
		return jvo;
	}

	GetCourseEvaluation dao;
	auto total = static_cast<v_int64>(dao.count(query));
	page->total = total;
	page->calcPages();

	if (total > 0)
	{
		auto rows = dao.selectWithPage(query);
		for (const auto& one : rows)
		{
			auto dto = EvaluateDTO::createShared();
			dto->id = one->getId();
			dto->name = one->getStudentName();
			dto->score = static_cast<v_int8>(one->getScore());
			dto->isSign = one->getSign() != 0;
			dto->evaluation = one->getEvaluation();
			dto->Operator = one->getTeacherName();
			dto->operationTime = one->getTime();
			page->addData(dto);
		}
	}

	jvo->success(page);
	return jvo;
}
