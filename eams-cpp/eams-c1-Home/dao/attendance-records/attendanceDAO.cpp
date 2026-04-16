/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:26:52

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
#include "stdafx.h"
#include "attendanceDAO.h"
#include "attendanceMapper.h"

std::string Lesson_StudentDAO::queryConditionBuilder(
	const attendance_recordsQuery::Wrapper& query,
	SqlParams& params)
{
	std::stringstream sqlCondition;
	sqlCondition << " WHERE 1=1 ";

	// 必须：学生id过滤
	if (query->student_id) {
		sqlCondition << " AND t1.student_id=? ";
		SQLPARAMS_PUSH(params, "i", uint64_t, query->student_id.getValue(0));
	}
	else {
		// 如果 Wrapper 没有 student_id，就改为固定 23
		sqlCondition << " AND t1.student_id=23 ";
	}

	// 必须：只取签到结果>0
	sqlCondition << " AND t1.sign_state > 0 ";

	return sqlCondition.str();
}

uint64_t Lesson_StudentDAO::count(const attendance_recordsQuery::Wrapper& query)
{
	SqlParams params;

	// 只统计 lesson_student 记录条数
	std::string sql = "SELECT COUNT(*) FROM lesson_student t1 ";
	sql += queryConditionBuilder(query, params);

	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<Lesson_StudentDO> Lesson_StudentDAO::selectWithPage(
	const attendance_recordsQuery::Wrapper& query)
{
	SqlParams params;

	std::string sql =
		"SELECT "
		"  t1.dec_lesson_count, "
		"  t1.sign_time, "
		"  t1.sign_state, "
		"  t4.date, t4.start_time, t4.end_time, "
		"  t5.name AS course_name, "
		"  t4.title AS lesson_title, "
		"  (t1.sign_state in (1,2)) AS can_evaluate "
		"FROM lesson_student t1 "
		"LEFT JOIN lesson t4 ON t4.id = t1.lesson_id "
		"LEFT JOIN course t5 ON t5.id = t4.course_id ";

	sql += queryConditionBuilder(query, params);

	sql += " ORDER BY t1.id DESC ";

	// 分页
	uint64_t offset = (query->pageIndex - 1) * query->pageSize;
	sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);

	return sqlSession->executeQuery<Lesson_StudentDO>(sql, Lesson_StudentMapper(), params);
}


bool Teach_EvaluationDAO::insert(const Ptrteach_evaluationDO data)
{
	if(!data->getPrimaryField()->get())
		throw std::runtime_error("Primary key value is required for insert operation.");
	SqlParams params;
	std::string sql =
		"INSERT INTO teach_evaluation ("
		"  id, lesson_id, teacher_id, score1, score2, score3, score4, content, add_time, student_id, anonymity "
		") VALUES ("
		"  ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? "
		")";
	SQLPARAMS_PUSH(params, "ull", uint64_t, data->getId());
	SQLPARAMS_PUSH(params, "ull", uint64_t, data->getLessonId());
	SQLPARAMS_PUSH(params, "ull", uint64_t, data->getTeacherId());
	SQLPARAMS_PUSH(params, "i", uint32_t, data->getScore1());
	SQLPARAMS_PUSH(params, "i", uint32_t, data->getScore2());
	SQLPARAMS_PUSH(params, "i", uint32_t, data->getScore3());
	SQLPARAMS_PUSH(params, "i", uint32_t, data->getScore4());
	SQLPARAMS_PUSH(params, "s", std::string, data->getContent());
	SQLPARAMS_PUSH(params, "s", std::string, data->getAddTime());
	SQLPARAMS_PUSH(params, "ull", uint64_t, data->getStudentId());
	SQLPARAMS_PUSH(params, "ull", uint64_t, data->getAnonymity());
	return sqlSession->executeUpdate(sql, params);
}