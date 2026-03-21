//// 项目预编译头文件（通常包含常用头文件，加速编译）
//#include "stdafx.h"
//// 引入当前DAO的头文件
//#include "UserDAO.h"
//// 引入字符串格式化、数值转换等工具（按需）
//#include <sstream>
//#include <memory>
//
///**
// * 私有工具方法：构建动态查询条件（防SQL注入）
// * 作用：根据UserQuery的非空条件，拼接WHERE子句，并绑定参数到SqlParams
// * 新手核心理解：
// *   1. WHERE 1=1：是拼接动态条件的通用技巧，避免第一个条件前多一个AND
// *   2. CONCAT('%', ?, '%')：实现模糊查询（如用户名含"张"），参数通过?绑定，防注入
// *   3. SQLPARAMS_PUSH：项目封装的宏，将参数类型、值存入SqlParams，格式：
// *      SQLPARAMS_PUSH(参数容器, 类型标识, C++类型, 参数值)
// *      类型标识："s"=字符串，"i"=整数，"l"=长整型
// */
//std::string UserDAO::queryConditionBuilder(const UserQuery::Wrapper& query, SqlParams& params) {
//    // stringstream：高效拼接字符串（比直接+号拼接更优）
//    std::stringstream sql;
//    // 基础条件：1=1恒成立，后续条件直接加AND即可，无需判断是否是第一个条件
//    sql << " WHERE 1=1";
//
//    // 1. 用户名模糊查询：如果query的username非空，则添加该条件
//    if (query->username) {
//        // 拼接SQL片段：AND username LIKE 模糊匹配占位符
//        sql << " AND username LIKE CONCAT('%', ?, '%')";
//        // 绑定参数：类型s（字符串），值为query->username的实际值（空则取""）
//        SQLPARAMS_PUSH(params, "s", std::string, query->username.getValue(""));
//    }
//
//    // 2. 昵称模糊查询：逻辑同用户名
//    if (query->nickname) {
//        sql << " AND nickname LIKE CONCAT('%', ?, '%')";
//        SQLPARAMS_PUSH(params, "s", std::string, query->nickname.getValue(""));
//    }
//
//    // 3. 性别精确查询：sex非空则添加
//    if (query->sex) {
//        sql << " AND sex = ?";
//        SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
//    }
//
//    // 4. 最小年龄范围查询：minAge非空则添加（age >= 最小值）
//    if (query->minAge) {
//        sql << " AND age >= ?";
//        SQLPARAMS_PUSH(params, "i", int, query->minAge.getValue(0));
//    }
//
//    // 5. 最大年龄范围查询：maxAge非空则添加（age <= 最大值）
//    if (query->maxAge) {
//        sql << " AND age <= ?";
//        SQLPARAMS_PUSH(params, "i", int, query->maxAge.getValue(0));
//    }
//
//    // 6. 状态精确查询：status非空则添加（默认值1=启用）
//    if (query->status) {
//        sql << " AND status = ?";
//        SQLPARAMS_PUSH(params, "i", int, query->status.getValue(1));
//    }
//
//    // 返回拼接好的WHERE条件片段（如：WHERE 1=1 AND username LIKE CONCAT('%', ?, '%')）
//    return sql.str();
//}
//
///**
// * 统计符合条件的用户总数（用于分页计算总页数）
// * 核心逻辑：
// *   1. 拼接COUNT(*)的SQL + 动态条件
// *   2. 执行SQL，获取单行单列的统计结果
// *   3. 返回总数（无符号长整型，避免总数超出int范围）
// */
//uint64_t UserDAO::count(const UserQuery::Wrapper& query) {
//    // 1. 定义SQL字符串流，初始化COUNT查询的基础SQL
//    std::stringstream sql;
//    sql << "SELECT COUNT(*) FROM sys_user";
//
//    // 2. 声明参数容器，用于存储动态条件的参数（防SQL注入）
//    SqlParams params;
//    // 3. 拼接动态WHERE条件（调用私有工具方法）
//    sql << queryConditionBuilder(query, params);
//
//    // 4. 执行统计查询：BaseDAO封装的executeScalar方法，返回单行单列的结果（总数）
//    //    第一个参数：拼接好的SQL字符串
//    //    第二个参数：参数容器
//    //    第三个参数：默认返回值（查询失败时返回0）
//    uint64_t total = executeScalar(sql.str(), params, 0);
//
//    // 5. 返回统计总数（新手：total=0表示无符合条件的记录）
//    return total;
//}
//
///**
// * 分页查询用户列表
// * 核心逻辑：
// *   1. 拼接SELECT *的SQL + 动态条件 + LIMIT分页子句
// *   2. 计算分页偏移量：offset = (页码-1)*每页条数
// *   3. 执行SQL，将结果集转换为UserDO列表
// */
//std::list<UserDO> UserDAO::selectWithPage(const UserQuery::Wrapper& query) {
//    // 1. 定义存储结果的列表（每个元素是UserDO对象，对应数据库一行数据）
//    std::list<UserDO> userList;
//
//    // 2. 拼接基础查询SQL
//    std::stringstream sql;
//    sql << "SELECT * FROM sys_user";
//
//    // 3. 声明参数容器，绑定动态条件参数
//    SqlParams params;
//    // 4. 拼接动态WHERE条件
//    sql << queryConditionBuilder(query, params);
//
//    // 5. 计算分页偏移量（核心：LIMIT offset, size）
//    //    query->page.getValue(1)：获取页码，默认值1
//    //    query->size.getValue(10)：获取每页条数，默认值10
//    int page = query->page.getValue(1);
//    int size = query->size.getValue(10);
//    int offset = (page - 1) * size; // 偏移量：第1页offset=0，第2页offset=10，以此类推
//
//    // 6. 拼接分页LIMIT子句（MySQL分页语法）
//    sql << " LIMIT ?, ?";
//    // 绑定分页参数：先offset（偏移量），后size（每页条数）
//    SQLPARAMS_PUSH(params, "i", int, offset);
//    SQLPARAMS_PUSH(params, "i", int, size);
//
//    // 7. 执行查询：BaseDAO封装的executeQuery方法，返回结果集（ResultSet）
//    //    智能指针：自动释放结果集，避免内存泄漏
//    std::shared_ptr<ResultSet> resultSet = executeQuery(sql.str(), params);
//
//    // 8. 遍历结果集，转换为UserDO对象
//    if (resultSet) { // 结果集非空时遍历
//        UserDO userDO; // 声明临时UserDO对象，用于存储单行数据
//        while (resultSet->next()) { // 逐行读取结果集（next()返回false表示遍历结束）
//            // 8.1 给UserDO对象赋值：ResultSet的getXXX方法，参数是数据库字段名
//            //     UserDO的setter方法是MYSQL_SYNTHESIZE宏自动生成的
//            userDO.setId(resultSet->getString("id"));
//            userDO.setUsername(resultSet->getString("username"));
//            userDO.setPassword(resultSet->getString("password")); // 注意：实际业务中可隐藏密码
//            userDO.setNickname(resultSet->getString("nickname"));
//            userDO.setAvatar(resultSet->getString("avatar"));
//            userDO.setEmail(resultSet->getString("email"));
//            userDO.setPhone(resultSet->getString("phone"));
//            userDO.setSex(resultSet->getString("sex"));
//            userDO.setAge(resultSet->getInt("age"));
//            userDO.setStatus(resultSet->getInt("status"));
//            userDO.setCreateBy(resultSet->getString("create_by"));
//            userDO.setCreateTime(resultSet->getString("create_time"));
//            userDO.setUpdateBy(resultSet->getString("update_by"));
//            userDO.setUpdateTime(resultSet->getString("update_time"));
//
//            // 8.2 将赋值后的UserDO添加到列表
//            userList.push_back(userDO);
//        }
//    }
//
//    // 9. 返回用户列表（新手：列表为空表示当前页无数据）
//    return userList;
//}
//
///**
// * 根据用户ID精确查询单条记录
// * 核心逻辑：
// *   1. 拼接带ID条件的SQL（主键查询，性能最优）
// *   2. 绑定ID参数，执行查询
// *   3. 结果集转换为UserDO智能指针（无结果则返回nullptr）
// */
//std::shared_ptr<UserDO> UserDAO::selectById(const std::string& id) {
//    // 1. 声明UserDO智能指针（默认nullptr，无结果时直接返回）
//    std::shared_ptr<UserDO> userDO = nullptr;
//
//    // 2. 拼接SQL：主键id精确查询
//    std::string sql = "SELECT * FROM sys_user WHERE id = ?";
//
//    // 3. 声明参数容器，绑定id参数（类型s=字符串）
//    SqlParams params;
//    SQLPARAMS_PUSH(params, "s", std::string, id);
//
//    // 4. 执行查询，获取结果集
//    std::shared_ptr<ResultSet> resultSet = executeQuery(sql, params);
//
//    // 5. 处理结果集（主键查询最多1条结果）
//    if (resultSet && resultSet->next()) {
//        // 5.1 创建UserDO对象（智能指针，自动管理内存）
//        userDO = std::make_shared<UserDO>();
//        // 5.2 给UserDO赋值（同分页查询的字段映射逻辑）
//        userDO->setId(resultSet->getString("id"));
//        userDO->setUsername(resultSet->getString("username"));
//        userDO->setPassword(resultSet->getString("password"));
//        userDO->setNickname(resultSet->getString("nickname"));
//        userDO->setAvatar(resultSet->getString("avatar"));
//        userDO->setEmail(resultSet->getString("email"));
//        userDO->setPhone(resultSet->getString("phone"));
//        userDO->setSex(resultSet->getString("sex"));
//        userDO->setAge(resultSet->getInt("age"));
//        userDO->setStatus(resultSet->getInt("status"));
//        userDO->setCreateBy(resultSet->getString("create_by"));
//        userDO->setCreateTime(resultSet->getString("create_time"));
//        userDO->setUpdateBy(resultSet->getString("update_by"));
//        userDO->setUpdateTime(resultSet->getString("update_time"));
//    }
//
//    // 6. 返回结果：有数据则返回UserDO智能指针，无数据则返回nullptr
//    return userDO;
//}
//
///**
// * 根据用户名精确查询单条记录（唯一索引查询）
// * 核心逻辑：与selectById一致，仅条件改为username
// * 适用场景：登录验证、用户名唯一性校验
// */
//std::shared_ptr<UserDO> UserDAO::selectByUsername(const std::string& username) {
//    // 1. 声明UserDO智能指针（默认nullptr）
//    std::shared_ptr<UserDO> userDO = nullptr;
//
//    // 2. 拼接SQL：username是唯一索引，精确查询
//    std::string sql = "SELECT * FROM sys_user WHERE username = ?";
//
//    // 3. 绑定用户名参数
//    SqlParams params;
//    SQLPARAMS_PUSH(params, "s", std::string, username);
//
//    // 4. 执行查询
//    std::shared_ptr<ResultSet> resultSet = executeQuery(sql, params);
//
//    // 5. 处理结果集（唯一索引最多1条结果）
//    if (resultSet && resultSet->next()) {
//        userDO = std::make_shared<UserDO>();
//        // 字段赋值（同selectById）
//        userDO->setId(resultSet->getString("id"));
//        userDO->setUsername(resultSet->getString("username"));
//        userDO->setPassword(resultSet->getString("password"));
//        userDO->setNickname(resultSet->getString("nickname"));
//        userDO->setAvatar(resultSet->getString("avatar"));
//        userDO->setEmail(resultSet->getString("email"));
//        userDO->setPhone(resultSet->getString("phone"));
//        userDO->setSex(resultSet->getString("sex"));
//        userDO->setAge(resultSet->getInt("age"));
//        userDO->setStatus(resultSet->getInt("status"));
//        userDO->setCreateBy(resultSet->getString("create_by"));
//        userDO->setCreateTime(resultSet->getString("create_time"));
//        userDO->setUpdateBy(resultSet->getString("update_by"));
//        userDO->setUpdateTime(resultSet->getString("update_time"));
//    }
//
//    // 6. 返回结果：找到则返回UserDO，否则返回nullptr
//    return userDO;
//}