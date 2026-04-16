/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 15:54:59

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
#include "dao/AddStudent/RegistRecord/RegistRecordViewDAO.h"
#include "dao/AddStudent/RegistRecord/RegistRecordViewMapper.h"
#include "SqlHelper.h"

std::string RegistRecordViewDAO::queryConditionBuilder(const RegistRecordQuery::Wrapper& query, SqlParams& params) {
	stringstream sqlCondition;
	sqlCondition << " WHERE sc.deleted = 0"; // 加前置空格，指定别名
	if (query->studentName) {
		sqlCondition << " AND s.name=?"; // 加空格，修正列名
		SQLPARAMS_PUSH(params,"s",std::string,query->studentName.getValue(""));
	}
	//if (query->payOff) {
	//	sqlCondition << " AND sc.pay_off=?"; // 加空格，修正列名
	//	SQLPARAMS_PUSH(params, "s", std::string, query->payOff.getValue(""));
	//}
	return sqlCondition.str();
}

// 统计数据条数
uint64_t RegistRecordViewDAO::count(const RegistRecordQuery::Wrapper& query) {
	SqlParams params;
	// 加上必要的关联，以便 count 能够处理条件中的外表字段
	string sql = R"(SELECT count(*) FROM student_course sc 
		LEFT JOIN student s ON sc.student_id = s.id
	)";
	//构建查询条件
	sql += queryConditionBuilder(query,params);
	//执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询数据
std::list<RegistRecordViewDO> RegistRecordViewDAO::selectWithPage(const RegistRecordQuery::Wrapper& query) {
	SqlParams params;
	string sql = R"(SELECT 
		sc.id,
		s.name AS student_name,
		c.name AS course_name,
		sc.start_date,
		sc.expire_date,
		sc.paid_amount
		FROM 
		student_course sc 
		LEFT JOIN student s ON sc.student_id = s.id
		LEFT JOIN course c ON sc.course_id = c.id
		)";
	//构建查询条件
	sql += queryConditionBuilder(query, params);
	//构建排序语句 (修正单引号问题)
	sql += " ORDER BY IFNULL(sc.add_time, sc.edit_time) DESC, sc.id DESC ";
	// 构建分页条件 (补充缺失的空格)
	sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + ", " + std::to_string(query->pageSize);

	//执行查询
	auto ptrList = sqlSession->executeQuery<PtrRegistRecordViewDO>(sql, RegistRecordPageViewMapper(), params);
	std::list<RegistRecordViewDO> res;
	for (auto& ptr : ptrList) {
		if (ptr) {
			res.push_back(*ptr);
		}
	}
	std::cout << "========= 数据库查到了 " << res.size() << " 条数据 =========" << std::endl;
	return res;
}
//// 通过姓名查询数据
//std::list<RegistRecordViewDO> RegistRecordViewDAO::selectByName(const string& name) {
//	
//}
// 通过ID查询数据
PtrRegistRecordViewDO RegistRecordViewDAO::selectById(std::string id) {
	string sql = R"(SELECT 
        sc.*,
        s.name AS student_name,
        sb.name AS subject_name,
        c.name AS course_name,
        slcl.remaining_count,
        r.*
        FROM student_course sc 
        LEFT JOIN student s ON sc.student_id = s.id
        LEFT JOIN course c ON sc.course_id = c.id
        LEFT JOIN subject sb ON sc.subject_id = sb.id
        LEFT JOIN refund r ON sc.id = r.student_course_id
        LEFT JOIN student_lesson_count_log slcl ON sc.student_id=slcl.student_id
        WHERE sc.id = ?)"; 
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, id); // 安全地绑定参数
	auto result = sqlSession->executeQueryOne<PtrRegistRecordViewDO>(sql, RegistRecordViewMapper(), params);
	return result;
}