#pragma once
#pragma once
#ifndef _COURSE_TRIAL_DTO_
#define _COURSE_TRIAL_DTO_

#include "../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 课程体验卡DTO
 * 对应数据库表 course_trial
 * 无分页需求，仅保留核心数据传输字段
 */
class UseTrialcardDTO : public oatpp::DTO
{
    DTO_INIT(UseTrialcardDTO, DTO);

    // 主键
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.id");
    }

    // 课程ID
    DTO_FIELD(Int64, course_id);
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.course_id");
    }

    // 体验卡名称
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

    // 领取后有效天数
    DTO_FIELD(Int32, expire_days);
    DTO_FIELD_INFO(expire_days) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.expire_days");
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

    // 创建人ID
    DTO_FIELD(Int64, creator);
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.creator");
    }

    // 编辑人ID
    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.editor");
    }

    // 添加时间
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.add_time");
    }

    // 编辑时间
    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.edit_time");
    }

    // 删除标记
    DTO_FIELD(Int32, deleted);
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.deleted");
    }

    // 创建者所属组织ID
    DTO_FIELD(Int64, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("c5.home.course.trial.field.org_id");
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_COURSE_TRIAL_DTO_