#pragma once
#ifndef _CLASS_STUDENT_DTO_
#define _CLASS_STUDENT_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassStudentDTO : public oatpp::DTO
{
    DTO_INIT(ClassStudentDTO, DTO);

    // 只保留这两个字段，其他全部删除
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("c5.home.class.classstudent.field.name");
    }

    DTO_FIELD(Int32, gender);
    DTO_FIELD_INFO(gender) {
        info->description = ZH_WORDS_GETTER("c5.home.class.classstudent.field.gender");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif