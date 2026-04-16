#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:08:56

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
#ifndef _ATTENDANCESEERVICE_H_
#define _ATTENDANCESEERVICE_H_
#include "../../domain/vo/attendance-records/attendanceVO.h"
#include "../../domain/query/attendance-records/attendancequery.h"
#include "../../domain/dto/attendance-records/attendanceDTO.h"

/**
 * Lesson_Student服务实现
 */
class Lesson_StudentService
{
public:
	// 分页查询所有数据
	attendance_recordsPageDTO::Wrapper listAll(const attendance_recordsQuery::Wrapper& query);
};

/**
* Teach_Evaluation服务实现
*/
class Teach_EvaluationService
{
public:
	// 保存数据
	std::string saveData(const attendance_recordsEvaluateDTO::Wrapper& dto);
};

#endif // !_ATTENDANCESEERVICE_H_

