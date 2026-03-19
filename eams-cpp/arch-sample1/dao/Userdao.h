#pragma once
// UserDAO.h
#include "BaseDAO.h"
#include "domain/do/UserDo.h"
class UserDAO : public BaseDAO {
private:
    std::string queryConditionBuilder(const UserQuery::Wrapper& query, SqlParams& params);
public:
    // 统计
    uint64_t count(const UserQuery::Wrapper& query);
    // 分页查询
    std::list<UserDO> selectWithPage(const UserQuery::Wrapper& query);
    // 根据ID查询
    std::shared_ptr<UserDO> selectByid(const std::string& id);
    // 根据用户名查询
    std::shared_ptr<UserDO> selectByUsername(const std::string& username);
};