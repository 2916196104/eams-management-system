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
 * 学生完整信息DTO（StudentDTO）
 * 用途：GET /student/{id} 接口的出参，返回单个学生的完整信息
 * 继承自StudentAddDTO，自动复用所有新增字段，仅新增主键ID字段
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
    //// 初始化DTO（框架强制要求，固定格式：当前类名, 父类名）
    DTO_INIT(StudentDTO, DTO);

    //// ===================== 核心字段（含主键，查询/新增通用） =====================
    ///**
    // * 学生主键ID
    // * 数据库字段：id（bigint UNSIGNED NOT NULL，主键）
    // * 用途：
    // *  - 新增：可选（数据库自增，前端无需传）
    // *  - 查询：必填（作为返回结果的唯一标识）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, id, "学生主键ID（新增无需传，查询返回）");

    ///**
    // * 家长ID（必填）
    // * 数据库字段：user_id（bigint NOT NULL）
    // * 说明：绑定当前登录家长的用户ID，后端可从Token中自动获取
    // */
    //API_DTO_FIELD(UInt64, userId, "家长ID", true, "");

    ///**
    // * 学员姓名（必填）
    // * 数据库字段：name（varchar(20) NOT NULL）
    // * 界面字段：姓名
    // */
    //API_DTO_FIELD(String, name, "学员姓名", true, "");

    ///**
    // * 性别（选填，默认0）
    // * 数据库字段：gender（tinyint DEFAULT 0）
    // * 界面字段：性别
    // * 枚举值：0=未知，1=男，2=女
    // */
    //API_DTO_FIELD_DEFAULT(Int32, gender, "性别（0=未知/1=男/2=女）", 0);

    ///**
    // * 您的身份（家庭关系，选填，默认0）
    // * 数据库字段：family_rel（tinyint DEFAULT 0）
    // * 界面字段：您的身份
    // * 枚举值：0=其他，1=爸爸，2=妈妈，3=爷爷，4=奶奶...
    // */
    //API_DTO_FIELD_DEFAULT(Int32, familyRel, "家庭关系（您的身份）", 0);

    ///**
    // * 入学年份（所在年级，选填）
    // * 数据库字段：grade（year NULL）
    // * 界面字段：所在年级
    // * 示例：2027 → 代表2027级
    // */
    //API_DTO_FIELD_DEFAULT(Int32, grade, "入学年份（所在年级，如2027）");

    ///**
    // * 身份证号（选填）
    // * 数据库字段：idcard（varchar(30) NULL）
    // * 界面字段：身份证号
    // */
    //API_DTO_FIELD_DEFAULT(String, idcard, "身份证号");

    ///**
    // * 出生年月（选填）
    // * 数据库字段：birthday（date NULL）
    // * 界面字段：出生年月
    // * 格式要求：YYYY-MM-DD（如2026-03-21）
    // */
    //API_DTO_FIELD_DEFAULT(String, birthday, "出生年月（格式：YYYY-MM-DD）");

    //// ===================== 数据库其他字段（界面未展示，可选传） =====================
    ///**
    // * 是否默认查看的学员（选填，默认1）
    // * 数据库字段：as_default（tinyint(1) DEFAULT 1）
    // * 说明：1=是，0=否；家长可设置默认查看的学员
    // */
    //API_DTO_FIELD_DEFAULT(Int32, asDefault, "是否默认查看的学员", 1);

    ///**
    // * 所属分校ID（选填）
    // * 数据库字段：school_id（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, schoolId, "所属分校ID");

    ///**
    // * 逻辑删除标识（选填，默认0）
    // * 数据库字段：deleted（int DEFAULT 0）
    // * 说明：0=未删除，1=已删除（逻辑删除）
    // */
    //API_DTO_FIELD_DEFAULT(Int32, deleted, "逻辑删除标识（0=未删除/1=已删除）", 0);

    ///**
    // * 阶段状态（选填）
    // * 数据库字段：stage（tinyint NULL）
    // * 说明：0=意向学员，1=在读学员，2=结业学员
    // */
    //API_DTO_FIELD_DEFAULT(Int32, stage, "阶段状态（0=意向学员/1=在读/2=结业）");

    ///**
    // * 头像URL（选填）
    // * 数据库字段：head_img（varchar(255) NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, headImg, "头像URL");

    ///**
    // * 加入方式ID（选填）
    // * 数据库字段：join_way（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, joinWay, "加入方式ID");

    ///**
    // * 备注信息（选填）
    // * 数据库字段：remark（varchar(255) NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, remark, "备注信息");

    ///**
    // * 结业日期（选填）
    // * 数据库字段：graduation_date（date NULL）
    // * 格式：YYYY-MM-DD
    // */
    //API_DTO_FIELD_DEFAULT(String, graduationDate, "结业日期（格式：YYYY-MM-DD）");

    ///**
    // * 结业原因（选填）
    // * 数据库字段：graduation_reason（varchar(255) NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, graduationReason, "结业原因");

    ///**
    // * 加入时间（选填）
    // * 数据库字段：add_time（datetime NULL）
    // * 格式：YYYY-MM-DD HH:MM:SS
    // * 说明：新增时后端可自动填充为当前时间
    // */
    //API_DTO_FIELD_DEFAULT(String, addTime, "加入时间（格式：YYYY-MM-DD HH:MM:SS）");

    ///**
    // * 顾问ID（选填）
    // * 数据库字段：counselor（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, counselor, "顾问ID");

    ///**
    // * 创建者ID（选填）
    // * 数据库字段：creator（bigint NULL）
    // * 说明：新增时后端自动填充为当前登录用户ID
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, creator, "创建者ID");

    ///**
    // * 编辑人ID（选填）
    // * 数据库字段：editor（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, editor, "编辑人ID");

    ///**
    // * 编辑时间（选填）
    // * 数据库字段：edit_time（datetime NULL）
    // * 格式：YYYY-MM-DD HH:MM:SS
    // */
    //API_DTO_FIELD_DEFAULT(String, editTime, "编辑时间（格式：YYYY-MM-DD HH:MM:SS）");

    ///**
    // * 红点标记成绩最后查看时间（选填）
    // * 数据库字段：redpoint_grade（datetime NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, redpointGrade, "红点标记成绩最后查看时间");

    ///**
    // * 红点标记点评最后查看时间（选填）
    // * 数据库字段：redpoint_evaluate（datetime NULL）
    // */
    //API_DTO_FIELD_DEFAULT(String, redpointEvaluate, "红点标记点评最后查看时间");

    ///**
    // * 入学日期（选填）
    // * 数据库字段：join_date（date NULL）
    // * 格式：YYYY-MM-DD
    // */
    //API_DTO_FIELD_DEFAULT(String, joinDate, "入学日期（格式：YYYY-MM-DD）");

    ///**
    // * 微信登录记录ID（选填）
    // * 数据库字段：wx_access_id（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, wxAccessId, "微信登录记录ID");

    ///**
    // * 学生积分（选填，默认0）
    // * 数据库字段：credit（int DEFAULT 0）
    // */
    //API_DTO_FIELD_DEFAULT(Int32, credit, "学生积分", 0);

    ///**
    // * 创建者所属组织ID（选填）
    // * 数据库字段：org_id（bigint NULL）
    // */
    //API_DTO_FIELD_DEFAULT(UInt64, orgId, "创建者所属组织ID");

    ///**
    // * 年级ID（选填）
    // * 数据库字段：grade_id（int NULL）
    // */
    //API_DTO_FIELD_DEFAULT(Int32, gradeId, "年级ID");
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