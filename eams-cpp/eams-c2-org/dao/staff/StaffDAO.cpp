#include "stdafx.h"
#include "StaffDAO.h"
#include "StaffMapper.h"

PtrStaffDO StaffDAO::selectById(const string& id)
{
    string sql = "SELECT "
        "su.id, su.name, su.id_card, su.head_img, su.deleted, "
        "su.mobile, su.wx_access_id, su.email, su.birthday, su.gender, "
        "su.school, su.degree, su.remark, su.state, su.is_manager, "
        "su.hire_date, su.fire_date, su.intro, su.add_time, su.edit_time, "
        "su.creator, su.editor, su.password, su.class_fee, su.assistant_fee, "
        "su.org_id, su.is_inner "
        "FROM staff su WHERE su.id = ? AND su.deleted = 0";
    return sqlSession->executeQueryOne<PtrStaffDO>(sql, StaffMapper(), "%s", id);
}

int StaffDAO::batchDeleteByIds(const std::list<std::string>& ids)
{
    if (ids.empty()) return 0;

    // 1. 拼接 IN 子句占位符 (?, ?, ?)
    string inClause;
    for (auto it = ids.begin(); it != ids.end(); ++it) {
        if (it != ids.begin()) inClause += ",";
        inClause += "?";
    }
    string sql = "UPDATE staff SET deleted=1 WHERE id IN (" + inClause + ") AND deleted=0";

    // 2. 用 SqlParams 绑定所有ID（符合工程规范，避免va_list错误）
    SqlParams params;
    for (const auto& id : ids) {
        SQLPARAMS_PUSH(params, "s", std::string, id);
    }

    // 3. 调用正确的 executeUpdate 重载（接收 SqlParams）
    return sqlSession->executeUpdate(sql, params);
}