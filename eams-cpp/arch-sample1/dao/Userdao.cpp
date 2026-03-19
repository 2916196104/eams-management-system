// UserDAO.cpp
#include "stdafx.h"
#include "AddressDAO.h"
#include "UserMapper.h"
// 私有方法：构建查询条件（你已提供）
std::string UserDAO::queryConditionBuilder(const UserQuery::Wrapper& query, SqlParams& params) {
    std::stringstream sql;
    sql << " WHERE 1=1";

    if (query->username) {
        sql << " AND username LIKE CONCAT('%', ?, '%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->username.getValue(""));
    }
    if (query->nickname) {
        sql << " AND nickname LIKE CONCAT('%', ?, '%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->nickname.getValue(""));
    }
    if (query->sex) {
        sql << " AND sex = ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
    }
    if (query->minAge) {
        sql << " AND age >= ?";
        SQLPARAMS_PUSH(params, "i", int, query->minAge.getValue(0));
    }
    if (query->maxAge) {
        sql << " AND age <= ?";
        SQLPARAMS_PUSH(params, "i", int, query->maxAge.getValue(0));
    }
    if (query->status) {
        sql << " AND status = ?";
        SQLPARAMS_PUSH(params, "i", int, query->status.getValue(1));
    }

    return sql.str();
}

// 1. 统计符合条件的用户数量
uint64_t UserDAO::count(const UserQuery::Wrapper& query) {
    // 初始化SQL参数容器
    SqlParams params;
    // 构建基础SQL和动态条件
    std::stringstream sql;
    sql << "SELECT COUNT(*) FROM sys_user ";
    sql << queryConditionBuilder(query, params);

    // 执行查询并获取结果（BaseDAO提供的通用查询方法）
    auto result = this->queryForSingle(sql.str(), params);
    if (result && !result->empty()) {
        // 转换为无符号64位整数
        return std::stoull((*result)[0]);
    }
    // 无数据时返回0
    return 0;
}

// 2. 分页查询用户列表
std::list<UserDO> UserDAO::selectWithPage(const UserQuery::Wrapper& query) {
    // 初始化返回列表和SQL参数
    std::list<UserDO> userList;
    SqlParams params;

    // 构建基础查询SQL
    std::stringstream sql;
    sql << "SELECT id, username, password, nickname, avatar, email, phone, "
        "sex, age, status, create_by, create_time, update_by, update_time "
        << "FROM sys_user ";

    // 拼接动态查询条件
    sql << queryConditionBuilder(query, params);

    // 拼接分页条件（PageQuery提供pageNum/pageSize）
    int offset = (query->pageNum.getValue(1) - 1) * query->pageSize.getValue(10);
    sql << " LIMIT ? OFFSET ?";
    SQLPARAMS_PUSH(params, "i", int, query->pageSize.getValue(10));
    SQLPARAMS_PUSH(params, "i", int, offset);

    // 执行查询并映射为UserDO列表（BaseDAO通用查询方法）
    auto resultSet = this->query(sql.str(), params);
    for (auto& row : resultSet) {
        UserDO userDO;
        // 按字段顺序映射结果到UserDO对象
        userDO.setId(row[0]);
        userDO.setUsername(row[1]);
        userDO.setPassword(row[2]);
        userDO.setNickname(row[3]);
        userDO.setAvatar(row[4]);
        userDO.setEmail(row[5]);
        userDO.setPhone(row[6]);
        userDO.setSex(row[7]);
        userDO.setAge(std::stoi(row[8]));
        userDO.setStatus(std::stoi(row[9]));
        userDO.setCreateBy(row[10]);
        userDO.setCreateTime(row[11]);
        userDO.setUpdateBy(row[12]);
        userDO.setUpdateTime(row[13]);

        userList.push_back(userDO);
    }

    return userList;
}

// 3. 根据ID查询单个用户
std::shared_ptr<UserDO> UserDAO::selectById(const std::string& id) {
    // 空ID直接返回空
    if (id.empty()) {
        return nullptr;
    }

    SqlParams params;
    std::string sql = "SELECT id, username, password, nickname, avatar, email, phone, "
        "sex, age, status, create_by, create_time, update_by, update_time "
        "FROM sys_user WHERE id = ?";
    SQLPARAMS_PUSH(params, "s", std::string, id);

    // 执行查询
    auto resultSet = this->query(sql, params);
    if (resultSet.empty()) {
        return nullptr;
    }

    // 映射结果到UserDO并返回智能指针
    auto row = resultSet[0];
    std::shared_ptr<UserDO> userDO = std::make_shared<UserDO>();
    userDO->setId(row[0]);
    userDO->setUsername(row[1]);
    userDO->setPassword(row[2]);
    userDO->setNickname(row[3]);
    userDO->setAvatar(row[4]);
    userDO->setEmail(row[5]);
    userDO->setPhone(row[6]);
    userDO->setSex(row[7]);
    userDO->setAge(std::stoi(row[8]));
    userDO->setStatus(std::stoi(row[9]));
    userDO->setCreateBy(row[10]);
    userDO->setCreateTime(row[11]);
    userDO->setUpdateBy(row[12]);
    userDO->setUpdateTime(row[13]);

    return userDO;
}

// 4. 根据用户名查询单个用户
std::shared_ptr<UserDO> UserDAO::selectByUsername(const std::string& username) {
    // 空用户名直接返回空
    if (username.empty()) {
        return nullptr;
    }

    SqlParams params;
    std::string sql = "SELECT id, username, password, nickname, avatar, email, phone, "
        "sex, age, status, create_by, create_time, update_by, update_time "
        "FROM sys_user WHERE username = ?";
    SQLPARAMS_PUSH(params, "s", std::string, username);

    // 执行查询
    auto resultSet = this->query(sql, params);
    if (resultSet.empty()) {
        return nullptr;
    }

    // 映射结果到UserDO并返回智能指针
    auto row = resultSet[0];
    std::shared_ptr<UserDO> userDO = std::make_shared<UserDO>();
    userDO->setId(row[0]);
    userDO->setUsername(row[1]);
    userDO->setPassword(row[2]);
    userDO->setNickname(row[3]);
    userDO->setAvatar(row[4]);
    userDO->setEmail(row[5]);
    userDO->setPhone(row[6]);
    userDO->setSex(row[7]);
    userDO->setAge(std::stoi(row[8]));
    userDO->setStatus(std::stoi(row[9]));
    userDO->setCreateBy(row[10]);
    userDO->setCreateTime(row[11]);
    userDO->setUpdateBy(row[12]);
    userDO->setUpdateTime(row[13]);

    return userDO;
}