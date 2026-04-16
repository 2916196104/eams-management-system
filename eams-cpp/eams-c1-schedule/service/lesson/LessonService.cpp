#include "stdafx.h"
#include "LessonService.h"
#include "dao/lesson/LessonDAO.h"

// ==============================================================================
// 业务 1：分页获取课表
// ==============================================================================
LessonPageDTO::Wrapper LessonService::listLesson(const LessonQuery::Wrapper& query, const PayloadDTO& payload)
{
	auto pageDto = LessonPageDTO::createShared();
	LessonDAO dao;
	uint64_t studentId = std::stoull(payload.getId());

	// 查询总数
	uint64_t totalCount = dao.countByQuery(query);

	// 初始化分页基础数据
	uint64_t pageIndex = query->pageIndex ? query->pageIndex.getValue(1) : 1;
	uint64_t pageSize = query->pageSize ? query->pageSize.getValue(10) : 10;
	pageDto->initAll(pageIndex, pageSize, totalCount, oatpp::Int64(static_cast<int64_t>(0)), oatpp::List<LessonVO::Wrapper>::createShared());
	pageDto->calcPages(); // 自动计算总页数

	// 如果总数为 0，直接返回空列表
	if (totalCount == 0) {
		return pageDto;
	}

	// 查询分页数据
	std::list<LessonExtDO> doList = dao.selectExtByPage(query, studentId);

	// DO 转 VO
	for (const auto& doItem : doList) {
		auto vo = convertDoToVo(doItem);
		pageDto->addData(vo);
	}

	return pageDto;
}

// ==============================================================================
// 业务 2：学生签到
// ==============================================================================
bool LessonService::signLesson(uint64_t lessonId, const PayloadDTO& payload)
{
	LessonDAO dao;
	uint64_t studentId = std::stoull(payload.getId());

	// 查出课程
	LessonDO lessonDO = dao.selectById(lessonId);
	if (!lessonDO.getIdPtr())return false;
	if (lessonDO.getId() == 0) return false;

	// 业务规则校验
	if (lessonDO.getState() != 1) return false; // 非进行中
	int currentSignState = dao.selectSignState(lessonId, studentId);
	if (currentSignState == 1) return false; // 已签到

	// 执行更新
	int rows = dao.updateSignState(lessonId, studentId, 1); // 1-已签到
	return rows > 0;
}

// ==============================================================================
// 私有辅助函数：DO -> VO
// ==============================================================================
LessonVO::Wrapper LessonService::convertDoToVo(const LessonExtDO& doItem)
{
	auto vo = LessonVO::createShared();

	// 宏拷贝
	ZO_STAR_DOMAIN_DO_TO_DTO(vo, doItem,
		id, Id,
		date, Date,
		startTime, StartTime,
		endTime, EndTime,
		courseName, CourseName,       // 来自 ExtDO
		className, ClassName,         // 来自 ExtDO
		teacherNames, TeacherName,    // 来自 ExtDO
		classroom, ClassroomName      // 来自 ExtDO
	);

	// 截取时间
	std::string startStr = doItem.getStartTime();
	if (startStr.length() >= 16) vo->startTime = startStr.substr(11, 5);
	std::string endStr = doItem.getEndTime();
	if (endStr.length() >= 16) vo->endTime = endStr.substr(11, 5);

	// 课程状态
	switch (doItem.getState()) {
	case 0: vo->state = ZH_WORDS_GETTER("lesson.status.not_started"); break;
	case 1: vo->state = ZH_WORDS_GETTER("lesson.status.ongoing"); break;
	case 2: vo->state = ZH_WORDS_GETTER("lesson.status.finished"); break;
	default: vo->state = ZH_WORDS_GETTER("lesson.status.unknown");
	}

	if (doItem.getSignState() == 1) {
		vo->studentSignState = ZH_WORDS_GETTER("lesson.status.signed");
		vo->studentCanSign = false;
		vo->studentCanLeave = false;
	}
	else {
		vo->studentSignState = ZH_WORDS_GETTER("lesson.status.unsigned");
		vo->studentCanSign = (doItem.getState() == 1); // 进行中才能签到
		vo->studentCanLeave = (doItem.getState() == 0); // 未开始才能请假
	}

	// 是否预约课 (bookable)
	vo->bookable = (doItem.getBookable() == 1);

	return vo;
}