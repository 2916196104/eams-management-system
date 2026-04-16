#include "stdafx.h"
#include "LessonDAO.h"
#include "dao/lesson/LessonMapper.h"
#include "dao/lesson/LessonExtMapper.h"

uint64_t LessonDAO::countByQuery(const LessonQuery::Wrapper& query)
{
	LessonDO tempDO;
	std::string sql = "SELECT COUNT(*) FROM " + tempDO.getTable() + " WHERE 1=1";
	SqlParams params;

	if (query->date && !query->date->empty()) {
		sql += " AND date = ?";
		SQLPARAMS_PUSH(params, "s", std::string, *(query->date.get()));
	}
	if (query->bookable) {
		sql += " AND bookable = ?";
		SQLPARAMS_PUSH(params, "i", int, query->bookable.getValue(false) ? 1 : 0);
	}
	return sqlSession->executeQueryNumerical(sql, params);
}

// 联表查询
std::list<LessonExtDO> LessonDAO::selectExtByPage(const LessonQuery::Wrapper& query, uint64_t studentId)
{
	std::string sql = R"(
		SELECT 
			l.*, 
			c.name AS course_name,
			cls.name AS class_name,
			s.name AS teacher_name,
			cr.name AS classroom_name,
			ls.sign_state
		FROM lesson l
		LEFT JOIN course c ON l.course_id = c.id
		LEFT JOIN class cls ON l.class_id = cls.id
		LEFT JOIN staff s ON l.teacher_id = s.id
		LEFT JOIN classroom cr ON l.room_id = cr.id
		LEFT JOIN lesson_student ls ON l.id = ls.lesson_id AND ls.student_id = ?
		WHERE 1=1
	)";

	SqlParams params;
	// 绑定 JOIN 条件里的 student_id
	SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);

	// 拼接查询条件
	if (query->date && !query->date->empty()) {
		sql += " AND l.date = ?";
		SQLPARAMS_PUSH(params, "s", std::string, *(query->date.get()));
	}
	if (query->bookable) {
		sql += " AND l.bookable = ?";
		SQLPARAMS_PUSH(params, "i", int, query->bookable.getValue(false) ? 1 : 0);
	}

	// 拼接分页
	sql += " LIMIT ?, ?";
	uint64_t pageIndex = query->pageIndex.getValue(1);
	uint64_t pageSize = query->pageSize.getValue(10);
	uint64_t offset = (pageIndex - 1) * pageSize;
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

	LessonExtMapper mapper;
	return sqlSession->executeQuery<LessonExtDO, LessonExtMapper>(sql, mapper, params);
}

LessonDO LessonDAO::selectById(uint64_t id)
{
	LessonDO tempDO;
	std::string sql = "SELECT * FROM " + tempDO.getTable() + " WHERE id = ?";
	LessonMapper mapper;
	return sqlSession->executeQueryOne<LessonDO, LessonMapper>(sql, mapper, "%ull", id);
}

// --- 合并的签到逻辑 ---
int LessonDAO::selectSignState(uint64_t lessonId, uint64_t studentId) {
	std::string sql = "SELECT sign_state FROM lesson_student WHERE lesson_id = ? AND student_id = ?";
	return static_cast<int>(sqlSession->executeQueryNumerical(sql, "%ull%ull", lessonId, studentId));
}

int LessonDAO::updateSignState(uint64_t lessonId, uint64_t studentId, int state) {
	std::string sql = "UPDATE lesson_student SET sign_state = ? WHERE lesson_id = ? AND student_id = ?";
	return sqlSession->executeUpdate(sql, "%i%ull%ull", state, lessonId, studentId);
}