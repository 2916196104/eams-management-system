#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:47:24

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

#ifndef _STUDENTLESSONCOUNTLOG_H_
#define _STUDENTLESSONCOUNTLOG_H_
#include "../../DoInclude.h"
#include "SqlHelper.h"

class StudentLessonCountLogDO :public BaseDO
{
	//文件唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	//学生学号
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	//课程号
	MYSQL_SYNTHESIZE(string, courseId, CourseId);
	//课次号
	MYSQL_SYNTHESIZE(string, lessonId, LessonId);
	//变更课次数
	MYSQL_SYNTHESIZE(int, changeCount, ChangeCount);
	//剩余数量
	MYSQL_SYNTHESIZE(int, remainingCount, RemainingCount);
	//操作人
	MYSQL_SYNTHESIZE(string, staffId, StaffId);
	//时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	//变更阶段
	MYSQL_SYNTHESIZE(string, stage, Stage);
	//
	MYSQL_SYNTHESIZE(string, remark, Remark);
public:
	StudentLessonCountLogDO() :BaseDO("student_lesson_count_log")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("student_id", "s", studentId, false);
		MYSQL_ADD_FIELD_NULLABLE("course_id", "s", courseId, false);
		MYSQL_ADD_FIELD("lesson_id", "s", lessonId);
		MYSQL_ADD_FIELD("change_count", "i", changeCount);
		MYSQL_ADD_FIELD("remaining_count", "i", remainingCount);
		MYSQL_ADD_FIELD("staff_id", "s", staffId);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("stage", "s", stage);
		MYSQL_ADD_FIELD("remark", "s", remark);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<StudentLessonCountLogDO> PtrStudentLessonCountLogDO;

/**
 * 文件视图对象，关联一些外表的字段
 */
class StudentLessonCountLogViewDO : public StudentLessonCountLogDO {
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	MYSQL_SYNTHESIZE(string, staffName, StaffName);
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<StudentLessonCountLogViewDO> PtrStudentLessonCountLogViewDO;

#endif // !_FILEDO_H_