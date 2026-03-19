#pragma once
#ifndef _INTENDEDSTUDENT_DTO_
#define _INTENDEDSTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据新增对象
 */
class IntendAddDTO : public oatpp::DTO
{
	DTO_INIT(IntendAddDTO, DTO);
    // Excel 列对应字段（按顺序）
    // 第1列：*姓名（必填）
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.name");
    }

    // 第2列：*手机号（必填）
    DTO_FIELD(String, mobile);
    DTO_FIELD_INFO(mobile) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.mobile");
    }

    // 第3列：*登录密码（必填）
    DTO_FIELD(String, password);
    DTO_FIELD_INFO(password) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.password");
    }

    // 第4列：家长姓名（可选）
    DTO_FIELD(String, parent);
    DTO_FIELD_INFO(parent) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.parent");
    }

    // 第5列：性别(有效值:男|女|未知)
    DTO_FIELD(String, sex);
    DTO_FIELD_INFO(sex) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.sex");
    }

    // 第6列：生日(格式:2000-01-01)
    DTO_FIELD(String, birthday);
    DTO_FIELD_INFO(birthday) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.birthday");
    }

    // 第7列：身份证（可选）
    DTO_FIELD(String, idCard);
    DTO_FIELD_INFO(idCard) {
        info->description = ZH_WORDS_GETTER("intendedstudent.field.student.idcard");
    }

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
        if (sex && !sex->empty()) {
            if (
                *sex != ZH_WORDS_GETTER("intendedstudent.field.student.male") 
                && *sex != ZH_WORDS_GETTER("intendedstudent.field.student.fmale")
                && *sex != ZH_WORDS_GETTER("intendedstudent.field.student.unknown")
                )
                return "sex invalidate.";
        }

        // 生日格式校验（简单校验，也可省略让数据库处理）
        if (birthday && !birthday->empty()) {
            if (birthday->length() != 10 || (*birthday)[4] != '-' || (*birthday)[7] != '-')
                return "biryhday invalidate.";
        }

        return "";
    }

};

/**
 * excel导入对象
 */
class IntendImportDTO : public oatpp::DTO
{
	DTO_INIT(IntendImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("intendedstudent.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif