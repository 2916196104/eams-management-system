#pragma once
#ifndef _GETTRIALCARD_DTO_
#define _GETTRIALCARD_DTO_

#include "../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 获取课程体验卡DTO
 * 对应数据库表 course_trial_record（体验卡领取/使用记录）
 */
class GetTrialcardDTO : public oatpp::DTO
{
    DTO_INIT(GetTrialcardDTO, DTO);

    // 体验卡ID
    DTO_FIELD(Int64, trial_id);
    DTO_FIELD_INFO(trial_id) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.trial_id");
    }

    // 学生ID
    DTO_FIELD(Int64, student_id);
    DTO_FIELD_INFO(student_id) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.student_id");
    }

    // 学生账号ID
    DTO_FIELD(Int64, user_id);
    DTO_FIELD_INFO(user_id) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.user_id");
    }

    // 生成的学生课程关联ID
    DTO_FIELD(Int64, student_course_id);
    DTO_FIELD_INFO(student_course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.student_course_id");
    }

    // 领取时间
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.add_time");
    }

    // 到期时间
    DTO_FIELD(String, expired_date);
    DTO_FIELD_INFO(expired_date) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.expired_date");
    }

    // 领取到数量预约后减少
    DTO_FIELD(Int32, lesson_count);
    DTO_FIELD_INFO(lesson_count) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.lesson_count");
    }

    // 学生所属学校ID
    DTO_FIELD(Int64, school_id);
    DTO_FIELD_INFO(school_id) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.school_id");
    }

    // 学生的顾问
    DTO_FIELD(String, counselor);
    DTO_FIELD_INFO(counselor) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.counselor");
    }

    // 以下为 course_trial 表关联字段（使用体验卡时可能需要的基础信息）
    // 课程ID
    DTO_FIELD(Int64, course_id);
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.course_id");
    }

    // 体验卡名称
    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.title");
    }

    // 领取后有效天数
    DTO_FIELD(Int32, expire_days);
    DTO_FIELD_INFO(expire_days) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.expire_days");
    }

    // 启用状态
    DTO_FIELD(Int32, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.state");
    }

};

#include OATPP_CODEGEN_END(DTO)

#endif // 
