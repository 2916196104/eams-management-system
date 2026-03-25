#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: ghf
 @Date: 2026/03/20

 学生信息VO头文件说明：
 1. VO（视图对象）：封装接口最终返回给前端的响应数据，基于项目通用的JsonVO基类
 2. 核心能力：自动包含「通用响应字段」（errCode/msg/data），无需重复定义
 3. 适配接口：
    - StudentInfoJsonVO：GET /student/{id}（获取学生信息）接口响应VO
    - StudentAddJsonVO：PUSH /student（新增学生信息）接口响应VO
 4. 与DTO的区别：
    - DTO：前端→后端的「入参载体」（如StudentAddDTO接收新增参数）
    - VO：后端→前端的「出参载体」（封装响应状态+业务数据）
*/
#ifndef _STUDENTVO_H_  // 头文件保护宏：防止重复包含导致类重复定义
#define _STUDENTVO_H_

// 1. 引入项目通用头文件（包含oatpp核心库、宏定义）
#include "../../GlobalInclude.h"
// 2. 引入通用JSON响应基类（核心！提供errCode/msg/data通用字段）
#include "../BaseJsonVO.h"
// 3. 引入学生DTO（VO的data字段复用StudentDTO的结构）
#include "StudentDTO.h"

// ======================== oatpp代码生成宏（必须！）========================
// 作用：自动生成VO的JSON序列化/反序列化代码、Swagger文档注释
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学生信息查询响应VO（StudentInfoJsonVO）
 * 用途：适配「获取当前学生信息」接口（GET /student/{id}）的最终响应
 * 继承关系：JsonVO<StudentDTO::Wrapper> → 通用响应基类 + 学生信息DTO
 * 核心结构：{errCode: 0, msg: "操作成功", data: {学生完整信息（含ID）}}
 */
class StudentInfoJsonVO : public JsonVO<StudentDTO::Wrapper> {
    // DTO_INIT(当前类名, 父类名)：oatpp框架强制要求，初始化VO元数据
    // 父类是JsonVO，泛型参数是「学生DTO的智能指针」（自动管理内存）
    DTO_INIT(StudentInfoJsonVO, JsonVO<StudentDTO::Wrapper>);
    // 无需额外定义字段！通用基类JsonVO已包含以下核心字段：
    // - errCode：响应码（0=成功，非0=失败，如-1=学生不存在）
    // - msg：响应提示语（如"查询成功"、"学生ID不存在"）
    // - data：核心业务数据（此处是StudentDTO对象，包含学生完整信息）
};

/**
 * 学生信息新增响应VO（StudentAddJsonVO）
 * 用途：适配「新增学生信息」接口（PUSH /student）的最终响应
 * 继承关系：JsonVO<StudentDTO::Wrapper> → 通用响应基类 + 学生信息DTO
 * 核心结构：{errCode: 0, msg: "新增成功", data: {新增的学生完整信息（含自动生成的ID）}}
 */
class StudentAddJsonVO : public JsonVO<StudentDTO::Wrapper> {
    // 初始化VO：父类是JsonVO，泛型参数为StudentDTO的智能指针
    DTO_INIT(StudentAddJsonVO, JsonVO<StudentDTO::Wrapper>);
    // 同样继承通用字段：errCode + msg + data
    // data字段存储「新增成功后的学生完整信息」（含数据库生成的ID），供前端确认
};

// ======================== 结束oatpp代码生成 ========================
#include OATPP_CODEGEN_END(DTO)

#endif // _STUDENTVO_H_