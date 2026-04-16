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
#ifndef _COURSE_DO_H_
#define _COURSE_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 课程套餐表 DO（对应 course 表）
 */
class CourseDO : public BaseDO
{
public:
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, subjectId, SubjectId);
	MYSQL_SYNTHESIZE(std::string, name, Name);
	MYSQL_SYNTHESIZE(int32_t, state, State);
	MYSQL_SYNTHESIZE(std::string, info, Info);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	MYSQL_SYNTHESIZE(uint32_t, expireMonths, ExpireMonths);
	MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);
	MYSQL_SYNTHESIZE(double, price, Price);
	MYSQL_SYNTHESIZE(std::string, unitName, UnitName);
	MYSQL_SYNTHESIZE(double, discount, Discount);
	MYSQL_SYNTHESIZE(uint32_t, lessonCount, LessonCount);
	MYSQL_SYNTHESIZE(int32_t, lessonType, LessonType);
	MYSQL_SYNTHESIZE(std::string, description, Description);
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	MYSQL_SYNTHESIZE(bool, bookable, Bookable);
	MYSQL_SYNTHESIZE(bool, forSale, ForSale);
	MYSQL_SYNTHESIZE(bool, recommend, Recommend);
	MYSQL_SYNTHESIZE(std::string, cover, Cover);
	MYSQL_SYNTHESIZE(std::string, closeDate, CloseDate);
	MYSQL_SYNTHESIZE(std::string, teacherInfo, TeacherInfo);
	MYSQL_SYNTHESIZE(std::string, serviceInfo, ServiceInfo);
	MYSQL_SYNTHESIZE(int32_t, storage, Storage);
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);
	MYSQL_SYNTHESIZE(double, salary, Salary);
	MYSQL_SYNTHESIZE(std::string, gradeIds, GradeIds);
	MYSQL_SYNTHESIZE(std::string, gradeNames, GradeNames);

public:
	CourseDO() : BaseDO("course")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD_NULLABLE("subject_id", "ll", subjectId, false);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("expire_months", "ui", expireMonths);
		MYSQL_ADD_FIELD("unit_price", "d", unitPrice);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("unit_name", "s", unitName);
		MYSQL_ADD_FIELD("discount", "d", discount);
		MYSQL_ADD_FIELD("lesson_count", "ui", lessonCount);
		MYSQL_ADD_FIELD("lesson_type", "i", lessonType);
		MYSQL_ADD_FIELD("description", "s", description);
		MYSQL_ADD_FIELD("deleted", "b", deleted);
		MYSQL_ADD_FIELD("bookable", "b", bookable);
		MYSQL_ADD_FIELD("for_sale", "b", forSale);
		MYSQL_ADD_FIELD("recommend", "b", recommend);
		MYSQL_ADD_FIELD("cover", "s", cover);
		MYSQL_ADD_FIELD("close_date", "dt", closeDate);
		MYSQL_ADD_FIELD("teacher_info", "s", teacherInfo);
		MYSQL_ADD_FIELD("service_info", "s", serviceInfo);
		MYSQL_ADD_FIELD("storage", "i", storage);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
		MYSQL_ADD_FIELD("salary", "d", salary);
		MYSQL_ADD_FIELD("grade_ids", "s", gradeIds);
		MYSQL_ADD_FIELD("grade_names", "s", gradeNames);
	}
};

#endif // !_COURSE_DO_H_
