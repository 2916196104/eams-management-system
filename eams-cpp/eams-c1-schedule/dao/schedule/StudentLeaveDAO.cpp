#include "stdafx.h"
#include "StudentLeaveDAO.h"

uint64_t StudentLeaveDAO::checkHasLeaveRecord(uint64_t studentId, uint64_t lessonId)
{
	SqlParams params;
	// state = 1 通常代表这是一个有效的请假申请
	std::string sql = "SELECT COUNT(*) FROM student_leave WHERE student_id = ? AND lesson_id = ? AND state = 1";
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonId);
	return sqlSession->executeQueryNumerical(sql, params);
}

bool StudentLeaveDAO::checkLessonExists(uint64_t lessonId)
{
	SqlParams params;
	// 假设 lesson 表中 state = 1 表示正常未取消的课
	std::string sql = "SELECT COUNT(*) FROM lesson WHERE id = ? AND state = 1";
	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonId);

	return sqlSession->executeQueryNumerical(sql, params) > 0;
}

