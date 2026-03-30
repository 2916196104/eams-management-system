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
class GetTimeableDTO : public oatpp::DTO
{
    DTO_INIT(GetTimeableDTO, DTO);

    // ========== 1. 核心字段定义（和 DO/映射逻辑完全对齐） ==========
    // 课程ID
    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("Timeable.field.id"); // 课程ID
    }

    // 课程标题
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("Timeable.field.title"); // 课程标题
    }

    // 课程序号
    DTO_FIELD(String, sn);
    DTO_FIELD_INFO(sn) {
        info->description = ZH_WORDS_GETTER("Timeable.field.sn"); // 课程序号
    }

    // 上课日期（保留原有）
    DTO_FIELD(String, date);
    DTO_FIELD_INFO(date) {
        info->description = ZH_WORDS_GETTER("Timeable.field.date"); // 日期（若有专属key可替换，比如"sample.field.date"）
    }

    // 开始时间
    DTO_FIELD(String, start_time);
    DTO_FIELD_INFO(start_time) {
        info->description = ZH_WORDS_GETTER("Timeable.field.start_time"); // 开始时间
    }

    // 结束时间
    DTO_FIELD(String, end_time);
    DTO_FIELD_INFO(end_time) {
        info->description = ZH_WORDS_GETTER("Timeable.field.end_time"); // 结束时间
    }

    // 教师ID
    DTO_FIELD(Int32, teacher_id);
    DTO_FIELD_INFO(teacher_id) {
        info->description = ZH_WORDS_GETTER("Timeable.field.teacher_id"); // 教师ID
    }

    // 排课计划ID
    DTO_FIELD(Int32, schedule_id);
    DTO_FIELD_INFO(schedule_id) {
        info->description = ZH_WORDS_GETTER("Timeable.field.schedule_id"); // 排课计划ID
    }

    // 教师姓名
    DTO_FIELD(String, teacher_name);
    DTO_FIELD_INFO(teacher_name) {
        info->description = ZH_WORDS_GETTER("Timeable.field.teacher_name"); // 教师姓名
    }

    // 签到状态
    DTO_FIELD(Int32, sign_state);
    DTO_FIELD_INFO(sign_state) {
        info->description = ZH_WORDS_GETTER("Timeable.field.sign_state"); // 签到状态
    }

    // ========== 2. 保留原有Payload字段（不改动） ==========
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

    // 分页DTO：适配ClassStudentDTO
//class ClassStudentPageDTO : public PageDTO<ClassStudentDTO::Wrapper>
//{
//    DTO_INIT(ClassStudentPageDTO, PageDTO<ClassStudentDTO::Wrapper>);
//};
class GetTimeablePageDTO : public PageDTO<GetTimeableDTO::Wrapper>
{
    DTO_INIT(GetTimeablePageDTO, PageDTO<GetTimeableDTO::Wrapper>);
};

//// 1. 主键ID（bigint unsigned → Int64）
//DTO_FIELD(Int64, id);
//DTO_FIELD_INFO(id) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.id");
//}
//// 2. 所属课程ID（bigint → Int64，NOT NULL）
//DTO_FIELD(Int64, course_id);
//DTO_FIELD_INFO(course_id) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.course_id");
//}
////3.章节标题(varchar(255))
//DTO_FIELD(String, title);
//DTO_FIELD_INFO(title) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.title");
//}
////4.计划课时数(int)
//DTO_FIELD(Int64, lesson_count);
//DTO_FIELD_INFO(lesson_count) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.lesson_count");
//}
////5.创建人(bigint → Int64，NOT NULL)
//DTO_FIELD(String, creator);
//DTO_FIELD_INFO(creator) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.creato");
//}
////6.编辑者(bigint → Int64，NOT NULL)
//DTO_FIELD(String, editor);
//DTO_FIELD_INFO(editor) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.editor");
//}
////7.添加时间（datetime → String）
//DTO_FIELD(String, add_time);
//DTO_FIELD_INFO(add_time) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.add_time");
//}
////8..修改时间（datetime → String）
//DTO_FIELD(String, edit_time);
//DTO_FIELD_INFO(edit_time) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.edit_time");
//
////9.删除标记（tinyint(1) → Boolean，DEFAULT '0'）
//DTO_FIELD(String, deleted);
//DTO_FIELD_INFO(deleted) {
//    info->description = ZH_WORDS_GETTER("c5.schedule.Timeable.field.deleted");

#include OATPP_CODEGEN_END(DTO)
#endif // !_TIMEABLE_DTO_