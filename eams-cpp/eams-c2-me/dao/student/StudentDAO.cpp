#include "stdafx.h"
#include "StudentDAO.h"
#include "StudentMapper.h"
#include "SqlSession.h"

//分页查询学生列表
std::list<PtrStudentDO> StudentDAO::selectAll(const StudentQuery::Wrapper& query)
{
	string sql = "SELECT * FROM student WHERE deleted = 0 ";//末尾加空格 防止拼接错误
	SqlParams params;

	//拼接分页
	sql += "LIMIT ?,?";
	// 计算分页偏移量 (当前页-1)*每页条数
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));
 
	// 执行查询，通过 StudentMapper 映射结果集为 DO 列表
	return sqlSession->executeQuery<PtrStudentDO>(sql, StudentMapper(), params);


}


//统计学生总数

uint64_t StudentDAO::count(const StudentQuery::Wrapper& query)
{
	string sql = "SELECT count(id) FROM student WHERE deleted = 0 ";
	SqlParams params;
 
	return sqlSession->executeQueryNumerical(sql, params);
}