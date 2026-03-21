//#pragma once
//// 头文件保护宏：防止多次包含导致类重复定义（C++必写规范）
//#ifndef _USER_DTO_H_
//#define _USER_DTO_H_
//
//// 引入oatpp核心DTO基类：所有自定义DTO都继承自oatpp::DTO
//#include "oatpp/core/Types.hpp"
////#include "oatpp/core/data/mapping/type/DTO.hpp"
//// 引入分页DTO基类：用于封装分页查询结果（如用户列表分页）
//#include "domain/dto/PageDTO.h"
//
//// ======================== oatpp代码生成宏：核心开关 ========================
//// OATPP_CODEGEN_BEGIN(DTO)：开启DTO代码生成，oatpp会自动做3件事：
//// 1. 生成DTO的JSON序列化/反序列化逻辑（前端<->后端数据传输自动转换）
//// 2. 生成Swagger文档所需的字段描述（接口文档自动显示字段说明）
//// 3. 生成字段的校验逻辑（如必填字段检查）
//#include OATPP_CODEGEN_BEGIN(DTO)
//
///** 
// * 1. 用户注册DTO（Data Transfer Object - 数据传输对象）
// * 核心作用：封装「用户注册接口」的请求参数，是前端传递给后端的参数载体
// * 设计原则：仅包含注册所需的字段，字段名/类型与前端请求JSON严格对应
// * 继承：oatpp::DTO，获得JSON自动转换、参数校验能力
// */
//class UserRegisterDTO : public oatpp::DTO {
//    // DTO_INIT(当前类名, 父类名)：oatpp框架要求，初始化DTO元数据（必须写）
//    DTO_INIT(UserRegisterDTO, DTO);
//
//    // ======================== 字段定义宏：API_DTO_FIELD ========================
//    // API_DTO_FIELD(字段类型, 类成员名, "字段说明", 是否必填, "默认值")
//    // 核心作用：
//    // 1. 定义DTO字段，关联前端JSON字段名（默认和类成员名一致）
//    // 2. 标记字段是否必填（接口调用时自动校验）
//    // 3. 生成Swagger文档的字段说明
//    // 字段类型说明：
//    //   String → 字符串（对应JSON的string）
//    //   Int32 → 32位整数（对应JSON的number）
//    //   Bool → 布尔值（对应JSON的boolean）
//
//    // 用户名：必填，无默认值（前端必须传）
//    API_DTO_FIELD(String, username, "用户名", true, "");
//    // 密码：必填，无默认值（前端必须传，后端需加密存储）
//    API_DTO_FIELD(String, password, "密码", true, "");
//    // 昵称：必填，无默认值（前端必须传）
//    API_DTO_FIELD(String, nickname, "昵称", true, "");
//    // ======================== 字段定义宏：API_DTO_FIELD_DEFAULT ========================
//    // API_DTO_FIELD_DEFAULT(字段类型, 类成员名, "字段说明")
//    // 简化版：等价于「非必填 + 默认值为空」，适用于可选参数
//
//    // 邮箱：可选，默认空（前端不传则用默认值）
//    API_DTO_FIELD_DEFAULT(String, email, "邮箱");
//    // 手机号：可选，默认空（前端不传则用默认值）
//    API_DTO_FIELD_DEFAULT(String, phone, "手机号");
//};
//
///**
// * 2. 用户登录DTO
// * 核心作用：封装「用户登录接口」的请求参数
// * 设计原则：仅保留登录必要字段（用户名+密码），精简参数
// */
//class UserLoginDTO : public oatpp::DTO {
//    DTO_INIT(UserLoginDTO, DTO);
//
//    // 用户名：登录必填
//    API_DTO_FIELD(String, username, "用户名", true, "");
//    // 密码：登录必填
//    API_DTO_FIELD(String, password, "密码", true, "");
//};
//
///**
// * 3. 用户信息DTO
// * 核心作用：封装「用户信息查询接口」的响应参数（后端返回给前端的用户信息）
// * 设计原则：仅返回前端需要展示的字段，隐藏敏感信息（如密码）
// */
//class UserDTO : public oatpp::DTO {
//    DTO_INIT(UserDTO, DTO);
//
//    // 用户ID：可选（后端查询后赋值，前端无需传）
//    API_DTO_FIELD_DEFAULT(String, id, "用户ID");
//    // 用户名：可选（展示用）
//    API_DTO_FIELD_DEFAULT(String, username, "用户名");
//    // 昵称：可选（展示用）
//    API_DTO_FIELD_DEFAULT(String, nickname, "昵称");
//    // 头像URL：可选（展示用）
//    API_DTO_FIELD_DEFAULT(String, avatar, "头像");
//    // 邮箱：可选（展示用）
//    API_DTO_FIELD_DEFAULT(String, email, "邮箱");
//    // 手机号：可选（展示用）
//    API_DTO_FIELD_DEFAULT(String, phone, "手机号");
//    // 性别：可选（展示用，如M=男/F=女/N=未知）
//    API_DTO_FIELD_DEFAULT(String, sex, "性别");
//    // 年龄：可选（32位整数，对应JSON的number）
//    API_DTO_FIELD_DEFAULT(Int32, age, "年龄");
//};
//
///**
// * 4. 用户分页DTO
// * 核心作用：封装「用户列表分页查询」的响应参数（如第1页，每页10条）
// * 继承：PageDTO<UserDTO::Wrapper> → 分页基类 + 用户信息DTO的智能指针
// * 说明：UserDTO::Wrapper 是 oatpp封装的智能指针，等价于 std::shared_ptr<UserDTO>
// */
//class UserPageDTO : public PageDTO<UserDTO::Wrapper> {
//    // 初始化分页DTO：父类是PageDTO，泛型参数是「单条数据的类型」
//    DTO_INIT(UserPageDTO, PageDTO<UserDTO::Wrapper>);
//    // 无需额外定义字段！分页基类PageDTO已包含：
//    // - list：当前页数据列表（UserDTO::Wrapper的集合）
//    // - total：总记录数（用于计算总页数）
//    // - page：当前页码
//    // - size：每页条数
//};
//
//// 关闭DTO代码生成（框架要求，和BEGIN成对出现）
//#include OATPP_CODEGEN_END(DTO)
//
//#endif // _USER_DTO_H_
