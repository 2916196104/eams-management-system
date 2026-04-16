#include "stdafx.h"
#include "TimetableService.h"
#include "../../dao/timetable/TimetableDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

/**
 * 一个只有这个文件用的工具函数（获取课表功能部分）
 * 作用：从yyyy-MM-dd输入格式中安全提取year/month
 */
namespace
{
	bool parseYearMonthFromDate(const std::string& queryDate, int& year, int& month)
	{
		year = 0;
		month = 0;

		if (queryDate.size() != 10)
		{
			return false;
		}
		if (queryDate[4] != '-' || queryDate[7] != '-')
		{
			return false;
		}

		try
		{
			year = std::stoi(queryDate.substr(0, 4));
			month = std::stoi(queryDate.substr(5, 2));
		}
		catch (...)
		{
			return false;
		}

		return year > 0 && month >= 1 && month <= 12;
	}
}

/**
 * 将课程视图DO转换为课程卡片DTO
 */
oatpp::Object<TimetableCourseItemDTO> TimetableService::buildCourseItemDTO(const TimetableCourseViewDO& data)
{
	// 创建课程卡片DTO对象
	auto dto = TimetableCourseItemDTO::createShared();

	// 复制基础字段
	dto->lessonId = data.getId().c_str();
	dto->title = data.getTitle().c_str();
	dto->classId = data.getClassId().c_str();
	dto->className = data.getClassName().c_str();
	dto->roomId = data.getRoomId().c_str();
	dto->roomName = data.getClassroomName().c_str();
	dto->teacherId = data.getTeacherId().c_str();
	dto->teacherName = data.getTeacherName().c_str();
	dto->date = data.getDate().c_str();
	dto->startTime = data.getStartTime().c_str();
	dto->endTime = data.getEndTime().c_str();
	dto->remark = data.getRemark().c_str();

	// 复制课程状态字段
	dto->lessonState = data.getLessonState();
	dto->lessonStateText = data.getLessonStateText().c_str();

	// 复制签到状态字段
	dto->signState = data.getSignState();
	dto->signStateText = data.getSignStateText().c_str();

	// 复制按钮控制字段
	dto->canSign = (data.getCanSign() == 1);
	dto->canLeave = (data.getCanLeave() == 1);
	dto->canReserve = (data.getCanReserve() == 1);

	// 复制卡片动作字段
	dto->cardType = data.getCardType().c_str();
	dto->actionType = data.getActionType().c_str();
	dto->actionText = data.getActionText().c_str();

	return dto;
}

/**
 * 构建课表分组DTO
 */
oatpp::Object<TimetableSectionDTO> TimetableService::buildLessonSectionDTO(
	const oatpp::String& queryDate,
	const std::list<TimetableCourseViewDO>& datas)
{
	// 创建分组对象
	auto section = TimetableSectionDTO::createShared();

	// 设置分组标题
	section->sectionTitle = queryDate + oatpp::String(ZH_WORDS_GETTER("timetable.words.lesson-section-suffix").c_str());
	// 初始化课程列表
	section->courseList = oatpp::List<oatpp::Object<TimetableCourseItemDTO>>::createShared();
	// 设置空数据提示
	section->emptyTip = ZH_WORDS_GETTER("timetable.words.empty-lesson-section").c_str();
	// 初始化总数
	section->total = 0;

	// 遍历原始数据并转换为DTO
	for (const auto& one : datas)
	{
		section->courseList->push_back(buildCourseItemDTO(one));
	}

	// 设置总数
	section->total = (v_int32)section->courseList->size();

	// 只有空分组时才返回emptyTip空态提示，有数据时返回空字符串
	if (section->total > 0)
	{
		section->emptyTip = "";
	}
	else
	{
		section->emptyTip = ZH_WORDS_GETTER("timetable.words.empty-lesson-section").c_str();
	}

	return section;
}

/**
 * 构建预约分组DTO
 */
oatpp::Object<TimetableSectionDTO> TimetableService::buildReserveSectionDTO(
	const oatpp::String& queryDate,
	const std::list<TimetableCourseViewDO>& datas)
{
	// 创建分组对象
	auto section = TimetableSectionDTO::createShared();

	// 设置分组标题
	section->sectionTitle = queryDate + oatpp::String(ZH_WORDS_GETTER("timetable.words.reserve-section-suffix").c_str());
	// 初始化课程列表
	section->courseList = oatpp::List<oatpp::Object<TimetableCourseItemDTO>>::createShared();
	// 设置空数据提示
	section->emptyTip = ZH_WORDS_GETTER("timetable.words.empty-reserve-section").c_str();
	// 初始化总数
	section->total = 0;

	// 遍历原始数据并转换为DTO
	for (const auto& one : datas)
	{
		section->courseList->push_back(buildCourseItemDTO(one));
	}

	// 设置总数
	section->total = (v_int32)section->courseList->size();

	// 只有空分组时才返回emptyTip空态提示，有数据时返回空字符串
	if (section->total > 0)
	{
		section->emptyTip = "";
	}
	else
	{
		section->emptyTip = ZH_WORDS_GETTER("timetable.words.empty-reserve-section").c_str();
	}

	return section;
}

/**
 * 构建通用动作响应DTO
 */
oatpp::Object<TimetableActionResultDTO> TimetableService::buildActionResult(
	bool success,
	const oatpp::String& lessonId,
	const oatpp::String& actionType,
	const oatpp::String& message)
{
	// 创建响应DTO对象
	auto dto = TimetableActionResultDTO::createShared();

	// 设置是否成功
	dto->success = success;
	// 设置课次ID
	dto->lessonId = lessonId;
	// 设置动作类型
	dto->actionType = actionType;
	// 设置响应消息
	dto->message = message;
	return dto;
}

/**
 * 构建签到专用响应DTO
 */
oatpp::Object<TimetableSignResultDTO> TimetableService::buildSignResult(
	bool success,
	const oatpp::String& lessonId,
	v_int32 signType,
	v_int32 signState,
	const oatpp::String& signStateText,
	const oatpp::String& signTime,
	const oatpp::String& message)
{
	auto dto = TimetableSignResultDTO::createShared();

	dto->success = success;
	dto->lessonId = lessonId;
	dto->signType = signType;
	dto->signState = signState;
	dto->signStateText = signStateText;
	dto->signTime = signTime;
	dto->message = message;

	return dto;
}

/**
 * 按天查询课表
 */
TimetableVO::Wrapper TimetableService::getDayTimetable(const TimetableDayQuery::Wrapper& query)
{
	// 创建返回VO对象
	auto result = TimetableVO::createShared();
	// 创建返回数据DTO对象
	auto data = TimetableListDTO::createShared();

	// 设置查询日期
	data->queryDate = query->queryDate;
	// 初始化月历计数列表
	data->calendarList = oatpp::List<oatpp::Object<TimetableCalendarItemDTO>>::createShared();

	// 创建DAO对象
	TimetableDAO dao;

	// 查询当月月历计数
	std::string queryDate = query->queryDate.getValue("");
	int year = 0;
	int month = 0;

	// 只有日期格式合法时才解析年月，避免20260331这种格式导致month=33
	if (parseYearMonthFromDate(queryDate, year, month))
	{
		std::list<TimetableCalendarCountDO> countDatas =
			dao.selectCalendarCountByMonth(
				query->studentId.getValue(""),
				year,
				month);

		// 转换月历计数DTO
		for (const auto& one : countDatas)
		{
			auto item = TimetableCalendarItemDTO::createShared();
			item->date = one.getDate().c_str();
			item->count = one.getCount();
			data->calendarList->push_back(item);
		}
	}

	// 查询课表分组
	std::list<TimetableCourseViewDO> lessonDatas =
		dao.selectLessonSectionByDay(
			query->studentId.getValue(""),
			query->queryDate.getValue(""));

	// 构建课表分组
	data->lessonSection = buildLessonSectionDTO(query->queryDate, lessonDatas);

	// 查询预约分组
	if (query->includeReservable.getValue(true))
	{
		std::list<TimetableCourseViewDO> reserveDatas =
			dao.selectReserveSectionByDay(
				query->studentId.getValue(""),
				query->queryDate.getValue(""));

		data->reserveSection = buildReserveSectionDTO(query->queryDate, reserveDatas);
	}
	else
	{
		data->reserveSection = buildReserveSectionDTO(query->queryDate, std::list<TimetableCourseViewDO>());
	}

	result->success(data);
	return result;
}

/**
 * 按月查询月历统计
 */
TimetableMonthVO::Wrapper TimetableService::getMonthTimetable(const TimetableMonthQuery::Wrapper& query)
{
	// 创建返回VO对象
	auto result = TimetableMonthVO::createShared();
	// 创建返回数据DTO对象
	auto data = TimetableMonthDTO::createShared();

	// 设置年份
	data->year = query->year;
	// 设置月份
	data->month = query->month;
	// 初始化日期统计列表
	data->dateList = oatpp::List<oatpp::Object<TimetableCalendarItemDTO>>::createShared();

	// 创建DAO对象
	TimetableDAO dao;

	// 查询月历统计数据
	std::list<TimetableCalendarCountDO> countDatas =
		dao.selectCalendarCountByMonth(
			query->studentId.getValue(""),
			query->year.getValue(0),
			query->month.getValue(0));

	// 遍历统计数据并转换为DTO
	for (const auto& one : countDatas)
	{
		// 创建单日统计DTO
		auto item = TimetableCalendarItemDTO::createShared();
		// 设置日期
		item->date = one.getDate().c_str();
		// 设置当天课表数量
		item->count = one.getCount();
		// 加入列表
		data->dateList->push_back(item);
	}

	// 写入成功数据
	result->success(data);
	return result;
}

/**
 * 提交预约
 */
ReserveVO::Wrapper TimetableService::reserveLesson(const ReserveDTO::Wrapper& dto)
{
	// 创建返回VO对象
	auto result = ReserveVO::createShared();

	// 创建DAO对象
	TimetableDAO dao;

	// 查询课次是否存在
	auto lesson = dao.selectLessonById(dto->lessonId.getValue(""));
	// 课次不存在则直接返回失败
	if (!lesson)
	{
		result->success(buildActionResult(false, dto->lessonId, "reserve", ZH_WORDS_GETTER("timetable.words.lesson-not-found").c_str()));
		return result;
	}

	// 查询该学员该课次是否已经提交过预约
	uint64_t appointmentCount =
		dao.countAppointmentByLessonId(
			dto->lessonId.getValue(""),
			dto->studentId.getValue(""));

	// 已存在预约记录则不允许重复预约
	if (appointmentCount > 0)
	{
		result->success(buildActionResult(false, dto->lessonId, "reserve", ZH_WORDS_GETTER("timetable.words.reserve-duplicated").c_str()));
		return result;
	}

	// 查询该学员该课次是否存在驳回记录
	uint64_t rejectedCount =
		dao.countRejectedAppointmentByLessonId(
			dto->lessonId.getValue(""),
			dto->studentId.getValue(""));

	// 存在驳回记录则不能再次预约同班同课次
	if (rejectedCount > 0)
	{
		result->success(buildActionResult(false, dto->lessonId, "reserve", ZH_WORDS_GETTER("timetable.words.reserve-rejected").c_str()));
		return result;
	}

	// 创建预约记录DO对象
	AppointmentDO appointment;

	// 创建UUID生成器
	UuidFacade uf;

	// 设置预约记录主键
	appointment.setId(uf.genUuid());
	// 设置课次ID
	appointment.setLessonId(dto->lessonId.getValue(""));
	// 设置学员ID
	appointment.setStudentId(dto->studentId.getValue(""));
	// 设置预约时间
	appointment.setAddTime(SimpleDateTimeFormat::format());
	// 设置审核状态为待审核
	appointment.setVerifyState(1);
	// 设置课程ID
	appointment.setCourseId(lesson->getCourseId());

	// 这里先留空，后续如果补学生表查询可再完善
	appointment.setSchoolId("");
	appointment.setCounselor("");

	// 执行新增预约
	if (dao.insertAppointment(appointment) != 1)
	{
		result->success(buildActionResult(false, dto->lessonId, "reserve", ZH_WORDS_GETTER("timetable.words.reserve-submit-failed").c_str()));
		return result;
	}

	// 返回预约成功
	result->success(buildActionResult(true, dto->lessonId, "reserve", ZH_WORDS_GETTER("timetable.words.reserve-submit-success").c_str()));
	return result;
}

/**
 * 学员签到
 */
TimetableSignVO::Wrapper TimetableService::signLesson(const TimetableSignDTO::Wrapper& dto)
{
	// 创建返回VO对象
	auto result = TimetableSignVO::createShared();

	// 创建DAO对象
	TimetableDAO dao;

	// 查询课次签到记录
	auto lessonStudent = dao.selectLessonStudentByLessonId(
		dto->lessonId.getValue(""),
		dto->studentId.getValue(""));

	// 未找到签到记录则返回失败
	if (!lessonStudent)
	{
		result->success(buildSignResult(
			false,
			dto->lessonId,
			dto->signType.getValue(2),
			0,
			"",
			"",
			ZH_WORDS_GETTER("timetable.words.sign-record-not-found").c_str()
		));
		return result;
	}

	// 创建更新DO对象
	LessonStudentDO updateData;

	// 设置主键
	updateData.setId(lessonStudent->getId());
	// 设置签到状态为已签到
	updateData.setSignState(1);
	// 设置签到方式，家长端默认传2
	updateData.setSignType(dto->signType.getValue(2));
	// 设置签到时间
	updateData.setSignTime(SimpleDateTimeFormat::format());

	// 执行更新
	// 更新失败时：
	if (dao.updateLessonStudent(updateData) != 1)
	{
		result->success(buildSignResult(
			false,
			dto->lessonId,
			dto->signType.getValue(2),
			lessonStudent->getSignState(),
			lessonStudent->getSignState() == 1 ? ZH_WORDS_GETTER("timetable.words.sign-state-signed").c_str() :
			lessonStudent->getSignState() == 2 ? ZH_WORDS_GETTER("timetable.words.sign-state-repair").c_str() :
			lessonStudent->getSignState() == 3 ? ZH_WORDS_GETTER("timetable.words.sign-state-leave").c_str() :
			lessonStudent->getSignState() == 4 ? ZH_WORDS_GETTER("timetable.words.sign-state-absence").c_str() :
			ZH_WORDS_GETTER("timetable.words.sign-state-unsigned").c_str(),
			lessonStudent->getSignTime().c_str(),
			ZH_WORDS_GETTER("timetable.words.sign-failed").c_str()
		));
		return result;
	}
	// 更新成功时:
	auto currentSignTime = SimpleDateTimeFormat::format();

	result->success(buildSignResult(
		true,
		dto->lessonId,
		dto->signType.getValue(2),
		1,
		ZH_WORDS_GETTER("timetable.words.sign-state-signed").c_str(),
		currentSignTime.c_str(),
		ZH_WORDS_GETTER("timetable.words.sign-success").c_str()
	));

	return result;
}

/**
 * 学员请假
 */
LeaveVO::Wrapper TimetableService::leaveLesson(const LeaveDTO::Wrapper& dto)
{
	// 创建返回VO对象
	auto result = LeaveVO::createShared();

	// 创建DAO对象
	TimetableDAO dao;

	// 查询课次签到记录
	auto lessonStudent = dao.selectLessonStudentByLessonId(
		dto->lessonId.getValue(""),
		dto->studentId.getValue(""));

	// 未找到签到记录则返回失败
	if (!lessonStudent)
	{
		result->success(buildActionResult(false, dto->lessonId, "leave", ZH_WORDS_GETTER("timetable.words.leave-record-not-found").c_str()));
		return result;
	}

	// 创建更新DO对象
	LessonStudentDO updateData;

	// 设置主键
	updateData.setId(lessonStudent->getId());
	// 设置签到状态为请假
	updateData.setSignState(3);
	// 设置更新时间
	updateData.setSignTime(SimpleDateTimeFormat::format());

	// 当前版本先只更新签到状态
	// 如果后面你们有单独请假表或请假原因字段，再补充原因存储逻辑

	// 执行更新
	if (dao.updateLessonStudent(updateData) != 1)
	{
		result->success(buildActionResult(false, dto->lessonId, "leave", ZH_WORDS_GETTER("timetable.words.leave-failed").c_str()));
		return result;
	}

	// 返回请假成功
	result->success(buildActionResult(true, dto->lessonId, "leave", ZH_WORDS_GETTER("timetable.words.leave-success").c_str()));
	return result;
}
