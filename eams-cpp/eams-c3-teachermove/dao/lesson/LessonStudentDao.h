#pragma once

#include "BaseDAO.h"
#include "domain/do/lesson/LessonStudentDO.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/query/timetable/TimetableQuery.h"

class LessonStudentDao : public BaseDAO
{
public:
	// 1) 点名页：按课次分页查 lesson_student
	list<PtrLessonStudentDO> SelectLessonStudentWithPage(int64_t lessonId, const GetStuListQuery::Wrapper& query);
	uint64_t CountLessonStudent(int64_t lessonId);

	// 2) 点评页：按课次 + 条件分页查（name/score/isSign/isEvaluate）
	list<PtrLessonStudentDO> SelectEvaluationWithPage(int64_t lessonId, const EvaluationQuery::Wrapper& query);
	uint64_t CountEvaluation(int64_t lessonId, const EvaluationQuery::Wrapper& query);

	// 3) 设置上课状态：更新 sign_type/sign_state/dec_lesson_count/sign_time
	int UpdateSignStatus(uint64_t lessonStudentId, int32_t signType, int32_t signState, int32_t decLessonCount);

	// 4) 点评指定学员：更新 score/evaluation/evaluate_teacher/evaluate_time
	int UpdateEvaluation(uint64_t lessonStudentId, int32_t score, const std::string& evaluation, int64_t evaluateTeacherId);

	// 5) 添加学员到课次：批量插入 lesson_student（add_time 用 NOW()）
	int InsertStudentsToLesson(int64_t lessonId, const std::list<int64_t>& studentIds, int32_t classId, int64_t teacherId, int64_t orgId);

private:
	uint64_t NormalizePageIndex(uint64_t pageIndex);
	uint64_t NormalizePageSize(uint64_t pageSize);
	void AppendEvaluationFilters(
		std::string& sql,
		SqlParams& params,
		const EvaluationQuery::Wrapper& query
	);
};