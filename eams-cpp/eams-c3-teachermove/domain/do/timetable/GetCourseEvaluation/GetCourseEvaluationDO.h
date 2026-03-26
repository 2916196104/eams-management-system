#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/17 16:25:30

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
#ifndef _GET_COURSE_EVALUATION_DO_H
#define _GET_COURSE_EVALUATION_DO_H
#include "../../DoInclude.h"


class EvaluationDO : public BaseDO
{
	// 唯一编号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 点评时间
	MYSQL_SYNTHESIZE(string, time, Time);
	// 点评评语
	MYSQL_SYNTHESIZE(string, evaluation, Evaluation);
	// 点评老师
	MYSQL_SYNTHESIZE(int, teacherId, TeacherId);
	// 签到方式
	MYSQL_SYNTHESIZE(int, sign, Sign);
	// 评分分数
	MYSQL_SYNTHESIZE(int, score, Score);
	// 学生ID
	MYSQL_SYNTHESIZE(int, studentId, StudentId);

public:
	EvaluationDO() : BaseDO("lesson_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("evaluation", "s", evaluation);
		MYSQL_ADD_FIELD("teacher_id", "s", teacherId);
		MYSQL_ADD_FIELD("evaluate_time", "s", time);
		MYSQL_ADD_FIELD("sign_type", "s", sign);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("student_id", "i", studentId);
	}
};


// 定义一个智能指针方便使用
typedef std::shared_ptr<EvaluationDO> PtrEvaluationDO;


/**
 * 评分视图对象，关联一些外表的字段
 */
class EvaluationViewDO : public EvaluationDO {
	// 学生名称
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	// 老师名称
	MYSQL_SYNTHESIZE(string, teacherName, TeacherName);
};


// 定义一个智能指针别名方便使用
typedef std::shared_ptr<EvaluationViewDO> PtrEvaluationViewDO;



#endif // !_GET_COURSE_EVALUATION_DO_H