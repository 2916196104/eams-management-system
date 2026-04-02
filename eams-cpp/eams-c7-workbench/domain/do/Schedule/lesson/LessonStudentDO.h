#pragma once
#ifndef _LESSON_STUDENT_DO_H_
#define _LESSON_STUDENT_DO_H_
#include "../../DoInclude.h"

/**
 * 课程学生关联数据库实体类
 */
class LessonStudentDO : public BaseDO
{
	// 编号（主键）
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程id
	MYSQL_SYNTHESIZE(int64_t, lessonId, LessonId);
	// 班级id（为空表示调课生）
	MYSQL_SYNTHESIZE(int, classId, ClassId);
	// 学员id
	MYSQL_SYNTHESIZE(int64_t, studentId, StudentId);
	// 实扣课次
	MYSQL_SYNTHESIZE(int, decLessonCount, DecLessonCount);
	// 应扣课次
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 点名的老师
	MYSQL_SYNTHESIZE(int64_t, teacherId, TeacherId);
	// 签到时间
	MYSQL_SYNTHESIZE(string, signTime, SignTime);
	// 签到方式
	MYSQL_SYNTHESIZE(int, signType, SignType);
	// 签到结果
	MYSQL_SYNTHESIZE(int, signState, SignState);
	// 老师评分
	MYSQL_SYNTHESIZE(int, score, Score);
	// 老师评语
	MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
	// 评语时间
	MYSQL_SYNTHESIZE(string, evaluateTime, EvaluateTime);
	// 评语老师
	MYSQL_SYNTHESIZE(int64_t, evaluateTeacher, EvaluateTeacher);
	// 实际消费课程
	MYSQL_SYNTHESIZE(int64_t, consumeCourseId, ConsumeCourseId);
	// 消费课程与学生关联表ID
	MYSQL_SYNTHESIZE(int64_t, consumeStudentCourseId, ConsumeStudentCourseId);
	// 学生的顾问
	MYSQL_SYNTHESIZE(int64_t, counselor, Counselor);
	// 加入时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 上课老师所属组织ID
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);

public:
	LessonStudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("lesson_id", "ll", lessonId, false);
		MYSQL_ADD_FIELD_NULLABLE("class_id", "i", classId, false);
		MYSQL_ADD_FIELD_NULLABLE("student_id", "ll", studentId, false);
		MYSQL_ADD_FIELD_NULLABLE("dec_lesson_count", "i", decLessonCount, false);
		MYSQL_ADD_FIELD_NULLABLE("lesson_count", "i", lessonCount, false);
		MYSQL_ADD_FIELD_NULLABLE("teacher_id", "ll", teacherId, false);
		MYSQL_ADD_FIELD_NULLABLE("sign_time", "s", signTime, false);
		MYSQL_ADD_FIELD_NULLABLE("sign_type", "i", signType, false);
		MYSQL_ADD_FIELD_NULLABLE("sign_state", "i", signState, false);
		MYSQL_ADD_FIELD_NULLABLE("score", "i", score, false);
		MYSQL_ADD_FIELD_NULLABLE("evaluation", "s", evaluation, false);
		MYSQL_ADD_FIELD_NULLABLE("evaluate_time", "s", evaluateTime, false);
		MYSQL_ADD_FIELD_NULLABLE("evaluate_teacher", "ll", evaluateTeacher, false);
		MYSQL_ADD_FIELD_NULLABLE("consume_course_id", "ll", consumeCourseId, false);
		MYSQL_ADD_FIELD_NULLABLE("consume_student_course_id", "ll", consumeStudentCourseId, false);
		MYSQL_ADD_FIELD_NULLABLE("counselor", "ll", counselor, false);
		MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, false);
		MYSQL_ADD_FIELD_NULLABLE("org_id", "ll", orgId, false);
	}
};

// 给LessonStudentDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

#endif // !_LESSON_STUDENT_DO_H_
