#include "stdafx.h"
#include "StudentDAO.h"
#include "SqlSession.h"

bool StudentDAO::deleteById(const uint64_t & id)
{
	// ? 是参数占位符，必须用 SqlParams 绑定真实值，防止 SQL 注入
	string sql = "UPDATE student SET deleted=1 WHERE id=? ";
	// 创建参数容器：用来装要绑定到 SQL 占位符上的参数
	SqlParams params;
	SQLPARAMS_PUSH(params, "ull", uint64_t, id);
	// 参数容器， 数据库类型标识（unsigned long long，对应 uint64_t），C++ 变量类型，要绑定的真实参数值   
	//使用这种方式可以安全地将参数绑定到第一个?上
	auto aff = sqlSession->executeUpdate(sql, params);
	//查看影响行数
	return (aff > 0) ? true : false;
 
}
