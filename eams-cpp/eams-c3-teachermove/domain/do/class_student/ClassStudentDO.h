#pragma once
/*
 Copyright Zero One Star. All rights reserved.

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
#ifndef _CLASS_STUDENT_DO_H_
#define _CLASS_STUDENT_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 班级学员表 DO（对应 class_student 表）
 */
class ClassStudentDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, classId, ClassId);
	MYSQL_SYNTHESIZE(int64_t, studentId, StudentId);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int32_t, reason, Reason);
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(int64_t, consumeCourseId, ConsumeCourseId);

public:
	ClassStudentDO() : BaseDO("class_student")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "ull", id);

		// ---------------- 必填字段 (NOT NULL) ----------------
		MYSQL_ADD_FIELD("class_id", "ll", classId);
		MYSQL_ADD_FIELD("student_id", "ll", studentId);
		MYSQL_ADD_FIELD("consume_course_id", "ll", consumeCourseId);

		// ---------------- 选填字段 (NULLABLE) ----------------
		MYSQL_ADD_FIELD_NULLABLE("add_time", "dt", addTime, true);
		MYSQL_ADD_FIELD_NULLABLE("creator", "ll", creator, true);
		MYSQL_ADD_FIELD_NULLABLE("reason", "i", reason, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted", "b", deleted, true);
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, true);
	}
};

#endif // !_CLASS_STUDENT_DO_H_
