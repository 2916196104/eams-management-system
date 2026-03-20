#pragma once



#ifndef _LESSONCOMMENT_DTO_
#define _LESSONCOMMENT_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class LessonCommentDTO : public oatpp::DTO
{
	DTO_INIT(LessonCommentDTO, DTO);
    // 主键 ID
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.id");
    }

    // 课程id
    DTO_FIELD(Int64, lesson_id);
    DTO_FIELD_INFO(lesson_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.lesson_id");
    }

    // 班级id (为空表示调课生)
    DTO_FIELD(Int32, class_id);
    DTO_FIELD_INFO(class_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.class_id");
    }

    // 学员id
    DTO_FIELD(Int64, student_id);
    DTO_FIELD_INFO(student_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.student_id");
    }

    // 实扣课次
    DTO_FIELD(Int32, dec_lesson_count);
    DTO_FIELD_INFO(dec_lesson_count) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.dec_lesson_count");
    }

    // 应扣课次
    DTO_FIELD(Int32, lesson_count);
    DTO_FIELD_INFO(lesson_count) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.lesson_count");
    }

    // 点名的老师
    DTO_FIELD(Int64, teacher_id);
    DTO_FIELD_INFO(teacher_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.teacher_id");
    }

    // 签到时间
    DTO_FIELD(String, sign_time);
    DTO_FIELD_INFO(sign_time) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.sign_time");
    }

    // 签到方式
    DTO_FIELD(Int32, sign_type);
    DTO_FIELD_INFO(sign_type) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.sign_type");
    }

    // 签到结果
    DTO_FIELD(Int32, sign_state);
    DTO_FIELD_INFO(sign_state) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.sign_state");
    }

    // 老师评分
    DTO_FIELD(Int32, score);
    DTO_FIELD_INFO(score) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.score");
    }

    // 老师评语
    DTO_FIELD(String, evaluation);
    DTO_FIELD_INFO(evaluation) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.evaluation");
    }

    // 评语时间
    DTO_FIELD(String, evaluate_time);
    DTO_FIELD_INFO(evaluate_time) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.evaluate_time");
    }

    // 评语老师id
    DTO_FIELD(Int64, evaluate_teacher_id);
    DTO_FIELD_INFO(evaluate_teacher_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.evaluate_teacher_id");
    }

    DTO_FIELD(String, evaluate_teacher);
    DTO_FIELD_INFO(evaluate_teacher) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.evaluate_teacher");
    }

    // 实际消费课程
    DTO_FIELD(Int64, consume_course_id);
    DTO_FIELD_INFO(consume_course_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.consume_course_id");
    }

    // 消费课程与学生关联表ID
    DTO_FIELD(Int64, consume_student_course_id);
    DTO_FIELD_INFO(consume_student_course_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.consume_student_course_id");
    }

    // 学生的顾问
    DTO_FIELD(Int64, counselor);
    DTO_FIELD_INFO(counselor) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.counselor");
    }

    // 加入时间
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.add_time");
    }

    // 上课老师所属组织ID
    DTO_FIELD(Int64, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("LessonComment.field.org_id");
    }
};

class LessonCommentPageDTO : public PageDTO<LessonCommentDTO::Wrapper>
{
    DTO_INIT(LessonCommentPageDTO, PageDTO<LessonCommentDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif