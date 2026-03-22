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
#ifndef _ATTENDANCEDO_H_
#define _ATTENDANCEDO_H_
#include "../DoInclude.h"
/*
* 考勤记录数据库实体类
*/
class TeachEvaluationDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课次id
	MYSQL_SYNTHESIZE(string, lesson_id, LessonId);
	// 老师id
	MYSQL_SYNTHESIZE(string, teacher_id, TeacherId);
	// 综合评分
	MYSQL_SYNTHESIZE(int, score1, Score1);
	// 课堂气氛
	MYSQL_SYNTHESIZE(int, score2, Score2);
	// 授课态度
	MYSQL_SYNTHESIZE(int, score3, Score3);
	// 教学效果
	MYSQL_SYNTHESIZE(int, score4, Score4);
	// 评语
	MYSQL_SYNTHESIZE(string, content, Content);
	// 评价时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 学生id
	MYSQL_SYNTHESIZE(string, student_id, StudentId);
	// 是否匿名
	MYSQL_SYNTHESIZE(int, anonymity, Anonymity);
	// 被评价老师所属组织ID
	MYSQL_SYNTHESIZE(string, org_id, OrgId);

public:
	TeachEvaluationDO() : BaseDO("teach_evaluation")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("lesson_id", "s", lesson_id);
		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);
		MYSQL_ADD_FIELD("score1", "i", score1);
		MYSQL_ADD_FIELD("score2", "i", score2);
		MYSQL_ADD_FIELD("score3", "i", score3);
		MYSQL_ADD_FIELD("score4", "i", score4);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("student_id", "s", student_id);
		MYSQL_ADD_FIELD("anonymity", "i", anonymity);
		MYSQL_ADD_FIELD("org_id", "s", org_id);
	}
};

// TeachEvaluationDO智能指针
typedef std::shared_ptr<TeachEvaluationDO> PtrTeachEvaluationDO;

/**
 * 课程信息DO
 */
class LessonDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课程标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 课节数 第几节课
	MYSQL_SYNTHESIZE(int, sn, Sn);

	// 课程id
	MYSQL_SYNTHESIZE(string, course_id, CourseId);
	// 编排计划id
	MYSQL_SYNTHESIZE(string, schedule_id, ScheduleId);

	// 班级id
	MYSQL_SYNTHESIZE(string, class_id, ClassId);
	// 教室id
	MYSQL_SYNTHESIZE(string, room_id, RoomId);

	// 上课日期
	MYSQL_SYNTHESIZE(string, date, Date);
	// 开始时间
	MYSQL_SYNTHESIZE(string, start_time, StartTime);
	// 结束时间
	MYSQL_SYNTHESIZE(string, end_time, EndTime);

	// 创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(string, editor, Editor);

	// 添加时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 修改时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);

	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);

	// 应扣课次数
	MYSQL_SYNTHESIZE(int, dec_count, DecCount);

	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);

	// 授课方式
	MYSQL_SYNTHESIZE(int, teach_type, TeachType);

	// 是否开启试听
	MYSQL_SYNTHESIZE(int, on_trial, OnTrial);
	// 试听结果
	MYSQL_SYNTHESIZE(string, trial_result, TrialResult);

	// 课次状态
	MYSQL_SYNTHESIZE(int, state, State);

	// 结课时间
	MYSQL_SYNTHESIZE(string, close_time, CloseTime);
	// 结课人
	MYSQL_SYNTHESIZE(string, close_operator, CloseOperator);

	// 主讲人(只用于数据权限)
	MYSQL_SYNTHESIZE(string, teacher_id, TeacherId);

	// 是否开放预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);

	// 老师所属学校ID
	MYSQL_SYNTHESIZE(string, school_id, SchoolId);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(string, org_id, OrgId);

public:
	LessonDO() : BaseDO("lesson")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);

		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("sn", "i", sn);
		MYSQL_ADD_FIELD("course_id", "s", course_id);
		MYSQL_ADD_FIELD("schedule_id", "s", schedule_id);
		MYSQL_ADD_FIELD("class_id", "s", class_id);
		MYSQL_ADD_FIELD("room_id", "s", room_id);
		MYSQL_ADD_FIELD("date", "s", date);
		MYSQL_ADD_FIELD("start_time", "s", start_time);
		MYSQL_ADD_FIELD("end_time", "s", end_time);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("dec_count", "i", dec_count);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("teach_type", "i", teach_type);
		MYSQL_ADD_FIELD("on_trial", "i", on_trial);
		MYSQL_ADD_FIELD("trial_result", "s", trial_result);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("close_time", "s", close_time);
		MYSQL_ADD_FIELD("close_operator", "s", close_operator);
		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);
		MYSQL_ADD_FIELD("bookable", "i", bookable);
		MYSQL_ADD_FIELD("school_id", "s", school_id);
		MYSQL_ADD_FIELD("org_id", "s", org_id);
	}
};

// LessonDO智能指针
typedef std::shared_ptr<LessonDO> PtrLessonDO;

/**
 * lesson_student DO
 */
class LessonStudentDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 课程id
	MYSQL_SYNTHESIZE(string, lesson_id, LessonId);

	// 班级id为空表示调课生
	MYSQL_SYNTHESIZE(int, class_id, ClassId);

	// 学员id
	MYSQL_SYNTHESIZE(string, student_id, StudentId);

	// 实扣课次
	MYSQL_SYNTHESIZE(int, dec_lesson_count, DecLessonCount);
	// 应扣课次
	MYSQL_SYNTHESIZE(int, lesson_count, LessonCount);

	// 点名的老师
	MYSQL_SYNTHESIZE(string, teacher_id, TeacherId);

	// 签到时间
	MYSQL_SYNTHESIZE(string, sign_time, SignTime);
	// 签到方式
	MYSQL_SYNTHESIZE(int, sign_type, SignType);
	// 签到结果
	MYSQL_SYNTHESIZE(int, sign_state, SignState);

	// 老师评分
	MYSQL_SYNTHESIZE(int, score, Score);

	// 老师评语
	MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
	// 评语时间
	MYSQL_SYNTHESIZE(string, evaluate_time, EvaluateTime);

	// 评语老师
	MYSQL_SYNTHESIZE(string, evaluate_teacher, EvaluateTeacher);

	// 实际消费课程
	MYSQL_SYNTHESIZE(string, consume_course_id, ConsumeCourseId);
	// 消费课程与学生关联表ID
	MYSQL_SYNTHESIZE(string, consume_student_course_id, ConsumeStudentCourseId);

	// 学生的顾问
	MYSQL_SYNTHESIZE(string, counselor, Counselor);

	// 加入时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);

	// 上课老师所属组织ID
	MYSQL_SYNTHESIZE(string, org_id, OrgId);

public:
	LessonStudentDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);

		MYSQL_ADD_FIELD("lesson_id", "s", lesson_id);

		MYSQL_ADD_FIELD("class_id", "i", class_id);

		MYSQL_ADD_FIELD("student_id", "s", student_id);

		MYSQL_ADD_FIELD("dec_lesson_count", "i", dec_lesson_count);
		MYSQL_ADD_FIELD("lesson_count", "i", lesson_count);

		MYSQL_ADD_FIELD("teacher_id", "s", teacher_id);

		MYSQL_ADD_FIELD("sign_time", "s", sign_time);
		MYSQL_ADD_FIELD("sign_type", "i", sign_type);
		MYSQL_ADD_FIELD("sign_state", "i", sign_state);

		MYSQL_ADD_FIELD("score", "i", score);

		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
		MYSQL_ADD_FIELD("evaluate_time", "s", evaluate_time);

		MYSQL_ADD_FIELD("evaluate_teacher", "s", evaluate_teacher);

		MYSQL_ADD_FIELD("consume_course_id", "s", consume_course_id);
		MYSQL_ADD_FIELD("consume_student_course_id", "s", consume_student_course_id);

		MYSQL_ADD_FIELD("counselor", "s", counselor);

		MYSQL_ADD_FIELD("add_time", "s", add_time);

		MYSQL_ADD_FIELD("org_id", "s", org_id);
	}
};

// LessonStudentDO智能指针
typedef std::shared_ptr<LessonStudentDO> PtrLessonStudentDO;

#endif // !_ATTENDANCEDO_H_