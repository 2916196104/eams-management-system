#include "stdafx.h"
#include "userDAO.h"
#include "userMapper.h"


std::list<UserDO> UserDAO::QueryUid(std::string phone)
{
	SqlParams params;
	string sql = "SELECT id,mobile FROM user where mobile = ?";
	SQLPARAMS_PUSH(params, "s", std::string, phone);
	// Ö´ÐÐ²éÑ¯
	return sqlSession->executeQuery<UserDO>(sql, UserMapper(), params);
	
}
