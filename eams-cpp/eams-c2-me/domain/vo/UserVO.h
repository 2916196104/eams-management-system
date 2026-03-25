//#pragma once
//// 头文件保护宏：防止多次包含导致类重复定义（C++必写规范）
//#ifndef _USER_VO_H_
//#define _USER_VO_H_
//
//// 引入oatpp核心DTO基类：VO本质是特殊的DTO，用于封装接口响应
//#include "oatpp/core/Types.hpp"
//#include "oatpp/core/data/mapping/type/DTO.hpp"
//// 引入通用JSON响应基类JsonVO：封装了所有接口响应的通用结构（errCode、msg、data）
//#include "domain/vo/BaseJsonVO.h"
//// 引入用户相关DTO：VO需要复用DTO的字段定义（如UserDTO、UserPageDTO）
//#include "UserDTO.h"
//
//// ======================== oatpp代码生成宏：核心开关 ========================
//// OATPP_CODEGEN_BEGIN(DTO)：开启DTO/VO的代码生成，oatpp会自动做3件事：
//// 1. 生成JSON序列化/反序列化逻辑（后端返回给前端的JSON自动转换）
//// 2. 生成Swagger文档的响应结构说明
//// 3. 关联基类的通用字段（如JsonVO的errCode、msg）
//#include OATPP_CODEGEN_BEGIN(DTO)
//
///**
// * 1. 登录响应VO（View Object - 视图对象）
// * 核心作用：封装「登录接口」的核心响应数据（令牌+用户信息）
// * 设计原则：只包含前端展示/使用的核心数据，是接口响应的「数据体」
// * 区别于DTO：DTO是「请求参数载体」，VO是「响应结果载体」
// */
//class LoginVO : public oatpp::DTO {
//    // DTO_INIT(当前类名, 父类名)：oatpp框架要求，初始化VO元数据（必须写）
//    DTO_INIT(LoginVO, DTO);
//
//    // ======================== 字段定义宏：API_DTO_FIELD_DEFAULT ========================
//    // API_DTO_FIELD_DEFAULT(字段类型, 类成员名, "字段说明")
//    // 作用：定义VO字段，标记为「非必填」（响应字段由后端赋值，无需前端传），默认值为空
//
//    // 访问令牌：登录成功后返回给前端的token，前端后续请求需携带此token（身份凭证）
//    API_DTO_FIELD_DEFAULT(String, token, "访问令牌");
//    // 用户信息：登录成功后返回的用户基础信息（复用UserDTO的结构，避免重复定义字段）
//    // Object<UserDTO>：表示这是一个UserDTO类型的对象（而非列表）
//    API_DTO_FIELD_DEFAULT(Object<UserDTO>, user, "用户信息");
//};
//
///**
// * 2. 登录接口最终响应VO（继承通用JsonVO）
// * 核心作用：封装「登录接口」的完整响应结构（通用响应头 + 登录核心数据）
// * 继承关系：JsonVO<LoginVO::Wrapper> → 通用响应基类 + 登录核心数据VO
// * LoginVO::Wrapper：oatpp封装的智能指针（等价于std::shared_ptr<LoginVO>），自动管理内存
// */
//class LoginJsonVO : public JsonVO<LoginVO::Wrapper> {
//    // 初始化VO：父类是JsonVO，泛型参数是「核心数据VO的智能指针」
//    DTO_INIT(LoginJsonVO, JsonVO<LoginVO::Wrapper>);
//    // 无需额外定义字段！通用响应基类JsonVO已包含以下核心字段：
//    // - errCode：响应码（0=成功，非0=失败，如-1=登录失败）
//    // - msg：响应提示语（如"登录成功"、"用户名密码错误"）
//    // - data：核心数据（即LoginVO的内容，包含token和user）
//};
//
///********************主要使用这个vo***********************/
///**
// * 3. 单用户信息响应VO
// * 核心作用：封装「查询单个用户信息接口」的完整响应结构
// * 泛型参数：UserDTO::Wrapper → 核心数据是单条用户信息（复用UserDTO）
// */
//class UserJsonVO : public JsonVO<UserDTO::Wrapper> {
//    DTO_INIT(UserJsonVO, JsonVO<UserDTO::Wrapper>);
//    // 继承后自动拥有：errCode + msg + data（data是UserDTO的内容）
//};
//
///**
// * 4. 用户分页列表响应VO
// * 核心作用：封装「查询用户分页列表接口」的完整响应结构
// * 泛型参数：UserPageDTO::Wrapper → 核心数据是分页用户列表（复用UserPageDTO）
// */
//class UserPageJsonVO : public JsonVO<UserPageDTO::Wrapper> {
//    DTO_INIT(UserPageJsonVO, JsonVO<UserPageDTO::Wrapper>);
//    // 继承后自动拥有：errCode + msg + data（data是UserPageDTO的内容，包含page/size/total/list）
//};
//
//// 关闭DTO/VO代码生成（框架要求，和BEGIN成对出现）
//#include OATPP_CODEGEN_END(DTO)
//
//#endif // _USER_VO_H_