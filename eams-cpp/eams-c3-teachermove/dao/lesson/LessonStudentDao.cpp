#include "stdafx.h"
#include "LessonStudentDao.h"
#include "LessonStudentMapper.h"

list<PtrLessonStudentDO> LessonStudentDao::SelectLessonStudentWithPage(int64_t lessonId, const GetStuListQuery::Wrapper& query)
{
	uint64_t pageIndex = query && query->page_index ? query->page_index.getValue(1) : 1;
	uint64_t pageSize = query && query->page_size ? query->page_size.getValue(10) : 10;
	pageIndex = NormalizePageIndex(pageIndex);
	pageSize = NormalizePageSize(pageSize);

	uint64_t offset = (pageIndex - 1) * pageSize;

	const std::string sql =
		"SELECT * FROM lesson_student WHERE lesson_id = ? ORDER BY id LIMIT ?, ?";

	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), "%ll%ull%ull", lessonId, offset, pageSize);
}

uint64_t LessonStudentDao::CountLessonStudent(int64_t lessonId)
{
	const std::string sql = "SELECT COUNT(1) FROM lesson_student WHERE lesson_id = ? ";
	return sqlSession->executeQueryNumerical(sql, "%ll", lessonId);
}

list<PtrLessonStudentDO> LessonStudentDao::SelectEvaluationWithPage(int64_t lessonId, const EvaluationQuery::Wrapper& query)
{
	uint64_t pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : 1;
	uint64_t pageSize = query && query->pageSize ? query->pageSize.getValue(10) : 10;
	pageIndex = NormalizePageIndex(pageIndex);
	pageSize = NormalizePageSize(pageSize);

	uint64_t offset = (pageIndex - 1) * pageSize;

	std::string sql =
		"SELECT "
		" ls.id, ls.lesson_id, ls.class_id, ls.student_id, ls.dec_lesson_count, ls.lesson_count, ls.teacher_id, "
		" ls.sign_time, ls.sign_type, ls.sign_state, ls.score, ls.evaluation, ls.evaluate_time, ls.evaluate_teacher, "
		" ls.consume_course_id, ls.consume_student_course_id, ls.counselor, ls.add_time, ls.org_id "
		"FROM lesson_student ls LEFT JOIN student s ON s.id = ls.student_id "
		"WHERE ls.lesson_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "ll", int64_t, lessonId);

	AppendEvaluationFilters(sql, params, query);

	sql += " ORDER BY ls.id DESC LIMIT ?, ? ";
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

	return sqlSession->executeQuery<PtrLessonStudentDO>(sql, LessonStudentMapper(), params);
}

uint64_t LessonStudentDao::CountEvaluation(int64_t lessonId, const EvaluationQuery::Wrapper& query)
{
	std::string sql =
		"SELECT COUNT(1) "
		"FROM lesson_student ls "
		"LEFT JOIN student s ON s.id = ls.student_id "
		"WHERE ls.lesson_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "ll", int64_t, lessonId);

	AppendEvaluationFilters(sql, params, query);

	return sqlSession->executeQueryNumerical(sql, params);
}

int LessonStudentDao::UpdateSignStatus(uint64_t lessonStudentId, int32_t signType, int32_t signState, int32_t decLessonCount)
{
	// sign_time 直接写 NOW()
	const std::string sql =
		"UPDATE lesson_student "
		"SET sign_type = ?, sign_state = ?, dec_lesson_count = ?, sign_time = NOW() "
		"WHERE id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "i", int32_t, signType);
	SQLPARAMS_PUSH(params, "i", int32_t, signState);
	SQLPARAMS_PUSH(params, "i", int32_t, decLessonCount);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonStudentId);

	return sqlSession->executeUpdate(sql, params);
}

int LessonStudentDao::UpdateEvaluation(uint64_t lessonStudentId, int32_t score, const std::string& evaluation, int64_t evaluateTeacherId)
{
	const std::string sql =
		"UPDATE lesson_student "
		"SET score = ?, evaluation = ?, evaluate_teacher = ?, evaluate_time = NOW() "
		"WHERE id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "i", int32_t, score);
	SQLPARAMS_PUSH(params, "s", std::string, evaluation);
	SQLPARAMS_PUSH(params, "ll", int64_t, evaluateTeacherId);
	SQLPARAMS_PUSH(params, "ull", uint64_t, lessonStudentId);

	return sqlSession->executeUpdate(sql, params);
}

int LessonStudentDao::InsertStudentsToLesson(int64_t lessonId, const std::list<int64_t>& studentIds, int32_t classId, int64_t teacherId, int64_t orgId)
{
	if (studentIds.empty())
	{
		return 0;
	}

	const std::string sql =
		"INSERT INTO lesson_student(lesson_id, class_id, student_id, teacher_id, org_id, add_time) "
		"VALUES(?, ?, ?, ?, ?, NOW()) ";

	int rows = 0;
	sqlSession->beginTransaction();
	try
	{
		for (auto studentId : studentIds)
		{
			rows += sqlSession->executeUpdate(sql, "%ll%i%ll%ll%ll", lessonId, classId, studentId, teacherId, orgId);
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

uint64_t LessonStudentDao::NormalizePageIndex(uint64_t pageIndex)
{
	return pageIndex == 0 ? 1 : pageIndex;
}

uint64_t LessonStudentDao::NormalizePageSize(uint64_t pageSize)
{
	return pageSize == 0 ? 10 : pageSize;
}

void LessonStudentDao::AppendEvaluationFilters(
	std::string& sql,
	SqlParams& params,
	const EvaluationQuery::Wrapper& query)
{
	(void)query;

	// name: 需要 join student 表才可过滤
	if (query && query->name && !query->name->empty())
	{
		sql += " AND s.name LIKE CONCAT('%', ?, '%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	// score
	if (query && query->score)
	{
		sql += " AND ls.score = ? ";
		SQLPARAMS_PUSH(params, "i", int32_t, static_cast<int32_t>(query->score.getValue(0)));
	}

	// isSign：这里按 sign_state 是否为 0 简化
	if (query && query->isSign)
	{
		if (query->isSign.getValue(false))
		{
			sql += " AND ls.sign_state <> 0 ";
		}
		else
		{
			sql += " AND ls.sign_state = 0 ";
		}
	}

	// isEvaluate：按 evaluation 是否为空简化
	if (query && query->isEvaluate)
	{
		if (query->isEvaluate.getValue(false))
		{
			sql += " AND ls.evaluation IS NOT NULL AND ls.evaluation <> '' ";
		}
		else
		{
			sql += " AND (ls.evaluation IS NULL OR ls.evaluation = '') ";
		}
	}
}