#include "stdafx.h"
#include "RegisterDAO.h"
#include "RegisterMapper.h"
#include "SqlSession.h"

//RegisterDAO::insertAutoPk(const RegisterDO& bd)

PtrRegisterDO RegisterDAO::selectById(const std::string& id)
{
	std::string sql = "SELECT * FROM user WHERE id = ?";
	return sqlSession->executeQueryOne<PtrRegisterDO>(sql, PtrRegisterMapper(), "%s", id);
}