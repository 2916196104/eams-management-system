#include "stdafx.h"
#include "InstitutionDAO.h"
#include "SqlSession.h"
#include "../../domain/do/Institution/InstitutionDO.h"
#include "InstitutionMapper.h"
#include "oatpp/core/Types.hpp"
using namespace oatpp;

int InstitutionDAO::insert(const InstitutionDO& data) {
    std::string sql = "INSERT INTO org (id, name, pid, level, shortname, contact_name, phone, fax, email, sort_num, state, info) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    SqlParams params;
    SQLPARAMS_PUSH(params, "i", uint64_t, data.getId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getName());
    SQLPARAMS_PUSH(params, "i", uint64_t, data.getPid());
    SQLPARAMS_PUSH(params, "i", int, data.getLevel());
    SQLPARAMS_PUSH(params, "s", std::string, data.getShortname());
    SQLPARAMS_PUSH(params, "s", std::string, data.getContactName());
    SQLPARAMS_PUSH(params, "s", std::string, data.getPhone());
    SQLPARAMS_PUSH(params, "s", std::string, data.getFax());
    SQLPARAMS_PUSH(params, "s", std::string, data.getEmail());
    SQLPARAMS_PUSH(params, "i", int, data.getSortNum());
    SQLPARAMS_PUSH(params, "i", int, data.getState());
    SQLPARAMS_PUSH(params, "s", std::string, data.getInfo());

    return sqlSession->executeUpdate(sql, params);
}

int InstitutionDAO::update(const InstitutionDO& data) {
    std::string sql = "UPDATE org SET name = ?, pid = ?, level = ?, shortname = ?, contact_name = ?, phone = ?, fax = ?, email = ?, sort_num = ?, state = ?, info = ? WHERE id = ?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, data.getName());
    SQLPARAMS_PUSH(params, "i", uint64_t, data.getPid());
    SQLPARAMS_PUSH(params, "i", int, data.getLevel());
    SQLPARAMS_PUSH(params, "s", std::string, data.getShortname());
    SQLPARAMS_PUSH(params, "s", std::string, data.getContactName());
    SQLPARAMS_PUSH(params, "s", std::string, data.getPhone());
    SQLPARAMS_PUSH(params, "s", std::string, data.getFax());
    SQLPARAMS_PUSH(params, "s", std::string, data.getEmail());
    SQLPARAMS_PUSH(params, "i", int, data.getSortNum());
    SQLPARAMS_PUSH(params, "i", int, data.getState());
    SQLPARAMS_PUSH(params, "s", std::string, data.getInfo());
    SQLPARAMS_PUSH(params, "i", uint64_t, data.getId()); // WHERE 条件的 id

    return sqlSession->executeUpdate(sql, params);
}

std::list<PtrInstitutionDO> InstitutionDAO::selectAllInstitutions() {
    std::string sql = "SELECT id, name, pid, level, shortname, contact_name, phone, fax, email, sort_num, state, info FROM org WHERE deleted = 0";
    SqlParams params; // 虽然没有条件，但也传一个空的 params 进去
    // 使用 sqlSession 执行查询
    return sqlSession->executeQuery<PtrInstitutionDO>(sql, PtrInstitutionMapper(), params);
}