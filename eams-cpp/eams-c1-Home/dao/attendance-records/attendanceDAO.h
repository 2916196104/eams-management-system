#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

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
#ifndef _ATTENDANCEDAO_H_
#define _ATTENDANCEDAO_H_
#include "BaseDAO.h"
#include "../../domain/do/attendance-records/attendanceDO.h"
#include "../../domain/query/attendance-records/attendancequery.h"

/**
 * Lesson_Student数据库操作实现
 */
class Lesson_StudentDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const attendance_recordsQuery::Wrapper& query, SqlParams& params);
public:
	// 统计数据条数
	uint64_t count(const attendance_recordsQuery::Wrapper& query);
	// 分页查询数据
	std::list<Lesson_StudentDO> selectWithPage(const attendance_recordsQuery::Wrapper& query);
};

/**
* Teach_Evaluation数据库操作实现
*/
class Teach_EvaluationDAO : public BaseDAO
{
public:
	// 插入数据
	bool insert(const Ptrteach_evaluationDO bd);
};

#endif // !_ATTENDANCEDAO_H_