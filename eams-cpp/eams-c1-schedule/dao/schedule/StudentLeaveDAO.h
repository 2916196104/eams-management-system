#pragma once
#ifndef _STUDENT_LEAVE_DAO_
#define _STUDENT_LEAVE_DAO_

#include "BaseDAO.h"
#include "../../domain/do/schedule/studentLeaveDO.h" // 假设你有这个 DO

class StudentLeaveDAO : public BaseDAO
{
public:
	// 校验 1：是否已经请过假了？
	uint64_t checkHasLeaveRecord(uint64_t studentId, uint64_t lessonId);

	// 校验：课次是否存在且状态正常？
	bool checkLessonExists(uint64_t lessonId);
};

#endif