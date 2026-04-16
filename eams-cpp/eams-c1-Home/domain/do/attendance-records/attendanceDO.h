#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _LESSON_STUDENTDO_H_
#define _LESSON_STUDENTDO_H_

#include "../DoInclude.h"

 /**
  * lesson_student表数据库实体类
  */
class Lesson_StudentDO : public BaseDO
{
public:
	// id
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 课程id
	MYSQL_SYNTHESIZE(uint64_t, lesson_id, LessonId);
	// 班级id为空表示调课生
	MYSQL_SYNTHESIZE(uint32_t, class_id, ClassId);
	// 学员id
	MYSQL_SYNTHESIZE(uint64_t, student_id, StudentId);
	// 实扣课次
	MYSQL_SYNTHESIZE(uint32_t, dec_lesson_count, DecLessonCount);
	// 应扣课次
	MYSQL_SYNTHESIZE(uint32_t, lesson_count, LessonCount);
	// 点名的老师
	MYSQL_SYNTHESIZE(uint64_t, teacher_id, TeacherId);
	// 签到时间
	MYSQL_SYNTHESIZE(std::string, sign_time, SignTime);
	// 签到方式
	MYSQL_SYNTHESIZE(uint8_t, sign_type, SignType);
	// 签到结果
	MYSQL_SYNTHESIZE(uint8_t, sign_state, SignState);
	// 老师评分
	MYSQL_SYNTHESIZE(uint8_t, score, Score);
	// 老师评语
	MYSQL_SYNTHESIZE(std::string, evaluation, Evaluation);
	// 评语时间
	MYSQL_SYNTHESIZE(std::string, evaluate_time, EvaluateTime);
	// 评语老师
	MYSQL_SYNTHESIZE(uint64_t, evaluate_teacher, EvaluateTeacher);
	// 实际消费课程
	MYSQL_SYNTHESIZE(uint64_t, consume_course_id, ConsumeCourseId);
	// 消费课程与学生关联表ID
	MYSQL_SYNTHESIZE(uint64_t, consume_student_course_id, ConsumeStudentCourseId);
	// 学生的顾问
	MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
	// 加入时间
	MYSQL_SYNTHESIZE(std::string, add_time, AddTime);
	// 上课老师所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
	// 上课日期 lesson表
	MYSQL_SYNTHESIZE(std::string, date, Date);
	// 上课开始时间 lesson表
	MYSQL_SYNTHESIZE(std::string, start_time, StartTime);
	// 上课结束时间 lesson表
	MYSQL_SYNTHESIZE(std::string, end_time, EndTime);
	// 课程名称 course表
	MYSQL_SYNTHESIZE(std::string, course_name, CourseName);
	// 课时标题 lesson表
	MYSQL_SYNTHESIZE(std::string, lesson_title, LessonTitle);
	// 是否能评价 sign_state in (1,2) as can_evaluate
	MYSQL_SYNTHESIZE(uint32_t, can_evaluate, CanEvaluate);
public:
	Lesson_StudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);

		MYSQL_ADD_FIELD("lesson_id", "i", lesson_id);
		MYSQL_ADD_FIELD("class_id", "i", class_id);
		MYSQL_ADD_FIELD("student_id", "i", student_id);
		MYSQL_ADD_FIELD("dec_lesson_count", "i", dec_lesson_count);
		MYSQL_ADD_FIELD("lesson_count", "i", lesson_count);
		MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);
		MYSQL_ADD_FIELD("sign_time", "s", sign_time);
		MYSQL_ADD_FIELD("sign_type", "i", sign_type);
		MYSQL_ADD_FIELD("sign_state", "i", sign_state);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
		MYSQL_ADD_FIELD("evaluate_time", "s", evaluate_time);
		MYSQL_ADD_FIELD("evaluate_teacher", "i", evaluate_teacher);
		MYSQL_ADD_FIELD("consume_course_id", "i", consume_course_id);
		MYSQL_ADD_FIELD("consume_student_course_id", "i", consume_student_course_id);
		MYSQL_ADD_FIELD("counselor", "i", counselor);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("org_id", "i", org_id);
	}
};

typedef std::shared_ptr<Lesson_StudentDO> PtrLesson_StudentDO;

/**
* teach_evaluation表数据库实体类
*/
class Teach_EvaluationDO : public BaseDO
{
public:
	// 主键
	MYSQL_SYNTHESIZE(std::uint64_t, id, Id);
	// 课次id
	MYSQL_SYNTHESIZE(uint64_t, lesson_id, LessonId);
	// 老师id
	MYSQL_SYNTHESIZE(uint64_t, teacher_id, TeacherId);
	// 综合评分
	MYSQL_SYNTHESIZE(uint8_t, score1, Score1);
	// 课堂气氛
	MYSQL_SYNTHESIZE(uint8_t, score2, Score2);
	// 授课态度
	MYSQL_SYNTHESIZE(uint8_t, score3, Score3);
	// 教学效果
	MYSQL_SYNTHESIZE(uint8_t, score4, Score4);
	// 评语
	MYSQL_SYNTHESIZE(std::string, content, Content);
	// 评价时间
	MYSQL_SYNTHESIZE(std::string, add_time, AddTime);
	// 学生id
	MYSQL_SYNTHESIZE(uint64_t, student_id, StudentId);
	// 是否匿名
	MYSQL_SYNTHESIZE(uint8_t, anonymity, Anonymity);
	// 被评价老师所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, org_id, OrgId);
public:
	Teach_EvaluationDO(): BaseDO("teach_evaluation")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("lesson_id", "ull", lesson_id);
		MYSQL_ADD_FIELD("teacher_id", "ull", teacher_id);
		MYSQL_ADD_FIELD("score1", "i", score1);
		MYSQL_ADD_FIELD("score2", "i", score2);
		MYSQL_ADD_FIELD("score3", "i", score3);
		MYSQL_ADD_FIELD("score4", "i", score4);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("student_id", "ull", student_id);
		MYSQL_ADD_FIELD("anonymity", "i", anonymity);
		MYSQL_ADD_FIELD("org_id", "ull", org_id);
	}
};

typedef std::shared_ptr<Teach_EvaluationDO> Ptrteach_evaluationDO;
#endif // !_LESSON_STUDENTDO_H_

