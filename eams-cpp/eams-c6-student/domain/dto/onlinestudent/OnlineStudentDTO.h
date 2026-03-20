#pragma once
#ifndef _ONLINESTUDENT_DTO_
#define _ONLINESTUDENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 在线学员导入数据
 */
class OnlineAddDTO : public oatpp::DTO
{
	DTO_INIT(OnlineAddDTO, DTO);
    // Excel 列对应字段
    // 第 1 列：*学员姓名（必填）
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.name");
    }

    // 第 2 列：*家长姓名（必填）
    DTO_FIELD(String, parent);
    DTO_FIELD_INFO(parent) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.parent");
    }

    // 第 3 列：*亲属关系（必填）
    DTO_FIELD(String, parentRel);
    DTO_FIELD_INFO(parentRel) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.parent-rel");
    }

    // 第 4 列：*联系电话（必填）
    DTO_FIELD(String, mobile);
    DTO_FIELD_INFO(mobile) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.mobile");
    }

    // 第 5 列：*顾问（可选）
    DTO_FIELD(String, counselor);
    DTO_FIELD_INFO(counselor) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.counselor");
    }

    // 第 6 列：*年级（可选）
    DTO_FIELD(String, grade);
    DTO_FIELD_INFO(grade) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.grade");
    }

    // 第 7 列：*分校（可选）
    DTO_FIELD(String, school);
    DTO_FIELD_INFO(school) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.school");
    }

    // 第 8 列：*性别（可选）
    DTO_FIELD(String, sex);
    DTO_FIELD_INFO(sex) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.sex");
    }

    // 第 9 列：*年龄（必填）
    DTO_FIELD(Int32, age);
    DTO_FIELD_INFO(age) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.age");
    }

    // 第 10 列：备注（可选）
    DTO_FIELD(String, note);
    DTO_FIELD_INFO(note) {
        info->description = ZH_WORDS_GETTER("onlinestudent.field.student.note");
    }

    // 关联一个 PayloadDTO 负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
    // 数据校验
    std::string validate()
    {
        // 必填校验
        if (!name || name->empty())
            return "name invalidate.";
        if (!parent || parent->empty())
            return "parent invalidate.";
        if (!parentRel || parentRel->empty())
            return "parentRel invalidate.";
        if (!mobile || mobile->empty())
            return "mobile invalidate.";
        if (!age)
            return "age invalidate.";

        // 手机号格式
        if (mobile && mobile->length() != 11)
            return "mobile invalidate.";

        // 性别有效值校验（可选）
        if (sex && !sex->empty()) {
            if (
                *sex != ZH_WORDS_GETTER("onlinestudent.field.student.male") 
                && *sex != ZH_WORDS_GETTER("onlinestudent.field.student.female")
                )
                return "sex invalidate.";
        }

        return "";
    }

};

/**
 * 在线学员导入数据
 */
class OnlineImportDTO : public oatpp::DTO
{
	DTO_INIT(OnlineImportDTO, DTO);
	// 导入报表文件
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, excel, ZH_WORDS_GETTER("onlinestudent.field.excel"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif
