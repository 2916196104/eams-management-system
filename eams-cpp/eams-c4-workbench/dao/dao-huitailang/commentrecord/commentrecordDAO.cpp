#include "stdafx.h"
#include "commentrecordDAO.h"
#include "commentrecordMapper.h"



std::string CommentrecordDAO::queryConditionBuilder(const CommentrecordQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->teacherId)
	{
		sqlCondition << " AND t1.teacher_id=?";
		SQLPARAMS_PUSH(params, "s", std::string , query->teacherId.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t CommentrecordDAO::count(const CommentrecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT(*) FROM teach_evaluation t1";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 执行查询
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<CommentrecordViewDO> CommentrecordDAO::selectWithPage(const CommentrecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT t1.id,t1.teacher_id,t1.score1,t1.content,t1.add_time,t1.student_id,t1.anonymity,t2.name, " 
		"TIMESTAMPDIFF(YEAR, t2.birthday, CURDATE()) - "
		"(DATE_FORMAT(CURDATE(), '%m%d') < DATE_FORMAT(t2.birthday, '%m%d')) AS age "
		"FROM teach_evaluation t1,student t2";
	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	//添加多表查询条件
	sql += " AND t1.student_id=t2.id";
	// 构建排序语句
	sql += " ORDER BY t1.add_time DESC, t1.id ASC ";
	// 构建分页条件
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	//std::cout << sql << endl;
	// 执行查询
	return sqlSession->executeQuery<CommentrecordViewDO>(sql, CommentrecordMapper(), params);
}



