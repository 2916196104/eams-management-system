#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/16 15:47:39

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
#ifndef _GET_COURSE_EVALUATION_MAPPER_H_
#define _GET_COURSE_EVALUATION_MAPPER_H_
#include "Mapper.h"
#include "domain/do/timetable/GetCourseEvaluation/GetCourseEvaluationDO.h"

class EvaluationViewMapper : public Mapper<PtrEvaluationViewDO>
{
public:
	PtrEvaluationViewDO mapper(ResultSet* resultSet) const override
	{
		PtrEvaluationViewDO evaluation = std::make_shared<EvaluationViewDO>();
		evaluation->setId(resultSet->getString("ID"));
		evaluation->setTime(resultSet->getString("EvaluationTime"));
		evaluation->setEvaluation(resultSet->getString("Evaluation"));
		evaluation->setSign(resultSet->getInt("Sign"));
		evaluation->setScore(resultSet->getInt("Score"));
		evaluation->setStudentId(resultSet->getInt("StudentID"));
		evaluation->setTeacherId(resultSet->getInt("TeacherID"));

		evaluation->setStudentName(resultSet->getString("StudentName"));
		evaluation->setTeacherName(resultSet->getString("TeacherName"));

		return evaluation;
	}
};

#endif // !_GET_COURSE_EVALUATION_MAPPER_H_