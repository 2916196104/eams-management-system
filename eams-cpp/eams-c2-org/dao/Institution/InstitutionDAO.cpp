#include "stdafx.h"
#include "InstitutionDAO.h"
#include "SqlSession.h"
#include "../../domain/do/Institution/InstitutionDO.h"
#include "InstitutionMapper.h"


std::list<PtrInstitutionDO> InstitutionDAO::selectAllInstitutions() {
    std::string sql = "SELECT id, name, pid FROM org WHERE deleted = 0";
    SqlParams params; // 虽然没有条件，但也传一个空的 params 进去
    // 使用 sqlSession 执行查询
    return sqlSession->executeQuery<PtrInstitutionDO>(sql, PtrInstitutionMapper(), params);
}