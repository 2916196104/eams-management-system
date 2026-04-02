#include "stdafx.h"
#include "CourseDAO.h"
#include "CourseMapper.h"

PtrCourseDO CourseDAO::selectById(int64_t courseId)
{
	string sql = "SELECT id, name, subject_id FROM course WHERE id = ?";
	return sqlSession->executeQueryOne<PtrCourseDO>(sql, PtrCourseMapper(), "%ull", courseId);
}

std::string CourseDAO::selectNameById(int64_t courseId)
{
	string sql = "SELECT name FROM course WHERE id = ?";
	auto result = sqlSession->executeQueryOne<std::string>(sql, CourseNameMapper(), "%ull", courseId);
	return result;
}
