/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 14:41:24

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
#include "UserDAO.h"
#include "UserMapper.h"

uint64_t UserDAO::count(const UserQuery::Wrapper& query)
{
	string sql = "SELECT count(id) FROM sample_user ";
	SqlParams params;
	if (query->nickname)
	{
		sql += "WHERE nickname LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->nickname.getValue(""));
	}
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrUserDO> UserDAO::selectAll(const UserQuery::Wrapper& query)
{
	string sql = "SELECT su.id, su.nickname, su.age, su.id_card, su.avatar, sf.save_path, sf.name FROM sample_user su LEFT JOIN sample_file sf ON sf.id = su.avatar ";
	SqlParams params;
	if (query->nickname)
	{
		sql += "WHERE su.nickname LIKE CONCAT('%',?,'%') ";
		SQLPARAMS_PUSH(params, "s", std::string, query->nickname.getValue(""));
	}
	sql += "LIMIT ?,?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
	return sqlSession->executeQuery<PtrUserDO>(sql, UserMapper(), params);
}

PtrUserDO UserDAO::selectById(const string& id)
{
	string sql = "SELECT su.id, su.nickname, su.age, su.id_card, su.avatar, sf.save_path, sf.name FROM sample_user su, sample_file sf WHERE sf.id=su.avatar AND su.id = ?";
	return sqlSession->executeQueryOne<PtrUserDO>(sql, UserMapper(), "%s", id);
}
