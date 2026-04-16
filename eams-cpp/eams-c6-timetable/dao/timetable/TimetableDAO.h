#pragma once
#ifndef _TIMETABLE_DAO_
#define _TIMETABLE_DAO_

#include "BaseDAO.h"
#include "../../domain/do/timetable/TimetableDO.h"
#include "../../domain/query/timetable/TimetableQuery.h"

/**
 * 家长端课表DAO
 */
class TimetableDAO : public BaseDAO
{
private:

	 // 构建课次基础查询条件，当前只按日期过滤课次数据
	inline std::string lessonBaseConditionBuilder(const std::string& studentId,
		const std::string& queryDate,
		SqlParams& params);

	
	// 构建课表分组查询条件
	// 课表分组包含：1.已入班的正式课 2. 已提交预约且待审核/审核通过的预约课
	inline std::string lessonSectionConditionBuilder(const std::string& studentId,
		const std::string& queryDate,
		SqlParams& params);

	
	//构建预约分组查询条件，预约分组只包含当前还能预约的课
	inline std::string reserveSectionConditionBuilder(const std::string& studentId,
		const std::string& queryDate,
		SqlParams& params);

public:
	// 按天查询课表分组原始数据
	std::list<TimetableCourseViewDO> selectLessonSectionByDay(const std::string& studentId, const std::string& queryDate);

	// 按天查询预约分组原始数据
	std::list<TimetableCourseViewDO> selectReserveSectionByDay(const std::string& studentId, const std::string& queryDate);

	// 按月查询月历课表计数
	std::list<TimetableCalendarCountDO> selectCalendarCountByMonth(const std::string& studentId, int year, int month);

	// 根据课次ID查询课次基础信息
	PtrLessonDO selectLessonById(const std::string& id);

	// 根据课次ID和学员ID查询签到记录
	PtrLessonStudentDO selectLessonStudentByLessonId(const std::string& lessonId, const std::string& studentId);

	// 统计某学员在某课次的预约记录数量
	uint64_t countAppointmentByLessonId(const std::string& lessonId, const std::string& studentId);

	// 统计某学员在某课次的驳回记录数量
	uint64_t countRejectedAppointmentByLessonId(const std::string& lessonId, const std::string& studentId);

	// 新增预约记录
	int insertAppointment(const BaseDO& bd);

	// 更新签到记录
	int updateLessonStudent(const BaseDO& bd);
};

#endif // !_TIMETABLE_DAO_
