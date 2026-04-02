#pragma once
#ifndef _INTENDEDSTUDENT_DTO_
#define _INTENDEDSTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据新增对象
 */
class IntendedAddDTO : public oatpp::DTO
{
    DTO_INIT(IntendedAddDTO, DTO);
    // Excel 列对应字段（按顺序）
    // 第1列：*姓名（必填）
    DTO_FIELD(String, name);

    // 第2列：*手机号（必填）
    DTO_FIELD(String, mobile);

    // 第3列：*登录密码（必填）
    DTO_FIELD(String, password);

    // 第4列：家长姓名（可选）
    DTO_FIELD(String, parent);

    // 第5列：性别(有效值:男|女|未知)
    DTO_FIELD(Int32, sex);

    // 第6列：生日(格式:2000-01-01)
    DTO_FIELD(String, birthday);

    // 第7列：身份证（可选）
    DTO_FIELD(String, idCard);

    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
    // 数据校验
    std::string validate()
    {
        // 必填校验
        if (!name || name->empty())
            return "name invalidate.";
        if (!mobile || mobile->empty())
            return "mobile invalidate.";
        if (!password || password->empty())
            return "password invalidate.";
        // 手机号格式
        if (mobile && mobile->length() != 11)
            return "mobile invalidate.";
        // 性别有效值校验
        if (*sex != 0 && *sex != 1 && *sex != 2)
            return "sex invalidate.";
        // 生日格式校验
        if (birthday && !birthday->empty()) {
            if (birthday->length() != 10 || (*birthday)[4] != '-' || (*birthday)[7] != '-')
                return "birthday invalidate.";
        }

        return "";
    }
};

/**
 * excel导入对象
 */
class IntendedImportDTO : public oatpp::DTO
{
    DTO_INIT(IntendedImportDTO, DTO);
    // 导入报表文件
    API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("intendedstudent.field.excel"), true);
};

/**
 * excel导出对象
 */
class IntendedExportDTO : public oatpp::DTO
{
    DTO_INIT(IntendedExportDTO, DTO);

    DTO_FIELD(UInt64, id);              // 学员ID（数据库主键）
    DTO_FIELD(String, name);            // 学员姓名
    DTO_FIELD(String, mobile);          // 手机号码（user.mobile）
    DTO_FIELD(Int32, gender);           // 性别（student.gender：0女 1男）
    DTO_FIELD(String, parentName);      // 家长姓名（user.name）
    DTO_FIELD(Int32, familyRel);        // 家长关系（student.family_rel：0本人 1父亲 2母亲 3其他）
    DTO_FIELD(String, schoolName);      // 学校名称（org.name）
    DTO_FIELD(String, gradeName);       // 年级名称（class_grade.name）
    DTO_FIELD(String, counselorName);   // 顾问姓名（staff.name）
    DTO_FIELD(String, birthday);        // 生日（student.birthday）
};

#include OATPP_CODEGEN_END(DTO)
#endif