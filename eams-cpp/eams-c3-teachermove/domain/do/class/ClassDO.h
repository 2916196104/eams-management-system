#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/03/15

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
#ifndef _CLASS_DO_H_
#define _CLASS_DO_H_

#include "BaseDO.h"
#include "SqlHelper.h"

/**
 * 班级表 DO（对应 class 表）
 */
class ClassDO : public BaseDO
{
public:
	// 主键 id - bigint unsigned
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 班级名
	MYSQL_SYNTHESIZE(std::string, name, Name);
	// 课程
	MYSQL_SYNTHESIZE(int64_t, courseId, CourseId);
	// 教室
	MYSQL_SYNTHESIZE(int64_t, classroomId, ClassroomId);
	// 创建人
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(int64_t, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	// 编辑时间
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	// 班级负责人
	MYSQL_SYNTHESIZE(int64_t, teacherId, TeacherId);
	// 排课备注
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	// 是否完结
	MYSQL_SYNTHESIZE(bool, beOver, BeOver);
	// 完结时间
	MYSQL_SYNTHESIZE(std::string, overTime, OverTime);
	// 完结操作人
	MYSQL_SYNTHESIZE(int64_t, overOperator, OverOperator);
	// 计划开班日期
	MYSQL_SYNTHESIZE(std::string, startDate, StartDate);
	// 计划结业日期
	MYSQL_SYNTHESIZE(std::string, endDate, EndDate);
	// 预招人数
	MYSQL_SYNTHESIZE(int32_t, plannedStudentCount, PlannedStudentCount);
	// 预排课次数
	MYSQL_SYNTHESIZE(int32_t, plannedLessonCount, PlannedLessonCount);
	// 创建者所属学校id
	MYSQL_SYNTHESIZE(int64_t, schoolId, SchoolId);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(int64_t, orgId, OrgId);
	// 年级ID
	MYSQL_SYNTHESIZE(int32_t, gradeId, GradeId);

public:
	ClassDO() : BaseDO("class")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		// 普通字段
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("course_id", "ll", courseId, false);
		MYSQL_ADD_FIELD("classroom_id", "ll", classroomId);
		MYSQL_ADD_FIELD("creator", "ll", creator);
		MYSQL_ADD_FIELD("editor", "ll", editor);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("deleted", "b", deleted);
		MYSQL_ADD_FIELD("teacher_id", "ll", teacherId);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("be_over", "b", beOver);
		MYSQL_ADD_FIELD("over_time", "dt", overTime);
		MYSQL_ADD_FIELD("over_operator", "ll", overOperator);
		MYSQL_ADD_FIELD("start_date", "dt", startDate);
		MYSQL_ADD_FIELD("end_date", "dt", endDate);
		MYSQL_ADD_FIELD("planned_student_count", "i", plannedStudentCount);
		MYSQL_ADD_FIELD("planned_lesson_count", "i", plannedLessonCount);
		MYSQL_ADD_FIELD("school_id", "ll", schoolId);
		MYSQL_ADD_FIELD("org_id", "ll", orgId);
		MYSQL_ADD_FIELD("grade_id", "i", gradeId);
	}
};

#endif // !_CLASS_DO_H_
