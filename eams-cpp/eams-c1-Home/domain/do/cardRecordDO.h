#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: your_name
 @Date: 2024/05/24 10:00:00

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
#ifndef _CARD_RECORD_DO_H
#define _CARD_RECORD_DO_H
#include "./DoInclude.h"

/**
 * 课程体验卡领取记录数据实体
 */
class cardRecordDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(unsigned long long, id, Id);
	// 体验卡ID
	MYSQL_SYNTHESIZE(long, trialId, TrialId);
	// 学生ID
	MYSQL_SYNTHESIZE(long, studentId, StudentId);
	// 课程ID
	MYSQL_SYNTHESIZE(long, courseId, CourseId);
	// 学生账号ID
	MYSQL_SYNTHESIZE(long, userId, UserId);
	// 生成的学生课程关联ID
	MYSQL_SYNTHESIZE(long, studentCourseId, StudentCourseId);
	// 领取时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 到期时间
	MYSQL_SYNTHESIZE(string, endDate, EndDate);
	// 领取到的课时数量
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 学生所属学校ID
	MYSQL_SYNTHESIZE(long, schoolId, SchoolId);
	// 学生的顾问
	MYSQL_SYNTHESIZE(long, counselor, Counselor);

public:
	cardRecordDO() : BaseDO("course_trial_record")
	{
		MYSQL_ADD_FIELD_PK("id", "ui", id);
		MYSQL_ADD_FIELD("trial_id", "i", trialId);
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		MYSQL_ADD_FIELD("course_id", "i", courseId);
		MYSQL_ADD_FIELD("user_id", "i", userId);
		MYSQL_ADD_FIELD("student_course_id", "i", studentCourseId);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("expired_date", "s", endDate);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("school_id", "i", schoolId);
		MYSQL_ADD_FIELD("counselor", "i", counselor);
	}
};

// cardRecordDO指针类型定义
typedef std::shared_ptr<cardRecordDO> PtrCardRecordDO;
#endif // !_CARD_RECORD_DO_