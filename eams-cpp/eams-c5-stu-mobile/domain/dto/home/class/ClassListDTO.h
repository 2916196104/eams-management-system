#pragma once

#ifndef _CLASSLISTDTO_H_
#define _CLASSLISTDTO_H_

#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配 class 表字段，仅保留核心字段
class ClassListDTO : public oatpp::DTO
{
    DTO_INIT(ClassListDTO, DTO);

    // ========== 仅保留 class 表的核心字段 ==========
    // 1. 主键ID
    DTO_FIELD(Int64, id);  // 适配 bigint unsigned → Int64
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.ClassList.field.id");
    }

    // 2. 班级名
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("c5.home.class.ClassList.field.name");
    }

    // 3. 课程ID
    DTO_FIELD(Int64, course_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.ClassList.field.course_id");
    }

   
    // 10. 班级负责人
    DTO_FIELD(Int64, teacher_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(teacher_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.ClassList.field.teacher_id");
    }

    // 保留原有Payload字段（若业务需要）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配 ClassDetailDTO
class ClassListPageDTO : public PageDTO<ClassListDTO::Wrapper>
{
    DTO_INIT(ClassListPageDTO, PageDTO<ClassListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASS_DETAIL_DTO_