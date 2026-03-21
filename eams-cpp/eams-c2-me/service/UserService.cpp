//// 项目预编译头文件（包含常用头文件，加速编译）
//#include "stdafx.h"
//// 引入当前Service头文件
//#include "UserService.h"
////// 引入加密工具（密码加密/验证）
////#include "util/BcryptHelper.h"
////// 引入UUID生成工具（生成用户唯一ID）
////#include "util/UuidFacade.h"
////// 引入时间格式化工具（生成创建/更新时间）
////#include "util/SimpleDateTimeFormat.h"
////// 引入JWT令牌生成工具（登录token）
////#include "util/JwtHelper.h"
////// 引入Redis客户端（缓存登录信息）
////#include "util/RedisClient.h"
////// 引入邮件发送工具（注册欢迎邮件）
////#include "util/EmailSender.h"
////// 引入DO<->DTO转换宏（简化数据转换）
////#include "util/DtoDoConvert.h"
////// 引入JWT相关头文件（token生成）
////#include <jwt-cpp/jwt.h>
//// 引入异常处理、时间相关头文件
//#include <stdexcept>
//#include <chrono>
//#include <domain/do/UserDO.h>
//#include "../../arch-skeleton/Macros.h"
//#include <D:\01StarProject\WorkSpaseTeamCopy\zero-one-eams2603\eams-cpp\eams-c2-me\Macros.h>
//
/////**
//// * 用户注册方法
//// * 核心流程：参数校验 → 用户名唯一性校验 → 密码加密 → DTO转DO → 入库 → 异步发邮件 → 返回用户ID
//// */
////std::string UserService::registerUser(const UserRegisterDTO::Wrapper& dto) {
////    // ===================== 步骤1：参数非空校验（前置防御） =====================
////    std::string username = dto->username.getValue("");
////    std::string password = dto->password.getValue("");
////    std::string nickname = dto->nickname.getValue("");
////    if (username.empty() || password.empty() || nickname.empty()) {
////        throw std::runtime_error("用户名、密码、昵称不能为空");
////    }
////
////    // ===================== 步骤2：校验用户名是否已存在（避免重复注册） =====================
////    UserDAO dao; // 创建DAO对象（Service通过DAO操作数据库）
////    auto existUser = dao.selectByUsername(username); // 调用DAO根据用户名查询
////    if (existUser) { // 查到用户表示已存在
////        throw std::runtime_error("用户名已存在");
////    }
////
////    // ===================== 步骤3：密码加密（核心安全措施，绝不明文存储） =====================
////    BcryptHelper bcrypt; // 加密工具对象（基于Bcrypt算法，不可逆加密）
////    std::string hashedPassword = bcrypt.hash(password); // 加密明文密码
////
////    // ===================== 步骤4：DTO转换为DO（数据传输对象→数据库实体） =====================
////    UserDO userDO; // 声明数据库实体对象
////    // ZO_STAR_DOMAIN_DTO_TO_DO：项目封装的转换宏，格式：(DO对象, DTO对象, DO字段名, DTO字段名)
////    ZO_STAR_DOMAIN_DTO_TO_DO(userDO, dto,
////        Username, username,  // userDO.setUsername(dto->username)
////        Nickname, nickname,  // userDO.setNickname(dto->nickname)
////        Email, email,        // userDO.setEmail(dto->email)
////        Phone, phone         // userDO.setPhone(dto->phone)
////    );
////    // 手动设置DTO中没有的字段（数据库必填但前端不传的字段）
////    userDO.setPassword(hashedPassword); // 设置加密后的密码
////    userDO.setId(UuidFacade().genUuid()); // 生成UUID作为用户主键ID
////    userDO.setStatus(1); // 默认启用（1=启用，0=禁用）
////    userDO.setCreateTime(SimpleDateTimeFormat::format()); // 生成当前时间（格式：yyyy-MM-dd HH:mm:ss）
////    userDO.setCreateBy("system"); // 创建人：系统（也可传注册用户的IP/默认值）
////    userDO.setUpdateTime(userDO.getCreateTime()); // 更新时间默认等于创建时间
////    userDO.setUpdateBy(userDO.getCreateBy()); // 更新人默认等于创建人
////
////    // ===================== 步骤5：调用DAO插入数据库 =====================
////    // insert返回值：影响的行数（1=成功，0=失败）
////    if (dao.insert(userDO) != 1) {
////        throw std::runtime_error("用户注册失败，数据库插入异常");
////    }
////
////    // ===================== 步骤6：异步发送欢迎邮件（非核心逻辑，不影响注册结果） =====================
////    std::string email = userDO.getEmail();
////    if (!email.empty()) { // 有邮箱才发送
////        ZO_CREATE_MAIL_SENDER(emailSender); // 创建邮件发送器（项目封装的宏）
////        // 异步发送文本邮件（避免阻塞注册流程）
////        emailSender.sendTextMail(
////            email,                  // 收件人邮箱
////            "欢迎注册我们的服务",    // 邮件标题
////            "尊敬的 " + userDO.getNickname() + "，恭喜您注册成功！" // 邮件内容
////        );
////    }
////
////    // ===================== 步骤7：返回新增用户的ID（供前端确认） =====================
////    return userDO.getId();
////}
//
/////**
//// * 用户登录方法
//// * 核心流程：查询用户 → 验证密码 → 检查状态 → 生成Token → 缓存登录信息 → 构造返回VO
//// */
////LoginVO::Wrapper UserService::login(const UserLoginDTO::Wrapper& dto) {
////    // ===================== 步骤1：参数非空校验 =====================
////    std::string username = dto->username.getValue("");
////    std::string password = dto->password.getValue("");
////    if (username.empty() || password.empty()) {
////        throw std::runtime_error("用户名或密码不能为空");
////    }
////
////    // ===================== 步骤2：调用DAO查询用户（根据用户名） =====================
////    UserDAO dao;
////    auto userDO = dao.selectByUsername(username); // 返回智能指针，nullptr表示用户不存在
////    if (!userDO) { // 用户名不存在，统一提示“用户名或密码错误”（避免信息泄露）
////        throw std::runtime_error("用户名或密码错误");
////    }
////
////    // ===================== 步骤3：验证密码（明文密码 vs 加密密码） =====================
////    BcryptHelper bcrypt;
////    // verify方法：对比明文密码加密后是否和数据库中的加密密码一致
////    if (!bcrypt.verify(password, userDO->getPassword())) {
////        throw std::runtime_error("用户名或密码错误");
////    }
////
////    // ===================== 步骤4：检查用户状态（禁用用户无法登录） =====================
////    if (userDO->getStatus() != 1) { // 1=启用，0=禁用
////        throw std::runtime_error("用户已被禁用，请联系管理员");
////    }
////
////    // ===================== 步骤5：生成JWT Token（登录令牌，供前端后续请求携带） =====================
////    // JWT参数：算法HS256 + 秘钥 + 载荷（用户信息+过期时间）
////    jwt::jwt_object jwtObj{
////        jwt::params::algorithm("HS256"),          // 加密算法
////        jwt::params::secret("your-secret-key"),   // 秘钥（生产环境需配置在配置文件，不要硬编码）
////        jwt::params::payload({                    // 载荷（存储非敏感用户信息）
////            {"userId", userDO->getId()},          // 用户ID
////            {"username", userDO->getUsername()},  // 用户名
////            {"exp", std::chrono::system_clock::now() + std::chrono::hours(24)} // 过期时间：24小时
////        })
////    };
////    std::string token = jwtObj.signature(); // 生成签名后的token
////
////    // ===================== 步骤6：缓存登录信息到Redis（用于后续验证/登出） =====================
////    ZO_CREATE_REDIS_CLIENT(redisClient); // 创建Redis客户端（项目封装的宏）
////    std::string redisKey = "user:login:" + userDO->getId(); // Redis键：user:login:用户ID
////    // 存储token和登录时间
////    redisClient.hset(redisKey, "token", token);
////    redisClient.hset(redisKey, "loginTime", SimpleDateTimeFormat::format());
////    redisClient.expire(redisKey, std::chrono::hours(24)); // 设置缓存过期时间（和token一致）
////
////    // ===================== 步骤7：DO转换为DTO（隐藏敏感字段，如密码） =====================
////    auto userDTO = UserDTO::createShared(); // 创建用户DTO智能指针
////    // ZO_STAR_DOMAIN_DO_TO_DTO_1：项目封装的转换宏，格式：(DTO对象, DO对象, DTO字段名, DO字段名)
////    ZO_STAR_DOMAIN_DO_TO_DTO_1(userDTO, userDO,
////        id, Id,            // userDTO->id = userDO->getId()
////        username, Username,// userDTO->username = userDO->getUsername()
////        nickname, Nickname,// userDTO->nickname = userDO->getNickname()
////        avatar, Avatar,    // userDTO->avatar = userDO->getAvatar()
////        email, Email,      // userDTO->email = userDO->getEmail()
////        phone, Phone,      // userDTO->phone = userDO->getPhone()
////        sex, Sex,          // userDTO->sex = userDO->getSex()
////        age, Age           // userDTO->age = userDO->getAge()
////    );
////
////    // ===================== 步骤8：构造登录响应VO（返回给前端） =====================
////    auto loginVO = LoginVO::createShared(); // 创建登录VO智能指针
////    loginVO->token = token; // 设置登录令牌
////    loginVO->user = userDTO; // 设置用户信息DTO
////
////    // ===================== 步骤9：返回VO =====================
////    return loginVO;
////}
//
///**
// * 分页查询用户列表方法
// * 核心流程：统计总数 → 分页查询DO列表 → DO转DTO列表 → 封装分页DTO
// */
//UserPageDTO::Wrapper UserService::listUsers(const UserQuery::Wrapper& query) {
//    // ===================== 步骤1：创建DAO对象 =====================
//    UserDAO dao;
//
//    // ===================== 步骤2：调用DAO统计符合条件的总数（用于分页） =====================
//    uint64_t total = dao.count(query); // 总记录数
//
//    // ===================== 步骤3：调用DAO分页查询用户DO列表 =====================
//    std::list<UserDO> userDOList = dao.selectWithPage(query);
//
//    // ===================== 步骤4：创建分页DTO对象（封装返回结果） =====================
//    auto userPageDTO = UserPageDTO::createShared();
//    // 设置分页通用参数
//    userPageDTO->page = query->page.getValue(1);    // 当前页码
//    userPageDTO->size = query->size.getValue(10);   // 每页条数
//    userPageDTO->total = total;                     // 总记录数
//
//    // ===================== 步骤5：DO列表转换为DTO列表（逐个转换） =====================
//    auto userDTOList = oatpp::List<UserDTO::Wrapper>::createShared(); // 创建DTO列表智能指针
//    for (const auto& userDO : userDOList) { // 遍历DO列表
//        auto userDTO = UserDTO::createShared(); // 创建单个DTO
//        // DO转DTO（隐藏密码等敏感字段）
//        ZO_STAR_DOMAIN_DO_TO_DTO_1(userDTO, &userDO, // 注意：这里userDO是值，传地址
//            id, Id,
//            username, Username,
//            nickname, Nickname,
//            avatar, Avatar,
//            email, Email,
//            phone, Phone,
//            sex, Sex,
//            age, Age
//        );
//        userDTOList->push_back(userDTO); // 添加到DTO列表
//    }
//
//    // ===================== 步骤6：设置分页DTO的列表数据 =====================
//    userPageDTO->list = userDTOList;
//
//    // ===================== 步骤7：返回分页DTO =====================
//    return userPageDTO;
//}
//
///**
// * 根据ID查询用户详情方法
// * 核心流程：校验ID → 查询DO → DO转DTO → 返回DTO（隐藏敏感字段）
// */
//UserDTO::Wrapper UserService::getUserById(const std::string& id) {
//    // ===================== 步骤1：校验ID非空 =====================
//    if (id.empty()) {
//        throw std::runtime_error("用户ID不能为空");
//    }
//
//    // ===================== 步骤2：调用DAO查询用户DO =====================
//    UserDAO dao;
//    auto userDO = dao.selectById(id);
//    if (!userDO) { // 未找到用户
//        throw std::runtime_error("用户不存在");
//    }
//
//    // ===================== 步骤3：DO转换为DTO（隐藏密码） =====================
//    auto userDTO = UserDTO::createShared();
//    ZO_STAR_DOMAIN_DO_TO_DTO_1(userDTO, userDO,
//        id, Id,
//        username, Username,
//        nickname, Nickname,
//        avatar, Avatar,
//        email, Email,
//        phone, Phone,
//        sex, Sex,
//        age, Age
//    );
//
//    // ===================== 步骤4：返回DTO =====================
//    return userDTO;
//}
//
///**
// * 修改用户信息方法
// * 核心流程：校验参数 → 查询DO → DTO转DO（仅更新可修改字段） → 调用DAO更新 → 返回结果
// */
//bool UserService::updateUser(const UserDTO::Wrapper& dto, const std::string& operatorId) {
//    // ===================== 步骤1：参数非空校验 =====================
//    if (!dto || dto->id.getValue("").empty() || operatorId.empty()) {
//        throw std::runtime_error("用户ID、操作人ID不能为空");
//    }
//    std::string userId = dto->id.getValue("");
//
//    // ===================== 步骤2：调用DAO查询用户是否存在 =====================
//    UserDAO dao;
//    auto userDO = dao.selectById(userId);
//    if (!userDO) {
//        throw std::runtime_error("用户不存在，无法修改");
//    }
//
//    // ===================== 步骤3：DTO转换为DO（仅更新可修改字段） =====================
//    // 只更新昵称、邮箱、手机号、头像、性别、年龄（不更新密码、状态等敏感字段）
//    if (dto->nickname) { // 昵称非空才更新
//        userDO->setNickname(dto->nickname.getValue(""));
//    }
//    if (dto->email) { // 邮箱非空才更新
//        userDO->setEmail(dto->email.getValue(""));
//    }
//    if (dto->phone) { // 手机号非空才更新
//        userDO->setPhone(dto->phone.getValue(""));
//    }
//    if (dto->avatar) { // 头像非空才更新
//        userDO->setAvatar(dto->avatar.getValue(""));
//    }
//    if (dto->sex) { // 性别非空才更新
//        userDO->setSex(dto->sex.getValue(""));
//    }
//    if (dto->age) { // 年龄非空才更新
//        userDO->setAge(dto->age.getValue(0));
//    }
//
//    // ===================== 步骤4：设置更新信息（审计字段） =====================
//    userDO->setUpdateBy(operatorId); // 更新人：当前操作人ID
//    userDO->setUpdateTime(SimpleDateTimeFormat::format()); // 更新时间：当前时间
//
//    // ===================== 步骤5：调用DAO更新数据库 =====================
//    // update返回值：影响的行数（1=成功，0=失败）
//    int affectRows = dao.update(*userDO); // 注意：userDO是智能指针，解引用传值
//
//    // ===================== 步骤6：返回更新结果 =====================
//    return affectRows == 1;
//}
//
/////**
//// * 删除用户方法（逻辑删除：修改状态为禁用）
//// * 核心流程：校验ID → 查询DO → 修改状态 → 调用DAO更新 → 返回结果
//// */
////bool UserService::deleteUser(const std::string& id) {
////    // ===================== 步骤1：校验ID非空 =====================
////    if (id.empty()) {
////        throw std::runtime_error("用户ID不能为空");
////    }
////
////    // ===================== 步骤2：调用DAO查询用户是否存在 =====================
////    UserDAO dao;
////    auto userDO = dao.selectById(id);
////    if (!userDO) {
////        throw std::runtime_error("用户不存在，无法删除");
////    }
////
////    // ===================== 步骤3：设置逻辑删除状态（0=禁用） =====================
////    userDO->setStatus(0); // 逻辑删除：修改状态为禁用（而非物理删除数据）
////    userDO->setUpdateTime(SimpleDateTimeFormat::format()); // 更新时间
////    userDO->setUpdateBy("admin"); // 更新人：管理员（也可传当前登录用户ID）
////
////    // ===================== 步骤4：调用DAO更新数据库 =====================
////    int affectRows = dao.update(*userDO);
////
////    // ===================== 步骤5：返回删除结果 =====================
////    return affectRows == 1;
////}
//
/////**
//// * 修改密码方法
//// * 核心流程：校验参数 → 查询DO → 验证旧密码 → 加密新密码 → 更新DO → 调用DAO更新 → 返回结果
//// */
////bool UserService::changePassword(const std::string& userId,
////    const std::string& oldPassword,
////    const std::string& newPassword) {
////    // ===================== 步骤1：参数非空校验 =====================
////    if (userId.empty() || oldPassword.empty() || newPassword.empty()) {
////        throw std::runtime_error("用户ID、旧密码、新密码不能为空");
////    }
////    // 校验新密码复杂度（示例：长度≥6）
////    if (newPassword.length() < 6) {
////        throw std::runtime_error("新密码长度不能少于6位");
////    }
////
////    // ===================== 步骤2：调用DAO查询用户DO =====================
////    UserDAO dao;
////    auto userDO = dao.selectById(userId);
////    if (!userDO) {
////        throw std::runtime_error("用户不存在");
////    }
////
////    // ===================== 步骤3：验证旧密码 =====================
////    BcryptHelper bcrypt;
////    if (!bcrypt.verify(oldPassword, userDO->getPassword())) {
////        throw std::runtime_error("旧密码错误");
////    }
////
////    // ===================== 步骤4：加密新密码 =====================
////    std::string hashedNewPassword = bcrypt.hash(newPassword);
////
////    // ===================== 步骤5：更新DO的密码和审计字段 =====================
////    userDO->setPassword(hashedNewPassword);
////    userDO->setUpdateTime(SimpleDateTimeFormat::format());
////    userDO->setUpdateBy(userId); // 更新人：用户自己
////
////    // ===================== 步骤6：调用DAO更新数据库 =====================
////    int affectRows = dao.update(*userDO);
////
////    // ===================== 步骤7：返回修改结果 =====================
////    return affectRows == 1;
////}