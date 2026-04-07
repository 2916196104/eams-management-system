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
#ifndef _STUDENTLESSONCOUNTLOGMAPPER_H_
#define _STUDENTLESSONCOUNTLOGMAPPER_H_
#include "Mapper.h"
#include "domain/do/AddStudent/LessonLog/StudentLessonCountLogDO.h"

class StudentLessonCountLogViewMapper : public Mapper<PtrStudentLessonCountLogViewDO>
{
public:
	PtrStudentLessonCountLogViewDO mapper(ResultSet* resultSet) const override
	{
		PtrStudentLessonCountLogViewDO file = std::make_shared<StudentLessonCountLogViewDO>();
		// Ó³Éä»ù´¡×Ö¶Î
		file->setId(resultSet->getString("id"));
		file->setStudentId(resultSet->getString("student_id"));
		file->setCourseId(resultSet->getString("course_id"));
		file->setLessonId(resultSet->getString("lesson_id"));
		file->setChangeCount(resultSet->getInt("change_count"));
		file->setRemainingCount(resultSet->getInt("remaining_count"));
		file->setStaffId(resultSet->getString("staff_id"));
		file->setAddTime(resultSet->getString("add_time"));
		file->setStage(resultSet->getString("stage"));
		file->setRemark(resultSet->getString("log_remark"));
		// Ó³Éä¹ØÁª×Ö¶Î(ÊÓÍ¼DOÌØÓÐ)
		file->setStudentName(resultSet->getString("student_name"));
		file->setCourseName(resultSet->getString("course_name"));
		file->setStaffName(resultSet->getString("staff_name"));

		return file;
	}
};

#endif // !_STUDENTLESSONCOUNTLOGMAPPER_H_