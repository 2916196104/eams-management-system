#pragma once
#ifndef __LESSON_QUERY_H__
#define __LESSON_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程查询参数（支持分页和业务筛选）
 */
class LessonQuery : public PageQuery
{
    DTO_INIT(LessonQuery, PageQuery);

    // 课程名称（模糊查询）
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("lesson.title");
    }

    // 适用学校ID（精确查询）
    DTO_FIELD(Int64, schoolId);
    DTO_FIELD_INFO(schoolId) {
        info->description = ZH_WORDS_GETTER("lesson.school");
    }

    // 科目ID（精确查询）
    DTO_FIELD(Int64, courseId);
    DTO_FIELD_INFO(courseId) {
        info->description = ZH_WORDS_GETTER("lesson.course");
    }

    // 状态（1:正常 2:已关闭）
    DTO_FIELD(Int32, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("lesson.state");
    }

    // 适用年级ID（精确查询）
    DTO_FIELD(Int64, classId);
    DTO_FIELD_INFO(classId) {
        info->description = ZH_WORDS_GETTER("lesson.classId");
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif // __LESSON_QUERY_H__