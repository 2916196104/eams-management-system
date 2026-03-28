#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/24

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
#ifndef _CLASS_MAPPER_H_
#define _CLASS_MAPPER_H_

#include "Mapper.h"
#include "domain/do/class/ClassDO.h"

class ClassMapper : public Mapper<ClassDO>
{
public:
	ClassDO mapper(ResultSet* resultSet) const override
	{
		ClassDO data;

		if (!resultSet->isNull("id")) data.setId(resultSet->getUInt64("id"));
		if (!resultSet->isNull("name")) data.setName(resultSet->getString("name"));
		if (!resultSet->isNull("course_id")) data.setCourseId(resultSet->getInt64("course_id"));
		if (!resultSet->isNull("classroom_id")) data.setClassroomId(resultSet->getInt64("classroom_id"));
		if (!resultSet->isNull("creator")) data.setCreator(resultSet->getInt64("creator"));
		if (!resultSet->isNull("editor")) data.setEditor(resultSet->getInt64("editor"));
		if (!resultSet->isNull("add_time")) data.setAddTime(resultSet->getString("add_time"));
		if (!resultSet->isNull("edit_time")) data.setEditTime(resultSet->getString("edit_time"));
		if (!resultSet->isNull("deleted")) data.setDeleted(resultSet->getBoolean("deleted"));
		if (!resultSet->isNull("teacher_id")) data.setTeacherId(resultSet->getInt64("teacher_id"));
		if (!resultSet->isNull("remark")) data.setRemark(resultSet->getString("remark"));
		if (!resultSet->isNull("be_over")) data.setBeOver(resultSet->getBoolean("be_over"));
		if (!resultSet->isNull("over_time")) data.setOverTime(resultSet->getString("over_time"));
		if (!resultSet->isNull("over_operator")) data.setOverOperator(resultSet->getInt64("over_operator"));
		if (!resultSet->isNull("start_date")) data.setStartDate(resultSet->getString("start_date"));
		if (!resultSet->isNull("end_date")) data.setEndDate(resultSet->getString("end_date"));
		if (!resultSet->isNull("planned_student_count")) data.setPlannedStudentCount(resultSet->getInt("planned_student_count"));
		if (!resultSet->isNull("planned_lesson_count")) data.setPlannedLessonCount(resultSet->getInt("planned_lesson_count"));
		if (!resultSet->isNull("school_id")) data.setSchoolId(resultSet->getInt64("school_id"));
		if (!resultSet->isNull("org_id")) data.setOrgId(resultSet->getInt64("org_id"));
		if (!resultSet->isNull("grade_id")) data.setGradeId(resultSet->getInt("grade_id"));

		return data;
	}
};

#endif // !_CLASS_MAPPER_H_