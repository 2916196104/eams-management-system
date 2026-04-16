#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/28

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
#ifndef __RECORDNAME_SERVICE_H__
#define __RECORDNAME_SERVICE_H__

#include "domain/GlobalInclude.h"
#include "domain/query/timetable/GetDetailCSQuery.h"
#include "domain/query/timetable/GetStuListQuery.h"
#include "domain/query/timetable/TimetableQuery.h"
#include "domain/dto/timetable/TimetableDTO.h"
#include "domain/vo/timetable/GetDetailCSVO.h"
#include "domain/vo/timetable/GetStuListVO.h"
#include "dao/class_student/ClassStudentDao.h"

class RecordnameService
{
public:
	GetDetailCSJsonVO::Wrapper getDetailCS(const GetDetailCSQuery::Wrapper& query);
	GetStuListJsonVO::Wrapper getCSStuList(const GetStuListQuery::Wrapper& query);
};

class ClassStudentService
{
public:
	// 1. 获取学员列表 (条件+分页)
	PageDTO<TimetableStudentDTO::Wrapper>::Wrapper getStudentList(const StuListQuery::Wrapper& query);

	// 2. 添加学员到课次 (批量插入)
	bool addStudentToLesson(const AddStudentToLessonDTO::Wrapper& dto);

	// 3. 获取学员课程列表
	oatpp::List<TimetableStudentCourseDTO::Wrapper> getStudentCourseList(const StuClassQuery::Wrapper& query);
};

#endif // __RECORDNAME_SERVICE_H__
