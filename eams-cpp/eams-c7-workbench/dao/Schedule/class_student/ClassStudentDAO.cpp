#include "stdafx.h"
#include "ClassStudentDAO.h"
#include "ClassStudentMapper.h"

std::list<int64_t> ClassStudentDAO::selectStudentIdsByClassId(int64_t classId)
{
	string sql = "SELECT student_id FROM class_student WHERE class_id = ? AND deleted = 0";
	return sqlSession->executeQuery<int64_t>(sql, ClassStudentIdMapper(), "%ull", classId);
}

int ClassStudentDAO::getStudentCountByClassId(int64_t classId)
{
	string sql = "SELECT COUNT(*) FROM class_student WHERE class_id = ? AND deleted = 0";
	auto result = sqlSession->executeQuery<int>(sql, ClassStudentCountMapper(), "%ull", classId);
	if (result.empty()) return 0;
	return result.front();
}
