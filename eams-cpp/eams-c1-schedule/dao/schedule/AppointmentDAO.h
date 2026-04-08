#pragma once
#ifndef _APPOINTMENT_DAO_
#define _APPOINTMENT_DAO_

#include "BaseDAO.h"
#include "../../domain/do/schedule/appointmentDO.h"

/**
 * 预约表数据库访问层
 */
class AppointmentDAO : public BaseDAO
{
public:
	// 继承BaseDAO之后，底层的insert/update方法已经通用
	/**
	 * 校验是否重复预约
	 * @param studentId 学生ID
	 * @param lessonId 排课(课次)ID
	 * @return 返回该学生针对该课次的预约记录条数
	 */
	uint64_t selectCountByStudentAndLesson(uint64_t studentId, uint64_t lessonId);

	/*
	  校验课次是否存在
	  去lesson_schedule_setting表里查一下有没有这个id
	  */
	uint64_t getCourseIdByScheduleId(uint64_t scheduleId);
	/**
	 * 获取学生的正式课时剩余数量
	 * @param studentId 学生ID
	 * @param courseId 课程ID
	 * @return 返回计算后的剩余课时总数
	 */
	uint64_t getStudentCourseRemain(uint64_t studentId, uint64_t courseId);

	/**
	 * 获取学生的试听卡/体验卡剩余次数
	 */
	uint64_t getStudentTrialCardRemain(uint64_t studentId, uint64_t courseId);
	
	/*
	* 获取学生的试听卡id和试听卡领取记录id
	*/
	std::pair<uint64_t, uint64_t> getValidTrialCard(uint64_t studentId, uint64_t courseId);
};
#endif // !_APPOINTMENT_DAO_