//#pragma once
//// 头文件保护宏：防止多次包含导致类重复定义（C++编写头文件的标配）
//#ifndef _USER_QUERY_H_
//#define _USER_QUERY_H_
//
//// 引入分页查询基类PageQuery：所有查询条件类都继承此类，获得通用分页参数（页码、每页条数）
//#include "domain/query/PageQuery.h"
//// 引入oatpp的DTO核心头文件：Query本质是特殊的DTO，用于封装「查询条件参数」
//#include "oatpp/core/data/mapping/type/DTO.hpp"
//
//// 开启oatpp代码生成：自动生成查询条件的JSON序列化/反序列化、Swagger文档注释
//#include OATPP_CODEGEN_BEGIN(DTO)
//
///**
// * UserQuery - 用户查询条件封装类
// * 核心作用：封装「用户列表分页查询接口」的所有过滤条件 + 分页参数
// * 设计定位：
// *   1. 继承PageQuery：自动获得分页通用参数（page=当前页码，size=每页条数）
// *   2. 扩展业务过滤字段：用户名、昵称、性别等，用于精准筛选用户
// *   3. 区别于普通DTO：Query专门用于「查询接口的入参」，聚焦“过滤条件+分页”
// */
//class UserQuery : public PageQuery {
//    // DTO_INIT(当前类名, 父类名)：oatpp框架强制要求，初始化Query的元数据
//    // 作用：告诉框架这个类继承自PageQuery，需要合并父类的分页字段
//    DTO_INIT(UserQuery, PageQuery);
//
//    // ======================== 核心宏：API_DTO_FIELD_DEFAULT ========================
//    // 格式：API_DTO_FIELD_DEFAULT(字段类型, 类成员名, "字段说明")
//    // 核心能力：
//    // 1. 定义查询过滤字段，前端通过URL参数/JSON传参，框架自动映射到该成员
//    // 2. 标记为「非必填字段」（查询时可传可不传，不传则不参与过滤）
//    // 3. 自动生成Swagger文档的字段说明，前端能清晰看到每个查询条件的含义
//    // 字段类型说明：
//    //   String → 字符串类型（匹配数据库VARCHAR/CHAR字段）
//    //   Int32 → 32位整数（匹配数据库INT/TINYINT字段）
//
//    // 用户名过滤条件：模糊查询（如传"张"，则筛选出所有用户名含"张"的用户）
//    API_DTO_FIELD_DEFAULT(String, username, "用户名");
//    // 昵称过滤条件：模糊查询（如传"小"，则筛选出所有昵称含"小"的用户）
//    API_DTO_FIELD_DEFAULT(String, nickname, "昵称");
//    // 性别过滤条件：精确匹配（如传"M"筛选男性，传"F"筛选女性）
//    API_DTO_FIELD_DEFAULT(String, sex, "性别");
//    // 最小年龄过滤条件：范围查询（如传18，筛选出年龄≥18的用户）
//    API_DTO_FIELD_DEFAULT(Int32, minAge, "最小年龄");
//    // 最大年龄过滤条件：范围查询（如传30，筛选出年龄≤30的用户）
//    API_DTO_FIELD_DEFAULT(Int32, maxAge, "最大年龄");
//    // 状态过滤条件：精确匹配（如传1筛选启用的用户，传0筛选禁用的用户）
//    API_DTO_FIELD_DEFAULT(Int32, status, "状态");
//};
//
//// 关闭oatpp代码生成（与BEGIN成对出现，框架要求）
//#include OATPP_CODEGEN_END(DTO)
//
//#endif // _USER_QUERY_H_