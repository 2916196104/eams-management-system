#include "stdafx.h"
#include "HomeworkDAO.h"
#include "HomeworkMapper.h"

bool HomeworkDAO::insert(HomeworkDO& homework) {
    if (!sqlSession) {
        OATPP_LOGD("HomeworkDAO", "sqlSession is NULL!");
        return false;
    }

    // 简单转义字符串中的单引号
    auto escape = [](const std::string& s) {
        std::string result;
        for (char c : s) {
            if (c == '\'') result += "''";
            else result += c;
        }
        return result;
        };

    std::string sql = "INSERT INTO homework (id, class_id, title, content, creator, editor, add_time, edit_time, deleted, org_id) VALUES (" +
        std::to_string(homework.getId()) + ", " +
        std::to_string(homework.getClassId()) + ", '" +
        escape(homework.getTitle()) + "', '" +
        escape(homework.getContent()) + "', " +
        std::to_string(homework.getCreator()) + ", " +
        std::to_string(homework.getEditor()) + ", '" +
        homework.getAddTime() + "', '" +
        homework.getEditTime() + "', " +
        (homework.getDeleted() ? "1" : "0") + ", " +
        std::to_string(homework.getOrgId()) + ")";

    OATPP_LOGD("HomeworkDAO", "Executing SQL: %s", sql.c_str());

    try {
        int affected = sqlSession->executeUpdate(sql);
        return affected == 1;
    }
    catch (const std::exception& e) {
        OATPP_LOGD("HomeworkDAO", "exception: %s", e.what());
        return false;
    }
}

PtrHomeworkDO HomeworkDAO::selectById(uint64_t id) {
    string sql = "SELECT id, class_id, title, content, creator, editor, add_time, edit_time, deleted, org_id FROM homework WHERE id = " + std::to_string(id);
    return sqlSession->executeQueryOne<PtrHomeworkDO>(sql, PtrHomeworkMapper());
}

bool HomeworkDAO::update(const HomeworkDO& homework) {
    string sql = "UPDATE homework SET class_id=?, title=?, content=?, editor=?, edit_time=?, deleted=?, org_id=? "
        "WHERE id=?";
    return sqlSession->executeUpdate(sql, "%i,%s,%s,%i,%s,%b,%i,%i",
        homework.getClassId(),
        homework.getTitle().c_str(),
        homework.getContent().c_str(),
        homework.getEditor(),
        homework.getEditTime().c_str(),
        homework.getDeleted(),
        homework.getOrgId(),
        homework.getId()
    );
}

bool HomeworkDAO::deleteById(uint64_t id) {
    string sql = "UPDATE homework SET deleted=1 WHERE id=" + std::to_string(id);
    return sqlSession->executeUpdate(sql) == 1;
}