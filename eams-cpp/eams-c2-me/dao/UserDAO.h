//#pragma once
//// 头文件保护宏：防止多次包含导致类重复定义（C++编写头文件的核心规范）
//#ifndef _USER_DAO_H_
//#define _USER_DAO_H_
//
//// 引入基础DAO基类：所有DAO类都继承此类，获得数据库连接、SQL执行等通用能力
//#include "BaseDAO.h"
//// 引入用户查询条件类：用于接收分页+过滤条件（如用户名、年龄范围）
////#include "UserQuery.h"
//// 引入用户数据库实体类：DAO操作的核心数据载体（1:1映射sys_user表）
////#include "UserDO.h"
//// 引入SQL参数绑定类型：用于安全拼接SQL参数，避免SQL注入
////#include "SqlParams.h"
//
///**
// * UserDAO - 用户数据访问对象（Data Access Object）
// * 核心定位：
// * 1. 是Domain层（业务）和数据库之间的「唯一桥梁」，所有对sys_user表的操作都集中在这里
// * 2. 只负责「数据库CRUD操作」，不包含任何业务逻辑（业务逻辑在Service层）
// * 3. 继承BaseDAO：获得通用能力（获取数据库连接、执行SQL、处理结果集等）
// * 设计原则：一个DAO对应一张数据库表（UserDAO对应sys_user表）
// */
//class UserDAO : public BaseDAO {
//private:
//    /**
//     * 私有工具方法：构建查询条件SQL片段 + 绑定参数（核心防SQL注入）
//     * 作用：根据前端传入的UserQuery条件，动态拼接WHERE后的过滤SQL，并绑定参数
//     * @param query 前端传入的查询条件（如username="张"、minAge=18）
//     * @param params 输出参数：存储SQL参数（如"?", "张"），用于后续绑定到SQL语句
//     * @return std::string 拼接好的WHERE条件SQL片段（如"username LIKE ? AND age >= ?"）
//     * 新手理解：
//     *   - 避免直接拼接字符串SQL（如"WHERE username = '" + username + "'"），防止SQL注入攻击
//     *   - 所有参数通过?占位，再通过params绑定，是数据库操作的安全最佳实践
//     */
//    std::string queryConditionBuilder(const UserQuery::Wrapper& query, SqlParams& params);
//
//public:
//    /**
//     * 统计符合条件的用户总数（用于分页计算总页数）
//     * 作用：比如查询“用户名含张、年龄18-30的启用用户”的总数，用于分页控件显示“共XX条”
//     * @param query 查询条件（包含分页参数+业务过滤条件）
//     * @return uint64_t 符合条件的记录总数（无符号长整型，避免总数超出int范围）
//     * 使用场景：分页查询前先调用count，再调用selectWithPage，保证分页准确性
//     */
//    uint64_t count(const UserQuery::Wrapper& query);
//
//    /**
//     * 分页查询用户列表（核心查询方法）
//     * 作用：根据条件查询指定页的用户数据（如第1页、每页10条，筛选用户名含“张”的用户）
//     * @param query 查询条件（包含page=当前页、size=每页条数、username=过滤条件等）
//     * @return std::list<UserDO> 用户DO对象的列表（每个元素对应sys_user表的一行数据）
//     * 新手注意：
//     *   - 返回值是std::list而非数组：链表更适合分页场景，内存占用更优
//     *   - 每个元素是UserDO：直接映射数据库字段，可通过getter/setter获取字段值（如userDO.getId()）
//     */
//    std::list<UserDO> selectWithPage(const UserQuery::Wrapper& query);
//
//    /**
//     * 根据用户ID精确查询单条记录
//     * 作用：比如查询用户详情、修改用户信息前先查询数据，都需要通过ID精准定位
//     * @param id 用户ID（sys_user表的主键，UUID字符串）
//     * @return std::shared_ptr<UserDO> 用户DO对象的智能指针（找不到则返回nullptr）
//     * 新手注意：
//     *   - 使用shared_ptr智能指针：自动管理内存，无需手动delete，避免内存泄漏
//     *   - 返回nullptr表示未找到对应ID的用户，Service层可据此返回“用户不存在”提示
//     */
//    std::shared_ptr<UserDO> selectById(const std::string& id);
//
//    /**
//     * 根据用户名精确查询单条记录
//     * 核心作用：登录验证（根据用户名查密码）、用户名唯一性校验（注册时判断是否重复）
//     * @param username 用户名（sys_user表的唯一索引字段）
//     * @return std::shared_ptr<UserDO> 用户DO对象的智能指针（找不到则返回nullptr）
//     * 新手注意：
//     *   - 用户名是唯一索引，因此最多返回1条记录
//     *   - 登录时：查到用户后，Service层对比密码（加密后）是否一致
//     */
//    std::shared_ptr<UserDO> selectByUsername(const std::string& username);
//};
//
//#endif // _USER_DAO_H_