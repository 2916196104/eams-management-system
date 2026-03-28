#include "stdafx.h"
#include "LessonStudentDao.h"
#include "LessonStudentMapper.h"

list<PtrLessonStudentDO> LessonStudentDao::SelectLessonStudentWithPage(int64_t lesson_id, const GetStuListQuery::Wrapper& query)
{
	uint64_t page_index = query && query->page_index ? query->page_index.getValue(1) : 1;
	uint64_t page_size = query && query->page_size ? query->page_size.getValue(10) : 10;
	page_index = NormalizePageIndex(page_index);
	page_size = NormalizePageSize(page_size);

	uint64_t offset = (page_index - 1) * page_size;

	const std::string sql =
		"SELECT * FROM lesson_student WHERE lesson_id = ? ORDER BY id LIMIT ?, ?";

	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), "%ll%ull%ull", lesson_id, offset, page_size);
}

uint64_t LessonStudentDao::CountLessonStudent(int64_t lesson_id)
{
	const std::string sql = "SELECT COUNT(1) FROM lesson_student WHERE lesson_id = ? ";
	return sqlSession->executeQueryNumerical(sql, "%ll", lesson_id);
}

list<PtrLessonStudentDO> LessonStudentDao::SelectEvaluationWithPage(int64_t lesson_id, const EvaluationQuery::Wrapper& query)
{
	uint64_t page_index = 1;
	uint64_t page_size = 10;
	page_index = NormalizePageIndex(page_index);
	page_size = NormalizePageSize(page_size);

	uint64_t offset = (page_index - 1) * page_size;

	std::string sql =
		"SELECT "
		" ls.id, ls.lesson_id, ls.class_id, ls.student_id, ls.dec_lesson_count, ls.lesson_count, ls.teacher_id, "
		" ls.sign_time, ls.sign_type, ls.sign_state, ls.score, ls.evaluation, ls.evaluate_time, ls.evaluate_teacher, "
		" ls.consume_course_id, ls.consume_student_course_id, ls.counselor, ls.add_time, ls.org_id "
		"FROM lesson_student ls LEFT JOIN student s ON s.id = ls.student_id "
		"WHERE ls.lesson_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "ll", int64_t, lesson_id);

	sql += " ORDER BY ls.id DESC LIMIT ?, ? ";
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	SQLPARAMS_PUSH(params, "ull", uint64_t, page_size);
	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), params);
}

uint64_t LessonStudentDao::CountEvaluation(int64_t lesson_id, const EvaluationQuery::Wrapper& query)
{
	std::string sql =
		"SELECT COUNT(1) "
		"FROM lesson_student ls "
		"LEFT JOIN student s ON s.id = ls.student_id "
		"WHERE ls.lesson_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "ll", int64_t, lesson_id);

	return sqlSession->executeQueryNumerical(sql, params);
}

int LessonStudentDao::UpdateSignStatus(uint64_t lesson_student_id, int32_t sign_type, int32_t sign_state, int32_t dec_lesson_count)
{
	// sign_time 直接写 NOW()
	const std::string sql =
		"UPDATE lesson_student "
		"SET sign_type = ?, sign_state = ?, dec_lesson_count = ?, sign_time = NOW() "
		"WHERE id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "i", int32_t, sign_type);
	SQLPARAMS_PUSH(params, "i", int32_t, sign_state);
	SQLPARAMS_PUSH(params, "i", int32_t, dec_lesson_count);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lesson_student_id);

	return sqlSession->executeUpdate(sql, params);
}

int LessonStudentDao::UpdateEvaluation(uint64_t lesson_student_id, int32_t score, const std::string& evaluation, int64_t evaluate_teacher_id)
{
	const std::string sql =
		"UPDATE lesson_student "
		"SET score = ?, evaluation = ?, evaluate_teacher = ?, evaluate_time = NOW() "
		"WHERE id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "i", int32_t, score);
	SQLPARAMS_PUSH(params, "s", std::string, evaluation);
	SQLPARAMS_PUSH(params, "ll", int64_t, evaluate_teacher_id);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lesson_student_id);

	return sqlSession->executeUpdate(sql, params);
}

int LessonStudentDao::InsertStudentsToLesson(int64_t lesson_id, const std::list<int64_t>& student_ids, int32_t class_id, int64_t teacher_id, int64_t org_id)
{
	if (student_ids.empty())
		return 0;

	const std::string sql =
		"INSERT INTO lesson_student(lesson_id, class_id, student_id, teacher_id, org_id, add_time) "
		"VALUES(?, ?, ?, ?, ?, NOW()) ";

	int rows = 0;
	sqlSession->beginTransaction();
	try
	{
		for (auto student_id : student_ids)
		{
			rows += sqlSession->executeUpdate(sql, "%ll%i%ll%ll%ll", lesson_id, class_id, student_id, teacher_id, org_id);
		}
		sqlSession->commitTransaction();
	}
	catch (...)
	{
		sqlSession->rollbackTransaction();
		throw;
	}

	return rows;
}

uint64_t LessonStudentDao::NormalizePageIndex(uint64_t page_index)
{
	return page_index == 0 ? 1 : page_index;
}

uint64_t LessonStudentDao::NormalizePageSize(uint64_t page_size)
{
	return page_size == 0 ? 10 : page_size;
}