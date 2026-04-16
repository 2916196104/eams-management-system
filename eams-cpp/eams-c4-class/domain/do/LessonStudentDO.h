#pragma once
#ifndef _LessonStudent_DO_
#define _LessonStudent_DO_
#include "../DoInclude.h"

/**
 * 示例数据库实体类
 */
class LessonStudentDO : public BaseDO
{
	// 编号
	MYSQL_SYNTHESIZE(string, id, Id);
	//课程id
	MYSQL_SYNTHESIZE(string, lesson_id, Lesson_id);
	//班级id
	MYSQL_SYNTHESIZE(string, class_id, Class_id);
	//学员id
	MYSQL_SYNTHESIZE(string, student_id, Student_id);
	//实扣课次
	MYSQL_SYNTHESIZE(int, dec_lesson_count, dec_lesson_count);
	//应扣课次
	MYSQL_SYNTHESIZE(int, lesson_count, lesson_count);
	//点名的老师
	MYSQL_SYNTHESIZE(string, teacher_id, Teacher_id);
	//签到时间
	MYSQL_SYNTHESIZE(string, sign_time, Sign_time);
	//签到方式
	MYSQL_SYNTHESIZE(string, sign_type, Sign_type);
	//签到结果
	MYSQL_SYNTHESIZE(string, sign_state, Sign_state);
	//老师评分
	MYSQL_SYNTHESIZE(string, score, Score);
	//老师评语
	MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
	//评语时间
	MYSQL_SYNTHESIZE(string, evaluation_time, Evaluation_time);
	//评语老师
	MYSQL_SYNTHESIZE(string, evaluation_teacher, Evaluation_teacher);
	//实际消费课程
	MYSQL_SYNTHESIZE(int, consume_course_id, Consume_course_id);
	//消费课程与学生关联表ID
	MYSQL_SYNTHESIZE(string, consume_student_course_id, Consume_student_course_id);
	//学生的顾问
	MYSQL_SYNTHESIZE(string, counselor,Counselor);
	//加入时间
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	//上课老师所属组织
	MYSQL_SYNTHESIZE(string, org_id, Org_id);

public:
	LessonStudentDO() : BaseDO("LessonStudentDO")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("lesson_id", "s", lesson_id);
		MYSQL_ADD_FIELD("class_id", "s", class_id);
		MYSQL_ADD_FIELD("student_id", "s", student_id);
		MYSQL_ADD_FIELD("dec_lesson_count", "i", dec_lesson_count);
		MYSQL_ADD_FIELD("lesson_count", "i", lesson_count);
		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);
		MYSQL_ADD_FIELD("sign_time", "s", sign_time);
		MYSQL_ADD_FIELD("sign_type", "s", sign_type);
		MYSQL_ADD_FIELD("sign_state", "s", sign_state);
		MYSQL_ADD_FIELD("score", "s", score);
		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
		MYSQL_ADD_FIELD("evaluation_time", "s", evaluation_time);
		MYSQL_ADD_FIELD("evaluation_teacher", "s", evaluation_teacher);
		MYSQL_ADD_FIELD("consume_course_id", "i", consume_course_id);
		MYSQL_ADD_FIELD("consume_student_course_id", "s", consume_student_course_id);
		MYSQL_ADD_FIELD("counselor", "s", counselor);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("org_id", "s", org_id);

	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;
#endif // !_LessonStudent_DO_