#include "stdafx.h"
#include "LessonStudentDao.h"
#include "LessonStudentMapper.h"

std::string LessonStudentDao::queryConditionBuilder(const LessonStudentQuery::Wrapper& query, SqlParams& params)
{
	std::string whereSql = " WHERE 1=1";
	if (!query)
	{
		return whereSql;
	}

	if (query->lesson_id && !query->lesson_id->empty())
	{
		whereSql += " AND lesson_id = ?";
		SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->lesson_id.getValue("0")));
	}
	if (query->class_id && !query->class_id->empty())
	{
		whereSql += " AND class_id = ?";
		SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->class_id.getValue("0")));
	}
	if (query->student_id && !query->student_id->empty())
	{
		whereSql += " AND student_id = ?";
		SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->student_id.getValue("0")));
	}
	if (query->teacher_id && !query->teacher_id->empty())
	{
		whereSql += " AND teacher_id = ?";
		SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->teacher_id.getValue("0")));
	}
	if (query->sign_state && !query->sign_state->empty())
	{
		whereSql += " AND sign_state = ?";
		SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->sign_state.getValue("0")));
	}
	if (query->org_id && !query->org_id->empty())
	{
		whereSql += " AND org_id = ?";
		SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->org_id.getValue("0")));
	}

	return whereSql;
}

uint64_t LessonStudentDao::count(const LessonStudentQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(1) FROM lesson_student";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

list<PtrLessonStudentDO> LessonStudentDao::selectWithPage(const LessonStudentQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT id, lesson_id, class_id, student_id, dec_lesson_count, lesson_count, teacher_id, "
		"sign_time, sign_type, sign_state, score, evaluation, evaluate_time, evaluate_teacher, "
		"consume_course_id, consume_student_course_id, counselor, add_time, org_id "
		"FROM lesson_student";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY id DESC LIMIT ?, ?";

	uint64_t pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : 1;
	uint64_t pageSize = query && query->pageSize ? query->pageSize.getValue(10) : 10;
	pageIndex = NormalizePageIndex(pageIndex);
	pageSize = NormalizePageSize(pageSize);
	const uint64_t offset = (pageIndex - 1) * pageSize;
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), params);
}

PtrLessonStudentDO LessonStudentDao::selectById(uint64_t id)
{
	const std::string sql =
		"SELECT id, lesson_id, class_id, student_id, dec_lesson_count, lesson_count, teacher_id, "
		"sign_time, sign_type, sign_state, score, evaluation, evaluate_time, evaluate_teacher, "
		"consume_course_id, consume_student_course_id, counselor, add_time, org_id "
		"FROM lesson_student WHERE id = ? LIMIT 1";
	return sqlSession->executeQueryOne<PtrLessonStudentDO>(sql, LessonStudentMapper(), "%ull", id);
}

uint64_t LessonStudentDao::insert(const LessonStudentDO& data)
{
	return BaseDAO::insert(data);
}

uint64_t LessonStudentDao::updateById(const LessonStudentDO& data)
{
	return BaseDAO::update(data);
}

uint64_t LessonStudentDao::deleteById(uint64_t id)
{
	const std::string sql = "DELETE FROM lesson_student WHERE id = ?";
	return sqlSession->executeUpdate(sql, "%ull", id);
}

uint64_t LessonStudentDao::sumLessonCountByClassAndStudent(uint64_t classId, uint64_t studentId)
{
	const std::string sql =
		"SELECT IFNULL(SUM(ls.lesson_count), 0) "
		"FROM lesson_student ls "
		"INNER JOIN lesson l ON l.id = ls.lesson_id "
		"WHERE l.class_id = ? AND ls.student_id = ? AND l.deleted = 0";
	return sqlSession->executeQueryNumerical(sql, "%ull%ull", classId, studentId);
}

list<PtrLessonStudentDO> LessonStudentDao::SelectLessonStudentWithPage(int64_t lessonId, const GetStuListQuery::Wrapper& query)
{
	uint64_t page_index = query && query->page_index ? query->page_index.getValue(1) : 1;
	uint64_t page_size = query && query->page_size ? query->page_size.getValue(10) : 10;
	page_index = NormalizePageIndex(page_index);
	page_size = NormalizePageSize(page_size);

	uint64_t offset = (page_index - 1) * page_size;

	const std::string sql =
		"SELECT id, lesson_id, class_id, student_id, dec_lesson_count, lesson_count, teacher_id, "
		"sign_time, sign_type, sign_state, score, evaluation, evaluate_time, evaluate_teacher, "
		"consume_course_id, consume_student_course_id, counselor, add_time, org_id "
		"FROM lesson_student WHERE lesson_id = ? ORDER BY id LIMIT ?, ?";

	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), "%ll%ull%ull", lessonId, offset, page_size);
}

uint64_t LessonStudentDao::CountLessonStudent(int64_t lesson_id)
{
	const std::string sql = "SELECT COUNT(1) FROM lesson_student WHERE lesson_id = ? ";
	return sqlSession->executeQueryNumerical(sql, "%ll", lesson_id);
}

void LessonStudentDao::AppendEvaluationFilters(
	std::string& sql,
	SqlParams& params,
	const EvaluationQuery::Wrapper& query)
{
	if (!query)
	{
		return;
	}
	if (query->name && !query->name->empty())
	{
		sql += " AND s.name LIKE ?";
		const std::string pattern = "%" + query->name.getValue("") + "%";
		SQLPARAMS_PUSH(params, "s", std::string, pattern);
	}
	if (query->score)
	{
		sql += " AND ls.score = ?";
		SQLPARAMS_PUSH(params, "i", int32_t, query->score.getValue(0));
	}
	if (query->isSign)
	{
		if (query->isSign.getValue(false))
		{
			sql += " AND ls.sign_state <> 0";
		}
		else
		{
			sql += " AND ls.sign_state = 0";
		}
	}
	if (query->isEvaluate)
	{
		if (query->isEvaluate.getValue(false))
		{
			sql += " AND ls.evaluation IS NOT NULL AND ls.evaluation <> ''";
		}
		else
		{
			sql += " AND (ls.evaluation IS NULL OR ls.evaluation = '')";
		}
	}
}

list<PtrLessonStudentDO> LessonStudentDao::SelectEvaluationWithPage(int64_t lesson_id, const EvaluationQuery::Wrapper& query)
{
	uint64_t page_index = query && query->pageIndex ? query->pageIndex.getValue(1) : 1;
	uint64_t page_size = query && query->pageSize ? query->pageSize.getValue(10) : 10;
	page_index = NormalizePageIndex(page_index);
	page_size = NormalizePageSize(page_size);

	const uint64_t offset = (page_index - 1) * page_size;

	std::string sql =
		"SELECT "
		" ls.id, ls.lesson_id, ls.class_id, ls.student_id, ls.dec_lesson_count, ls.lesson_count, ls.teacher_id, "
		" ls.sign_time, ls.sign_type, ls.sign_state, ls.score, ls.evaluation, ls.evaluate_time, ls.evaluate_teacher, "
		" ls.consume_course_id, ls.consume_student_course_id, ls.counselor, ls.add_time, ls.org_id "
		"FROM lesson_student ls LEFT JOIN student s ON s.id = ls.student_id "
		"WHERE ls.lesson_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "ll", int64_t, lesson_id);
	AppendEvaluationFilters(sql, params, query);

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
	AppendEvaluationFilters(sql, params, query);

	return sqlSession->executeQueryNumerical(sql, params);
}

int LessonStudentDao::UpdateSignStatus(uint64_t lesson_student_id, int32_t sign_type, int32_t sign_state, int32_t dec_lesson_count)
{

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