//#pragma once
//// 防止头文件重复包含（C++核心语法，避免多次引入导致编译错误）
//#ifndef _USER_DO_H_
//#define _USER_DO_H_
//
//// 引入BaseDO基类头文件（BaseDO封装了数据库实体的通用逻辑，如字段映射、表名定义）
//#include "BaseDO.h"
//
///**
// * UserDO 数据对象（Data Object）
// * 核心作用：严格映射数据库中的 `sys_user` 表结构，是内存中存储数据库表一行数据的载体
// * 设计原则：1:1对应数据库字段，仅包含字段的getter/setter，无业务逻辑
// * 继承关系：继承BaseDO，获得表名定义、字段映射等通用能力
// */
//class UserDO : public BaseDO {
//    // ======================== 核心宏：自动生成字段的getter/setter方法 ========================
//    // MYSQL_SYNTHESIZE(字段类型, 成员变量名, 方法名前缀)
//    // 作用：自动生成 成员变量的 getXXX() 和 setXXX() 方法，避免手写重复代码
//    // 示例：MYSQL_SYNTHESIZE(string, id, Id) → 生成 string getId() 和 void setId(string) 方法
//
//    // 用户ID（对应数据库sys_user.id字段，主键，UUID类型）
//    MYSQL_SYNTHESIZE(string, id, Id);
//    // 用户名（对应sys_user.username，唯一索引，非空）
//    MYSQL_SYNTHESIZE(string, username, Username);
//    // 密码（对应sys_user.password，加密存储，非空）
//    MYSQL_SYNTHESIZE(string, password, Password);
//    // 昵称（对应sys_user.nickname，可选）
//    MYSQL_SYNTHESIZE(string, nickname, Nickname);
//    // 头像URL（对应sys_user.avatar，可选）
//    MYSQL_SYNTHESIZE(string, avatar, Avatar);
//    // 邮箱（对应sys_user.email，可选）
//    MYSQL_SYNTHESIZE(string, email, Email);
//    // 手机号（对应sys_user.phone，可选）
//    MYSQL_SYNTHESIZE(string, phone, Phone);
//    // 性别（对应sys_user.sex，M=男/F=女/N=未知）
//    MYSQL_SYNTHESIZE(string, sex, Sex);
//    // 年龄（对应sys_user.age，整数类型）
//    MYSQL_SYNTHESIZE(int, age, Age);
//    // 状态（对应sys_user.status，0=禁用/1=启用，默认1）
//    MYSQL_SYNTHESIZE(int, status, Status);
//    // 创建者（对应sys_user.create_by，系统字段）
//    MYSQL_SYNTHESIZE(string, createBy, CreateBy);
//    // 创建时间（对应sys_user.create_time，系统字段，格式：yyyy-MM-dd HH:mm:ss）
//    MYSQL_SYNTHESIZE(string, createTime, CreateTime);
//    // 更新者（对应sys_user.update_by，系统字段）
//    MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
//    // 更新时间（对应sys_user.update_time，系统字段）
//    MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);
//
//public:
//    /**
//     * 构造函数：初始化DO对象，核心作用是绑定「数据库字段名」和「类成员变量」的映射关系
//     * BaseDO("sys_user")：调用父类构造函数，指定当前DO对应的数据表名是 `sys_user`
//     */
//    UserDO() : BaseDO("sys_user") {
//        // ======================== 字段映射宏：绑定数据库字段和类成员 ========================
//        // MYSQL_ADD_FIELD_PK(数据库字段名, 字段类型标识, 类成员变量名)：绑定主键字段
//        // MYSQL_ADD_FIELD(数据库字段名, 字段类型标识, 类成员变量名)：绑定普通字段
//        // 字段类型标识说明：
//        //   "s" → string（字符串类型，对应数据库VARCHAR/CHAR等）
//        //   "i" → int（整数类型，对应数据库INT/TINYINT等）
//        //   "l" → long（长整型，对应数据库BIGINT）
//        //   "d" → double（浮点型，对应数据库DOUBLE/FLOAT）
//
//        // 绑定主键字段：数据库字段id → 类成员id（字符串类型）
//        MYSQL_ADD_FIELD_PK("id", "s", id);
//        // 绑定普通字段：数据库username → 类成员username（字符串）
//        MYSQL_ADD_FIELD("username", "s", username);
//        // 绑定密码字段：数据库password → 类成员password（字符串）
//        MYSQL_ADD_FIELD("password", "s", password);
//        // 绑定昵称字段：数据库nickname → 类成员nickname（字符串）
//        MYSQL_ADD_FIELD("nickname", "s", nickname);
//        // 绑定头像字段：数据库avatar → 类成员avatar（字符串）
//        MYSQL_ADD_FIELD("avatar", "s", avatar);
//        // 绑定邮箱字段：数据库email → 类成员email（字符串）
//        MYSQL_ADD_FIELD("email", "s", email);
//        // 绑定手机号字段：数据库phone → 类成员phone（字符串）
//        MYSQL_ADD_FIELD("phone", "s", phone);
//        // 绑定性别字段：数据库sex → 类成员sex（字符串）
//        MYSQL_ADD_FIELD("sex", "s", sex);
//        // 绑定年龄字段：数据库age → 类成员age（整数）
//        MYSQL_ADD_FIELD("age", "i", age);
//        // 绑定状态字段：数据库status → 类成员status（整数）
//        MYSQL_ADD_FIELD("status", "i", status);
//        // 绑定创建者字段：数据库create_by → 类成员createBy（字符串，注意数据库字段是下划线，类是驼峰）
//        MYSQL_ADD_FIELD("create_by", "s", createBy);
//        // 绑定创建时间字段：数据库create_time → 类成员createTime（字符串）
//        MYSQL_ADD_FIELD("create_time", "s", createTime);
//        // 绑定更新者字段：数据库update_by → 类成员updateBy（字符串）
//        MYSQL_ADD_FIELD("update_by", "s", updateBy);
//        // 绑定更新时间字段：数据库update_time → 类成员updateTime（字符串）
//        MYSQL_ADD_FIELD("update_time", "s", updateTime);
//    }
//};
//
//// 结束头文件保护宏
//#endif // _USER_DO_H_