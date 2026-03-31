#pragma once
// domain/dto/staff/StaffDTO.h
#ifndef STAFF_DTO_H
#define STAFF_DTO_H

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 员工核心DTO（基类，包含所有基础通用字段）
 * 对齐数据库staff表核心字段，无无效字段
 */
class StaffDTO : public oatpp::DTO {
    DTO_INIT(StaffDTO, DTO);

    // 1. 主键&基础标识字段
    API_DTO_FIELD_DEFAULT(UInt64, id, "field.id");                // bigint → 不动
    API_DTO_FIELD_DEFAULT(UInt64, orgId, "field.orgId");         // bigint → 不动
    API_DTO_FIELD_DEFAULT(Int32, deleted, "field.deleted");       // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(Int32, isInner, "field.isInner");       // tinyint Int32 → Int8

    // 2. 核心业务字段（必展示）
    API_DTO_FIELD_DEFAULT(String, name, "field.name");
    API_DTO_FIELD_DEFAULT(String, mobile, "field.mobile");
    API_DTO_FIELD_DEFAULT(String, idCard, "field.idCard");
    API_DTO_FIELD_DEFAULT(String, headImg, "field.headImg");
    API_DTO_FIELD_DEFAULT(Int32, state, "field.state");           // tinyint Int32 → Int8

    // 3. 基础信息字段（可选展示）
    API_DTO_FIELD_DEFAULT(UInt64, wxAccessId, "field.wxAccessId");// bigint → 不动
    API_DTO_FIELD_DEFAULT(String, email, "field.email");
    API_DTO_FIELD_DEFAULT(String, birthday, "field.birthday");
    API_DTO_FIELD_DEFAULT(Int32, gender, "field.gender");         // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, school, "field.school");
    API_DTO_FIELD_DEFAULT(Int32, degree, "field.degree");         // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, remark, "field.remark");
    API_DTO_FIELD_DEFAULT(Int32, isManager, "field.isManager");   // tinyint Int32 → Int8
    API_DTO_FIELD_DEFAULT(String, hireDate, "field.hireDate");
    API_DTO_FIELD_DEFAULT(String, fireDate, "field.fireDate");
    API_DTO_FIELD_DEFAULT(String, intro, "field.intro");

    // 4. 薪资相关字段
    API_DTO_FIELD_DEFAULT(Float64, classFee, "field.classFee");
    API_DTO_FIELD_DEFAULT(Float64, assistantFee, "field.assistantFee");

    // 5. 系统审计字段（后台用，前端可选展示）
    API_DTO_FIELD_DEFAULT(String, addTime, "field.addTime");
    API_DTO_FIELD_DEFAULT(String, editTime, "field.editTime");
    API_DTO_FIELD_DEFAULT(UInt64, creator, "field.creator");     // bigint → 不动
    API_DTO_FIELD_DEFAULT(UInt64, editor, "field.editor");       // bigint → 不动
};

/**
 * 员工基础DTO（列表展示用）
 */
class StaffBaseDTO : public StaffDTO
{
    DTO_INIT(StaffBaseDTO, StaffDTO);
};

/**
 * 员工详情DTO（详情页/编辑页用）
 */
class StaffDetailDTO : public StaffBaseDTO
{
    DTO_INIT(StaffDetailDTO, StaffBaseDTO);
    API_DTO_FIELD_DEFAULT(String, password, "field.password");
};

#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_DTO_H