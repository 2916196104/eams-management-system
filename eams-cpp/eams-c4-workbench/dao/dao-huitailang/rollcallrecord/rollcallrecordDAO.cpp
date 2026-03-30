#include "stdafx.h"
#include "rollcallrecordDAO.h"
#include "rollcallrecordMapper.h"


std::string RollcallrecordDAO::queryConditionBuilder(const RollcallQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->teacherId)
	{
		sqlCondition << " AND t1.teacher_id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->teacherId.getValue(""));
	}
	if (query->courseId)
	{
		sqlCondition << " AND t1.lesson_id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->courseId.getValue(""));
	}

	return sqlCondition.str();
}

uint64_t RollcallrecordDAO::count(const RollcallQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM lesson_student t1";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<RollcallrecordViewDO> RollcallrecordDAO::selectWithPage(const RollcallQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT t2.name,t1.sign_time,t1.sign_state FROM lesson_student t1,student t2";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	//添加多表查询条件
	sql += " AND t1.student_id=t2.id";
	// 构建排序语句
	sql += " ORDER BY t1.sign_time DESC, t1.id ASC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	//std::cout << sql << endl;
	// 执行查询
	return sqlSession->executeQuery<RollcallrecordViewDO>(sql, RollcallrecordMapper(), params);
}

