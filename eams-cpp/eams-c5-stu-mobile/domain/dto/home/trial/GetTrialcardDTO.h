#pragma once
#ifndef _COURSE_TRIAL_DTO_
#define _COURSE_TRIAL_DTO_

#include "../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程体验卡DTO
 * 对应数据库表 course_trial
 */
class GetTrialcardDTO : public oatpp::DTO
{
    DTO_INIT(GetTrialcardDTO, DTO);

    // 主键
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.id");
    }

    // 课程
    DTO_FIELD(Int64, course_id);
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.course_id");
    }

    // 名称
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.title");
    }

    // 发行数量
    DTO_FIELD(Int32, quantity);
    DTO_FIELD_INFO(quantity) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.quantity");
    }

    // 剩余数量
    DTO_FIELD(Int32, remaining_quantity);
    DTO_FIELD_INFO(remaining_quantity) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.remaining_quantity");
    }

    // 课时数
    DTO_FIELD(Int32, lesson_count);
    DTO_FIELD_INFO(lesson_count) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.lesson_count");
    }

    // 发行结束日期
    DTO_FIELD(String, end_date);
    DTO_FIELD_INFO(end_date) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.end_date");
    }

    // 启用状态
    DTO_FIELD(Int32, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.state");
    }

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSE_TRIAL_DTO_