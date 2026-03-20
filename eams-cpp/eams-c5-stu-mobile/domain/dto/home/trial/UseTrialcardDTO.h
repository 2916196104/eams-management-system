#pragma once
#ifndef _USETrialCARD_DTO_
#define _USETrialCARD_DTO_

#include "../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 使用课程体验卡DTO
 * 对应数据库表 course_trial
 */
class UseTrialcardDTO : public oatpp::DTO
{
    DTO_INIT(UseTrialcardDTO, DTO);
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

    // 领取时间（使用时需关联）
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.add_time");
    }

    // 到期时间
    DTO_FIELD(String, expired_date);
    DTO_FIELD_INFO(expired_date) {
        info->description = ZH_WORDS_GETTER("c5.home.get-trial.field.expired_date");
    }

    // 剩余可使用课时数（使用后扣减）
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

    // 发行数量
    DTO_FIELD(Int32, quantity);
    DTO_FIELD_INFO(quantity) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.quantity");
    }

    // 剩余数量
    DTO_FIELD(Int32, remaining_quantity);
    DTO_FIELD_INFO(remaining_quantity) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.remaining_quantity");
    }

    // 发行结束日期
    DTO_FIELD(String, end_date);
    DTO_FIELD_INFO(end_date) {
        info->description = ZH_WORDS_GETTER("c5.home.use-field.end_date");
    }

};

#include OATPP_CODEGEN_END(DTO)

#endif 