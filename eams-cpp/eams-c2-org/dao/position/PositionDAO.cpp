#include "PositionDAO.h"
#include "dao/position/PositionMapper.h"
#include <iostream>   // 用于 std::cerr

// ==================== 原有方法 ====================

std::vector<PositionItemDO> PositionDAO::fetchAll() {
    PositionItemMapper mapper;
    // 表名改为 positions，字段 id, name 保持不变
    auto list = sqlSession->executeQuery<PositionItemDO>(
        "SELECT id, name FROM positions WHERE deleted = 0", mapper);
    std::vector<PositionItemDO> vec;
    vec.reserve(list.size());
    for (auto& item : list) {
        vec.push_back(std::move(item));
    }
    return vec;
}

uint64_t PositionDAO::countByNameLike(const std::string& keyWord) {
    SqlParams params;
    // 表名改为 positions
    std::string sql = "SELECT COUNT(1) FROM positions WHERE deleted = 0";
    if (!keyWord.empty()) {
        sql += " AND name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, ("%" + keyWord + "%"));
    }
    return sqlSession->executeQueryNumerical(sql, params);
}

std::vector<PositionItemDO>
PositionDAO::selectPageByNameLike(int pageNum, int pageSize,
    const std::string& keyWord) {
    SqlParams params;
    // 表名改为 positions
    std::string sql = "SELECT id, name FROM positions WHERE deleted = 0";
    if (!keyWord.empty()) {
        sql += " AND name LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, ("%" + keyWord + "%"));
    }
    sql += " ORDER BY id DESC LIMIT ?, ?";
    const int32_t offset = (pageNum - 1) * pageSize;
    SQLPARAMS_PUSH(params, "i", int32_t, offset);
    SQLPARAMS_PUSH(params, "i", int32_t, pageSize);

    PositionItemMapper mapper;
    auto list = sqlSession->executeQuery<PositionItemDO>(sql, mapper, params);
    std::vector<PositionItemDO> vec;
    vec.reserve(list.size());
    for (auto& item : list) {
        vec.push_back(std::move(item));
    }
    return vec;
}

uint64_t PositionDAO::insertPosition(const std::string& name) {
    PositionItemDO item;
    item.setname(name);
    // 注意：insertAutoPk 内部使用的表名由 PositionItemDO 的注解或映射决定，
    // 如果 PositionItemDO 中映射的表名是 position，需要同步修改为 positions。
    // 此处假设 BaseDAO::insertAutoPk 能正确获取表名，若有问题请检查 PositionItemDO 的映射。
    return insertAutoPk(item);
}

int PositionDAO::updatePositionNameById(int64_t id, const std::string& name) {
    PositionItemDO item;
    item.setId(static_cast<int>(id));
    item.setname(name);
    // 同样，update 方法依赖实体映射的表名，确保 PositionItemDO 中表名为 positions
    return update(item);
}

// ==================== 新增方法：批量删除 ====================
bool PositionDAO::deleteByIds(const std::vector<int64_t>& ids) {
    if (ids.empty()) return true;  // 空列表视为成功

    try {
        // 获取底层数据库连接（用于事务）
        // 注意：如果 sqlSession->getConnection() 不可用，请根据项目实际获取连接的方式调整
        auto conn = sqlSession->getConnection();
        conn->setAutoCommit(false);

        // 1. 删除 data_permission 表中关联的记录（如果该表不存在或不需要，可注释此块）
        //    注意：data_permission 表可能也需要确认表名和字段名是否正确
        std::string sqlPerm = "DELETE FROM data_permission WHERE position_id IN (";
        for (size_t i = 0; i < ids.size(); ++i) {
            if (i > 0) sqlPerm += ",";
            sqlPerm += "?";
        }
        sqlPerm += ")";
        std::unique_ptr<sql::PreparedStatement> pstmtPerm(conn->prepareStatement(sqlPerm));
        for (size_t i = 0; i < ids.size(); ++i) {
            pstmtPerm->setInt64(i + 1, ids[i]);
        }
        pstmtPerm->executeUpdate();

        // 2. 删除职位本身（物理删除）—— 表名改为 positions
        std::string sqlPos = "DELETE FROM positions WHERE id IN (";
        for (size_t i = 0; i < ids.size(); ++i) {
            if (i > 0) sqlPos += ",";
            sqlPos += "?";
        }
        sqlPos += ")";
        std::unique_ptr<sql::PreparedStatement> pstmtPos(conn->prepareStatement(sqlPos));
        for (size_t i = 0; i < ids.size(); ++i) {
            pstmtPos->setInt64(i + 1, ids[i]);
        }
        int affectedRows = pstmtPos->executeUpdate();

        conn->commit();

        // 根据业务需求决定返回 true 的条件：
        // 如果期望删除必须影响至少一行才成功，使用 affectedRows > 0；
        // 如果允许删除不存在的 id 也算成功，可返回 true。
        // 目前保持原逻辑：affectedRows > 0 才成功。
        return affectedRows > 0;
    }
    catch (sql::SQLException& e) {
        // 发生异常时回滚事务
        if (sqlSession->getConnection()) sqlSession->getConnection()->rollback();
        std::cerr << "SQLException in deleteByIds: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        if (sqlSession->getConnection()) sqlSession->getConnection()->rollback();
        std::cerr << "Exception in deleteByIds: " << e.what() << std::endl;
        return false;
    }
    catch (...) {
        if (sqlSession->getConnection()) sqlSession->getConnection()->rollback();
        std::cerr << "Unknown exception in deleteByIds" << std::endl;
        return false;
    }
}