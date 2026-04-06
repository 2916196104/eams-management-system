#include "stdafx.h"
#include "GradeDAO.h"
#include "GradeMapper.h"



std::list<GradeDO> GradeDAO::selectWithPage()
{
	SqlParams params;
	string sql = "SELECT name FROM class_grade ";
	// 构建查询条件
	sql += "where deleted=0 ";
	// 构建排序语句
	sql += " ORDER BY sort_num ASC ";

	// 执行查询
	return sqlSession->executeQuery<GradeDO>(sql, GradeMapper(), params);
}