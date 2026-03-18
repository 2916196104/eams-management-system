#pragma once

#ifndef _TIMEABLE_DTO_
#define _TIMEABLE_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配class_student表字段，删除无关字段，保留核心字段
//class ClassStudentDTO : public oatpp::DTO
//{
//    DTO_INIT(ClassStudentDTO, DTO);
//
//    // ========== 仅保留class_student表的核心字段（与ClassStudentDO完全对应） ==========
//    // 1. 主键ID
//    DTO_FIELD(Int64, id);  // 适配uint64_t → Int64
//    DTO_FIELD_INFO(id) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.id");
//    }
//
//    // 2. 班级ID
//    DTO_FIELD(Int64, class_id);  // 适配uint64_t → Int64
//    DTO_FIELD_INFO(class_id) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.class_id");
//    }
//
//    // 3. 学生ID
//    DTO_FIELD(Int64, student_id);  // 适配uint64_t → Int64
//    DTO_FIELD_INFO(student_id) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.student_id");
//    }
//
//    // 4. 添加时间
//    DTO_FIELD(String, add_time);
//    DTO_FIELD_INFO(add_time) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.add_time");
//    }
//
//    // 5. 创建人
//    DTO_FIELD(Int64, creator);  // 适配uint64_t → Int64
//    DTO_FIELD_INFO(creator) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.creator");
//    }
//
//    // 6. 加入原因
//    DTO_FIELD(Int32, reason);  // 适配tinyint → Int32
//    DTO_FIELD_INFO(reason) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.reason");
//    }
//
//    // 7. 删除标记
//    DTO_FIELD(Boolean, deleted);  // 适配tinyint(1) → Boolean
//    DTO_FIELD_INFO(deleted) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.deleted");
//    }
//
//    // 8. 备注信息
//    DTO_FIELD(String, remark);
//    DTO_FIELD_INFO(remark) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.remark");
//    }
//
//    // 9. 默认消费课程ID
//    DTO_FIELD(Int64, consume_course_id);  // 适配uint64_t → Int64
//    DTO_FIELD_INFO(consume_course_id) {
//        info->description = ZH_WORDS_GETTER("ClassStudent.field.consume_course_id");
//    }
//
//    // 保留原有Payload字段（若业务需要）
//    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
//};
class ScheduleTimeableDTO : public oatpp::DTO
{
    DTO_INIT(ScheduleTimeableDTO, DTO);



    // 保留原有Payload字段（若业务需要）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

    // 分页DTO：适配ClassStudentDTO
//class ClassStudentPageDTO : public PageDTO<ClassStudentDTO::Wrapper>
//{
//    DTO_INIT(ClassStudentPageDTO, PageDTO<ClassStudentDTO::Wrapper>);
//};
class ScheduleTimeablePageDTO : public PageDTO<ScheduleTimeableDTO::Wrapper>
{
    DTO_INIT(ScheduleTimeablePageDTO, PageDTO<ScheduleTimeableDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_TIMEABLE_DTO_