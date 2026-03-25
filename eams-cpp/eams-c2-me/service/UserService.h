//#pragma once
//// 头文件保护宏：防止多次包含导致类重复定义（C++编写头文件的核心规范）
//#ifndef _USER_SERVICE_H_
//#define _USER_SERVICE_H_
//
//// 引入依赖：Service层需要用到的DTO/VO/Query/DAO
//#include "../domain\dto\student\UserDTO.h"       S   // 用户相关DTO（注册、登录、信息）
//#include "../domain/vo/UserVO.h"           // 用户相关VO（登录响应、分页响应）
//#include "../domain/query/UserQuery.h"        // 用户查询条件封装
//#include "../dao/UserDAO.h"          // 用户数据访问层（Service调用DAO操作数据库）
//#include "oatpp/core/Types.hpp" // oatpp的基础类型（如String、Wrapper智能指针）
//
///**
// * UserService - 用户业务逻辑层（Service层）
// * 核心定位：
// * 1. 承上启下：接收Controller层传递的DTO参数，调用DAO层操作数据库，处理完业务后返回VO/DTO给Controller
// * 2. 业务核心：所有和用户相关的业务规则都集中在这里（如注册时的用户名唯一性校验、登录密码验证、密码加密等）
// * 3. 数据转换：负责DO（数据库实体）和DTO/VO（传输/视图对象）之间的转换（DAO返回DO，Service转成前端需要的DTO/VO）
// * 设计原则：只处理业务逻辑，不直接操作数据库（数据库操作交给DAO）
// */
//class UserService {
//public:
//    /**
//     * 用户注册接口
//     * 核心业务逻辑：
//     *   1. 校验必填参数（用户名、密码、昵称不能为空）
//     *   2. 调用DAO查询用户名是否已存在（防止重复注册）
//     *   3. 对密码进行加密（如MD5/SHA256，绝不能明文存储）
//     *   4. 将DTO转换为DO，调用DAO插入数据库
//     *   5. 返回新增用户的ID（供前端确认注册结果）
//     * @param dto 注册请求DTO（包含用户名、密码、昵称等前端传入的参数）
//     * @return std::string 新增用户的ID（UUID），注册失败返回空字符串
//     * 使用场景：前端调用“用户注册接口”时，Controller调用此方法
//     */
//    std::string registerUser(const UserRegisterDTO::Wrapper& dto);
//
//    /**
//     * 用户登录接口
//     * 核心业务逻辑：
//     *   1. 校验用户名/密码是否为空
//     *   2. 调用DAO根据用户名查询用户DO（不存在则登录失败）
//     *   3. 校验传入的密码（加密后）是否和数据库中存储的密码一致
//     *   4. 生成登录令牌（Token，如JWT）
//     *   5. 将用户DO转换为UserDTO，封装到LoginVO中（包含Token+用户信息）
//     * @param dto 登录请求DTO（包含用户名、密码）
//     * @return LoginVO::Wrapper 登录响应VO（智能指针），包含Token和用户信息；登录失败返回nullptr
//     * 使用场景：前端调用“用户登录接口”时，Controller调用此方法
//     */
//    LoginVO::Wrapper login(const UserLoginDTO::Wrapper& dto);
//
//    /**
//     * 分页查询用户列表
//     * 核心业务逻辑：
//     *   1. 调用DAO统计符合条件的用户总数（用于分页计算总页数）
//     *   2. 调用DAO分页查询用户DO列表
//     *   3. 将DO列表逐个转换为UserDTO，封装到UserPageDTO（包含分页参数+用户列表）
//     * @param query 分页查询条件（包含页码、每页条数、用户名/性别等过滤条件）
//     * @return UserPageDTO::Wrapper 分页响应DTO（智能指针），包含总条数、当前页数据等
//     * 使用场景：前端调用“用户列表分页查询接口”时，Controller调用此方法
//     */
//    UserPageDTO::Wrapper listUsers(const UserQuery::Wrapper& query);
//
//    /**
//     * 根据用户ID查询用户详情
//     * 核心业务逻辑：
//     *   1. 校验用户ID是否为空
//     *   2. 调用DAO根据ID查询用户DO（不存在则返回空）
//     *   3. 将DO转换为UserDTO（隐藏敏感字段，如密码）
//     * @param id 用户ID（UUID字符串）
//     * @return UserDTO::Wrapper 用户详情DTO（智能指针），无数据则返回nullptr
//     * 使用场景：前端调用“用户详情接口”、“修改用户信息前查询原始数据”时调用
//     */
//    UserDTO::Wrapper getUserById(const std::string& id);
//
//    /**
//     * 修改用户信息
//     * 核心业务逻辑：
//     *   1. 校验必填参数（用户ID不能为空、DTO不能为空）
//     *   2. 调用DAO查询用户是否存在（不存在则修改失败）
//     *   3. 将DTO中的可修改字段（昵称、邮箱、手机号等）赋值到DO
//     *   4. 设置更新人、更新时间（操作人ID由前端登录令牌解析）
//     *   5. 调用DAO更新数据库
//     * @param dto 用户修改DTO（包含要修改的字段，如昵称、邮箱）
//     * @param operatorId 操作人ID（当前登录用户的ID，用于记录谁修改了数据）
//     * @return bool 修改结果：true=成功，false=失败
//     * 使用场景：前端调用“修改用户信息接口”时，Controller调用此方法
//     */
//    bool updateUser(const UserDTO::Wrapper& dto, const std::string& operatorId);
//
//    /**
//     * 删除用户（逻辑删除/物理删除，根据业务定）
//     * 核心业务逻辑：
//     *   1. 校验用户ID是否为空
//     *   2. 调用DAO查询用户是否存在（不存在则删除失败）
//     *   3. 物理删除：调用DAO执行DELETE语句；逻辑删除：调用DAO更新status为禁用
//     * @param id 要删除的用户ID
//     * @return bool 删除结果：true=成功，false=失败
//     * 使用场景：管理员调用“删除用户接口”时，Controller调用此方法
//     * 新手注意：生产环境通常用逻辑删除（改状态），而非物理删除（删数据）
//     */
//    bool deleteUser(const std::string& id);
//
//    /**
//     * 修改用户密码
//     * 核心业务逻辑：
//     *   1. 校验旧密码、新密码是否为空，新密码是否符合复杂度要求
//     *   2. 调用DAO根据用户ID查询用户DO（不存在则失败）
//     *   3. 校验旧密码（加密后）是否和数据库中一致
//     *   4. 对新密码加密，调用DAO更新密码字段
//     * @param userId 用户ID
//     * @param oldPassword 旧密码（前端传入的明文，需加密后校验）
//     * @param newPassword 新密码（前端传入的明文，需加密后存储）
//     * @return bool 修改结果：true=成功，false=失败
//     * 使用场景：前端调用“修改密码接口”时，Controller调用此方法
//     */
//    bool changePassword(const std::string& userId,
//        const std::string& oldPassword,
//        const std::string& newPassword);
//};
//
//#endif // _USER_SERVICE_H_