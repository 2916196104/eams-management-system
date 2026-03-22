#pragma once

#ifndef _CLASS_DETAIL_DTO_
#define _CLASS_DETAIL_DTO_

#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配 class 表字段，仅保留核心字段
class ClassDetailDTO : public oatpp::DTO
{
    DTO_INIT(ClassDetailDTO, DTO);

    // ========== 仅保留 class 表的核心字段 ==========
    // 1. 主键ID
    DTO_FIELD(Int64, id);  // 适配 bigint unsigned → Int64
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.id");
    }

    // 2. 班级名
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.name");
    }

    // 3. 课程ID
    DTO_FIELD(Int64, course_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.course_id");
    }

    // 4. 教室ID
    DTO_FIELD(Int64, classroom_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(classroom_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.classroom_id");
    }

    // 5. 创建人
    DTO_FIELD(Int64, creator);  // 适配 bigint → Int64
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.creator");
    }

    // 6. 编辑者
    DTO_FIELD(Int64, editor);  // 适配 bigint → Int64
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.editor");
    }

    // 7. 添加时间
    DTO_FIELD(String, add_time);  // 适配 datetime → String
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.add_time");
    }

    // 8. 编辑时间
    DTO_FIELD(String, edit_time);  // 适配 datetime → String
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.edit_time");
    }

    // 9. 删除标记
    DTO_FIELD(Boolean, deleted);  // 适配 tinyint(1) → Boolean
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.deleted");
    }

    // 10. 班级负责人
    DTO_FIELD(Int64, teacher_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(teacher_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.teacher_id");
    }

    // 11. 排课备注
    DTO_FIELD(String, remark);
    DTO_FIELD_INFO(remark) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.remark");
    }

    // 12. 是否完结
    DTO_FIELD(Boolean, be_over);  // 适配 tinyint(1) → Boolean
    DTO_FIELD_INFO(be_over) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.be_over");
    }

    // 13. 完结时间
    DTO_FIELD(String, over_time);  // 适配 datetime → String
    DTO_FIELD_INFO(over_time) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.over_time");
    }

    // 14. 完结操作人
    DTO_FIELD(Int64, over_operator);  // 适配 bigint → Int64
    DTO_FIELD_INFO(over_operator) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.over_operator");
    }

    // 15. 计划开班日期
    DTO_FIELD(String, start_date);  // 适配 date → String
    DTO_FIELD_INFO(start_date) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.start_date");
    }

    // 16. 计划结业日期
    DTO_FIELD(String, end_date);  // 适配 date → String
    DTO_FIELD_INFO(end_date) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.end_date");
    }

    // 17. 预招人数
    DTO_FIELD(Int32, planned_student_count);  // 适配 int → Int32
    DTO_FIELD_INFO(planned_student_count) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.planned_student_count");
    }

    // 18. 预排课次数
    DTO_FIELD(Int32, planned_lesson_count);  // 适配 int → Int32
    DTO_FIELD_INFO(planned_lesson_count) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.planned_lesson_count");
    }

    // 19. 创建者所属学校ID
    DTO_FIELD(Int64, school_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(school_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.school_id");
    }

    // 20. 创建者所属组织ID
    DTO_FIELD(Int64, org_id);  // 适配 bigint → Int64
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.org_id");
    }

    // 21. 年级ID
    DTO_FIELD(Int32, grade_id);  // 适配 int → Int32
    DTO_FIELD_INFO(grade_id) {
        info->description = ZH_WORDS_GETTER("c5.home.class.class.field.grade_id");
    }

    // 保留原有Payload字段（若业务需要）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配 ClassDetailDTO
class ClassDetailPageDTO : public PageDTO<ClassDetailDTO::Wrapper>
{
    DTO_INIT(ClassDetailPageDTO, PageDTO<ClassDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASS_DETAIL_DTO_