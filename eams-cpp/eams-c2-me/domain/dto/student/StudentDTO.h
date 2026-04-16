#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: ghf
 @Date: 2026/03/20

 学生信息DTO头文件说明：
 1. DTO（数据传输对象）：用于Service层和Controller层之间传输数据，定义API的输入/输出格式
 2. 核心类说明：
    - StudentAddDTO：新增学生（PUSH接口）时的入参DTO
    - StudentDTO：查询学生信息时的出参DTO（包含主键ID）
 3. 字段类型匹配规则：
    - 数据库bigint → oatpp::UInt64
    - 数据库tinyint/int → oatpp::Int32
    - 数据库varchar/date/datetime → oatpp::String（新手优先用String，避免日期类型复杂转换）
    - 数据库布尔型（tinyint(1)）→ oatpp::Int32（0/1表示）
*/
#ifndef _STUDENTDTO_H_  // 头文件保护宏：防止重复包含
#define _STUDENTDTO_H_


// 引入全局通用头文件（包含oatpp基础库、宏定义等，参考UserDTO写法）
#include "../../GlobalInclude.h"

// 开始oatpp的DTO代码生成（必须！框架自动生成序列化/反序列化代码）
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学生数据传输对象
 */
 /**
  * 学生信息DTO（StudentDTO）
  * 核心用途：
  *  1. 新增学生（PUSH /student）：作为入参（主键id可选，由数据库自增）
  *  2. 查询学生（GET /student/{id}）：作为出参（包含主键id，返回完整学生信息）
  * 对应数据库：student表（包含所有字段，与界面/数据库字段一一映射）
  * 界面字段映射：
  * - 姓名 → name
  * - 性别 → gender
  * - 您的身份 → familyRel（家庭关系）
  * - 所在年级 → grade（入学年份）
  * - 身份证号 → idcard
  * - 出生年月 → birthday
  */
class StudentDTO : public oatpp::DTO {
  DTO_INIT(StudentDTO, DTO);

    API_DTO_FIELD(String, id, ZH_WORDS_GETTER("dto.student.id"), true, String(""));
    API_DTO_FIELD(String, name, ZH_WORDS_GETTER("dto.student.name"), true, "");
    API_DTO_FIELD_DEFAULT(String, headImg, ZH_WORDS_GETTER("dto.student.headImg"));
    API_DTO_FIELD(Int32, credit, ZH_WORDS_GETTER("dto.student.credit"), true, 0);
    API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("dto.student.birthday"));
    API_DTO_FIELD(Int32, age, ZH_WORDS_GETTER("dto.student.age"), true, 0);
    API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("dto.student.gender"));
    API_DTO_FIELD_DEFAULT(String, stage, ZH_WORDS_GETTER("dto.student.stage"));
};


// 分页DTO：包含学员列表和分页信息
class StudentPageDTO : public PageDTO<StudentDTO::Wrapper> {
    DTO_INIT(StudentPageDTO, PageDTO<StudentDTO::Wrapper>);
};


/**
 * 学生新增DTO（StudentAddDTO）
 * 核心用途：新增学生接口（PUSH /student）的请求体参数
 * 仅包含前端表单提交的核心字段，无冗余字段，适配新增场景
 * 界面字段与DTO/数据库映射：
 * - 姓名 → name → 数据库name
 * - 性别 → gender → 数据库gender
 * - 您的身份 → familyRel → 数据库family_rel
 * - 所在年级 → grade → 数据库grade
 * - 身份证号 → idcard → 数据库idcard
 * - 出生年月 → birthday → 数据库birthday
 */
class StudentAddDTO : public oatpp::DTO {
    // 初始化DTO（oatpp框架强制要求，固定格式：当前类名, 父类名）
    DTO_INIT(StudentAddDTO, DTO);

    ///**
    // * 学员姓名（必填）
    // * 界面字段：姓名
    // * 数据库字段：name（varchar(20) NOT NULL）
    // */
    //API_DTO_FIELD(String, name, "学员姓名", true, "");

    ///**
    // * 性别（选填，默认0）
    // * 界面字段：性别
    // * 数据库字段：gender（tinyint DEFAULT 0）
    // * 枚举值：0=未知，1=男，2=女
    // */
    //API_DTO_FIELD_DEFAULT(Int32, gender, "性别（0=未知/1=男/2=女）", 0);

    ///**
    // * 您的身份（家庭关系，选填，默认0）
    // * 界面字段：您的身份
    // * 数据库字段：family_rel（tinyint DEFAULT 0）
    // * 枚举值：0=其他，1=爸爸，2=妈妈，3=爷爷，4=奶奶...
    // */
    //API_DTO_FIELD_DEFAULT(Int32, familyRel, "家庭关系（您的身份）", 0);

    ///**
    // * 所在年级（入学年份，选填）
    // * 界面字段：所在年级
    // * 数据库字段：grade（year NULL）
    // * 示例：2027 → 代表2027级
    // */
    //API_DTO_FIELD_DEFAULT(Int32, grade, "所在年级（入学年份，如2027）");

    ///**
    // * 身份证号（选填）
    // * 界面字段：身份证号
    // * 数据库字段：idcard（varchar(30) NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, idcard, "身份证号");

    ///**
    // * 出生年月（选填）
    // * 界面字段：出生年月
    // * 数据库字段：birthday（date NULL）
    // * 格式要求：YYYY-MM-DD（如2026-03-21）
    // */
    //API_DTO_FIELD_DEFAULT(String, birthday, "出生年月（格式：YYYY-MM-DD）");
};


// 结束oatpp的DTO代码生成（必须！与BEGIN成对出现）
#include OATPP_CODEGEN_END(DTO)
#endif // _STUDENTDTO_H_