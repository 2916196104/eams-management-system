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
#include "stdafx.h"
#include "GradeRecordDao.h"
#include "GradeRecordMapper.h"

std::string GradeRecordDao::queryConditionBuilder(const GradeRecordQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->gradeId) {
		sqlCondition << " AND grade_id=?";
		SQLPARAMS_PUSH(params, "bi", int64_t, (int64_t)query->gradeId.getValue(0));
	}
	if (query->studentId) {
		sqlCondition << " AND student_id=?";
		SQLPARAMS_PUSH(params, "bi", int64_t, (int64_t)query->studentId.getValue(0));
	}
	if (query->score) {
		sqlCondition << " AND score=?";
		SQLPARAMS_PUSH(params, "i", int32_t, (int32_t)query->score.getValue(0));
	}
	if (query->creator) {
		sqlCondition << " AND creator=?";
		SQLPARAMS_PUSH(params, "bi", int64_t, (int64_t)query->creator.getValue(0));
	}
	if (query->startAddTime) {
		sqlCondition << " AND add_time>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startAddTime.getValue(""));
	}
	if (query->endAddTime) {
		sqlCondition << " AND add_time<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endAddTime.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t GradeRecordDao::count(const GradeRecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM grade_record ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<GradeRecordDO> GradeRecordDao::selectWithPage(const GradeRecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,grade_id,student_id,score,add_time,creator FROM grade_record ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY add_time DESC, id DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<GradeRecordDO>(sql, GradeRecordMapper(), params);
}

std::list<GradeRecordDO> GradeRecordDao::selectByStudentId(const string& studentId)
{
	string sql = "SELECT id,grade_id,student_id,score,add_time,creator FROM grade_record WHERE student_id=?";
	return sqlSession->executeQuery<GradeRecordDO>(sql, GradeRecordMapper(), "%s", studentId);
}

PtrGradeRecordDO GradeRecordDao::selectById(std::string id)
{
	string sql = "SELECT id,grade_id,student_id,score,add_time,creator FROM grade_record WHERE id=?";
	return sqlSession->executeQueryOne<PtrGradeRecordDO>(sql, PtrGradeRecordMapper(), "%s", id);
}
