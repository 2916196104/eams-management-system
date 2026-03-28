#pragma once

#include "BaseDAO.h"
#include "domain/do/lesson/LessonStudentDO.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/query/timetable/TimetableQuery.h"

class LessonStudentDao : public BaseDAO
{
public:
	// 1) 点名页：按课次分页查 lesson_student
	list<PtrLessonStudentDO> SelectLessonStudentWithPage(int64_t lesson_id, const GetStuListQuery::Wrapper& query);
	uint64_t CountLessonStudent(int64_t lesson_id);

	// 2) 点评页：按课次 + 条件分页查（name/score/isSign/isEvaluate）
	list<PtrLessonStudentDO> SelectEvaluationWithPage(int64_t lesson_id, const EvaluationQuery::Wrapper& query);
	uint64_t CountEvaluation(int64_t lesson_id, const EvaluationQuery::Wrapper& query);

	// 3) 设置上课状态：更新 sign_type/sign_state/dec_lesson_count/sign_time
	int UpdateSignStatus(uint64_t lesson_student_id, int32_t sign_type, int32_t sign_state, int32_t dec_lesson_count);

	// 4) 点评指定学员：更新 score/evaluation/evaluate_teacher/evaluate_time
	int UpdateEvaluation(uint64_t lesson_student_id, int32_t score, const std::string& evaluation, int64_t evaluate_teacher_id);

	// 5) 添加学员到课次：批量插入 lesson_student（add_time 用 NOW()）
	int InsertStudentsToLesson(int64_t lesson_id, const std::list<int64_t>& student_ids, int32_t class_id, int64_t teacher_id, int64_t org_id);

private:
	uint64_t NormalizePageIndex(uint64_t page_index);
	uint64_t NormalizePageSize(uint64_t page_size);
};