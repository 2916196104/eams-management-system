#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

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
#ifndef _ATTENDANCEMAPPER_H_
#define _ATTENDANCEMAPPER_H_

#include "Mapper.h"
#include "../../domain/do/attendance-records/attendanceDO.h"

/**
 * lesson_student字段匹配映射
 */
class Lesson_StudentMapper : public Mapper<Lesson_StudentDO>
{
public:
	Lesson_StudentDO mapper(ResultSet* resultSet) const override
	{
		Lesson_StudentDO data;
		data.setDecLessonCount(resultSet->getInt("dec_lesson_count"));
		data.setSignTime(resultSet->getString("sign_time"));
		data.setSignState(resultSet->getInt("sign_state"));
		data.setDate(resultSet->getString("date"));
		data.setStartTime(resultSet->getString("start_time"));
		data.setEndTime(resultSet->getString("end_time"));
		data.setCourseName(resultSet->getString("course_name"));
		data.setLessonTitle(resultSet->getString("lesson_title"));
		data.setCanEvaluate(resultSet->getBoolean("can_evaluate"));
		return data;
	}
};

/**
* teach_eavlution字段匹配映射
*/
class Teach_EvaluationMapper : public Mapper<Teach_EvaluationDO>
{
public:
	Teach_EvaluationDO mapper(ResultSet* resultSet) const override
	{
		Teach_EvaluationDO data;
		data.setLessonId(resultSet->getInt("lesson_id"));
		data.setTeacherId(resultSet->getInt("teacher_id"));
		data.setScore1(resultSet->getInt("score1"));
		data.setScore2(resultSet->getInt("score2"));
		data.setScore3(resultSet->getInt("score3"));
		data.setScore4(resultSet->getInt("score4"));
		data.setContent(resultSet->getString("content"));
		data.setAddTime(resultSet->getString("add_time"));
		data.setStudentId(resultSet->getInt("student_id"));
		data.setAnonymity(resultSet->getInt("anonymity"));
		return data;
	}
};


/**
* teach_eavlution字段匹配映射-创建智能指针对象
*/
class PtrTeach_EvaluationMapper : public Mapper<Ptrteach_evaluationDO>
{
public:
	Ptrteach_evaluationDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<Teach_EvaluationDO>();
		data->setLessonId(resultSet->getInt("lesson_id"));
		data->setTeacherId(resultSet->getInt("teacher_id"));
		data->setScore1(resultSet->getInt("score1"));
		data->setScore2(resultSet->getInt("score2"));
		data->setScore3(resultSet->getInt("score3"));
		data->setScore4(resultSet->getInt("score4"));
		data->setContent(resultSet->getString("content"));
		data->setAddTime(resultSet->getString("add_time"));
		data->setStudentId(resultSet->getInt("student_id"));
		data->setAnonymity(resultSet->getInt("anonymity"));
		return data;
	}
};

#endif // !_ATTENDANCEMAPPER_H_