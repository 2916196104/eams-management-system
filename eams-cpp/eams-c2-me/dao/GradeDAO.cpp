#include "stdafx.h"
#include "GradeDAO.h"
#include "GradeMapper.h"

std::string GradeDAO::queryConditionBuilder(const GradeQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	sqlCondition << " AND deleted=0";
	return sqlCondition.str();
}

uint64_t GradeDAO::count(const GradeQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM class_grade ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<GradeDO> GradeDAO::selectWithPage(const GradeQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT name FROM class_grade ";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 构建排序语句
	sql += " ORDER BY sort_num ASC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	// 执行查询
	return sqlSession->executeQuery<GradeDO>(sql, GradeMapper(), params);
}