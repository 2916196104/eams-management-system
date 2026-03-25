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
    API_DTO_FIELD_DEFAULT(String, id, "field.id");                // 对应数据库：id (bigint)
    API_DTO_FIELD_DEFAULT(String, orgId, "field.orgId");         // 对应数据库：org_id (bigint)
    API_DTO_FIELD_DEFAULT(Int32, deleted, "field.deleted"); // 对应数据库：deleted (tinyint)
    API_DTO_FIELD_DEFAULT(Int32, isInner, "field.isInner"); // 对应数据库：is_inner (tinyint)

    // 2. 核心业务字段（必展示）
    API_DTO_FIELD_DEFAULT(String, name, "field.name");                // 对应数据库：name (varchar)
    API_DTO_FIELD_DEFAULT(String, mobile, "field.mobile");            // 对应数据库：mobile (varchar)
    API_DTO_FIELD_DEFAULT(String, idCard, "field.idCard");          // 对应数据库：id_card (varchar)
    API_DTO_FIELD_DEFAULT(String, headImg, "field.headImg");          // 对应数据库：head_img (varchar)
    API_DTO_FIELD_DEFAULT(Int32, state, "field.state"); // 对应数据库：state (tinyint)

    // 3. 基础信息字段（可选展示）
    API_DTO_FIELD_DEFAULT(String, wxAccessId, "field.wxAccessId");    // 对应数据库：wx_access_id (bigint)
    API_DTO_FIELD_DEFAULT(String, email, "field.email");              // 对应数据库：email (varchar)
    API_DTO_FIELD_DEFAULT(String, birthday, "field.birthday");            // 对应数据库：birthday (date)
    API_DTO_FIELD_DEFAULT(Int32, gender, "field.gender"); // 对应数据库：gender (tinyint)
    API_DTO_FIELD_DEFAULT(String, school, "field.school");          // 对应数据库：school (varchar)
    API_DTO_FIELD_DEFAULT(Int32, degree, "field.degree"); // 对应数据库：degree (tinyint)
    API_DTO_FIELD_DEFAULT(String, remark, "field.remark");              // 对应数据库：remark (varchar)
    API_DTO_FIELD_DEFAULT(Int32, isManager, "field.isManager"); // 对应数据库：is_manager (tinyint)
    API_DTO_FIELD_DEFAULT(String, hireDate, "field.hireDate");        // 对应数据库：hire_date (date)
    API_DTO_FIELD_DEFAULT(String, fireDate, "field.fireDate");        // 对应数据库：fire_date (date)
    API_DTO_FIELD_DEFAULT(String, intro, "field.intro");           // 对应数据库：intro (varchar)

    // 4. 薪资相关字段
    API_DTO_FIELD_DEFAULT(Float64, classFee, "field.classFee");         // 对应数据库：class_fee (decimal)
    API_DTO_FIELD_DEFAULT(Float64, assistantFee, "field.assistantFee");     // 对应数据库：assistant_fee (decimal)

    // 5. 系统审计字段（后台用，前端可选展示）
    API_DTO_FIELD_DEFAULT(String, addTime, "field.addTime");         // 对应数据库：add_time (datetime)
    API_DTO_FIELD_DEFAULT(String, editTime, "field.editTime");        // 对应数据库：edit_time (datetime)
    API_DTO_FIELD_DEFAULT(String, creator, "field.creator");         // 对应数据库：creator (bigint)
    API_DTO_FIELD_DEFAULT(String, editor, "field.editor");          // 对应数据库：editor (bigint)
};

/**
 * 员工基础DTO（列表展示用）
 * 仅保留列表页需要的核心字段，减少数据传输
 */
class StaffBaseDTO : public StaffDTO
{
    DTO_INIT(StaffBaseDTO, StaffDTO);

    // 继承StaffDTO，但前端展示时仅返回以下核心字段（通过接口控制，代码无需修改）
    // id / name / mobile / headImg / state / isInner / orgId
};

/**
 * 员工详情DTO（详情页/编辑页用）
 * 包含所有字段，满足详情展示和编辑需求
 */
class StaffDetailDTO : public StaffBaseDTO
{
    DTO_INIT(StaffDetailDTO, StaffBaseDTO);

    // 继承所有字段，额外补充敏感字段（按需开放）
    API_DTO_FIELD_DEFAULT(String, password, "field.password"); // 对应数据库：password (varchar)
};

#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_DTO_H