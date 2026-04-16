#include "TimetableController.h"
#include "../../service/timetable/TimetableService.h"

/**
 * 执行预约
 */
ReserveVO::Wrapper TimetableController::executeReserve(const ReserveDTO::Wrapper& dto)
{
	// 创建返回VO对象
	auto jvo = ReserveVO::createShared();

	try
	{
		// 判空校验
		if (!dto)
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 参数合法性校验
		std::string errmsg = dto->validate();
		if (!errmsg.empty())
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 调用业务层执行预约
		return TimetableService().reserveLesson(dto);
	}
	catch (...)
	{
		// 发生异常时返回失败
		jvo->fail(nullptr);
		return jvo;
	}
}

/**
 * 执行请假
 */
LeaveVO::Wrapper TimetableController::executeLeave(const LeaveDTO::Wrapper& dto)
{
	auto jvo = LeaveVO::createShared();

	// 这里先保留空实现
	jvo->success(TimetableActionResultDTO::createShared());
	return jvo;
}

/**
 * 执行按天查询课表
 */
TimetableVO::Wrapper TimetableController::executeDayQuery(const TimetableDayQuery::Wrapper& query)
{
	// 创建返回VO对象
	auto jvo = TimetableVO::createShared();

	try
	{
		// 判空校验
		if (!query)
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 参数合法性校验
		std::string errmsg = query->validate();
		if (!errmsg.empty())
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 调用业务层执行按天查询
		return TimetableService().getDayTimetable(query);
	}
	catch (...)
	{
		// 发生异常时返回失败
		jvo->fail(nullptr);
		return jvo;
	}
}

/**
 * 执行签到
 */
TimetableSignVO::Wrapper TimetableController::executeSign(const TimetableSignDTO::Wrapper& dto)
{
	// 创建返回VO对象
	auto jvo = TimetableSignVO::createShared();

	try
	{
		// 判空校验
		if (!dto)
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 参数合法性校验
		std::string errmsg = dto->validate();
		if (!errmsg.empty())
		{
			jvo->init(nullptr, RS_PARAMS_INVALID);
			return jvo;
		}

		// 调用业务层执行签到
		return TimetableService().signLesson(dto);
	}
	catch (...)
	{
		// 发生异常时返回失败
		jvo->fail(nullptr);
		return jvo;
	}
}
