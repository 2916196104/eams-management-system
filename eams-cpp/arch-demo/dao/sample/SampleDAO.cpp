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
#include "SampleDAO.h"
#include "SampleMapper.h"

std::string SampleDAO::queryConditionBuilder(const SampleQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name) {

		sqlCondition << " AND `name`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->sex) {

		sqlCondition << " AND sex=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
	}
	if (query->age) {

		sqlCondition << " AND age=?";
		SQLPARAMS_PUSH(params, "i", int, query->age.getValue(0));
	}
	return sqlCondition.str();
}

uint64_t SampleDAO::count(const SampleQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM sample ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<SampleDO> SampleDAO::selectWithPage(const SampleQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT id,name,sex,age FROM sample ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

	// 执行查询
	return sqlSession->executeQuery<SampleDO>(sql, SampleMapper(), params);
}

std::list<SampleDO> SampleDAO::selectByName(const string& name)
{
	string sql = "SELECT id,name,sex,age FROM sample WHERE `name` LIKE CONCAT('%',?,'%')";
	return sqlSession->executeQuery<SampleDO>(sql, SampleMapper(), "%s", name);
}

PtrSampleDO SampleDAO::selectById(std::string id)
{
	string sql = "SELECT id,name,sex,age FROM sample WHERE `id`=?";
	return sqlSession->executeQueryOne<PtrSampleDO>(sql, PtrSampleMapper(), "%s", id);
}
