#pragma once
#ifndef __LESSON_QUERY_H__
#define __LESSON_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课次分页查询对象
 */
class LessonQuery : public PageQuery
{
    DTO_INIT(LessonQuery, PageQuery);

    // 课程标题（模糊查询）
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("lesson.field.title");
    }

    // 课程ID（精确查询）
    DTO_FIELD(String, course_id);
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("lesson.field.course_id");
    }

    // 班级ID（精确查询）
    DTO_FIELD(String, class_id);
    DTO_FIELD_INFO(class_id) {
        info->description = ZH_WORDS_GETTER("lesson.field.class_id");
    }

    // 主讲人ID（精确查询）
    DTO_FIELD(String, teacher_id);
    DTO_FIELD_INFO(teacher_id) {
        info->description = ZH_WORDS_GETTER("lesson.field.teacher_id");
    }

    // 上课日期（精确查询，yyyy-MM-dd）
    DTO_FIELD(String, date);
    DTO_FIELD_INFO(date) {
        info->description = ZH_WORDS_GETTER("lesson.field.date");
    }

    // 课次状态（精确查询）
    DTO_FIELD(String, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("lesson.field.state");
    }

    // 是否开放预约（精确查询）
    DTO_FIELD(String, bookable);
    DTO_FIELD_INFO(bookable) {
        info->description = ZH_WORDS_GETTER("lesson.field.bookable");
    }

    // 学校ID（精确查询）
    DTO_FIELD(String, school_id);
    DTO_FIELD_INFO(school_id) {
        info->description = ZH_WORDS_GETTER("lesson.field.school_id");
    }

    // 组织ID（精确查询）
    DTO_FIELD(String, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("lesson.field.org_id");
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif // __LESSON_QUERY_H__