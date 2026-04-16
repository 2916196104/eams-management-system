#include "stdafx.h"
#include "domain/do/parent/ParentInfoDO.h"
#include "ParentInfoDAO.h"
#include "ParentInfoMapper.h"

PtrParentInfoDO ParentInfoDAO::selectParentInfoById(const uint64_t& id)
{
	string sql = "SELECT name, mobile, datetime FROM user WHERE `id` = ?";
	return sqlSession->executeQueryOne<PtrParentInfoDO>(sql, PtrParentInfoMapper(), "%ull", id);
}
