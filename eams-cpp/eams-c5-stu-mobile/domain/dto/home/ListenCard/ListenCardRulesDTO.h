#pragma once
#ifndef _LISTEN_CARD_RULES_DTO_H
#define _LISTEN_CARD_RULES_DTO_H
#include"../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class ListenCardRulesDTO:public oatpp::DTO{
	DTO_INIT(ListenCardRulesDTO, DTO);
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.id");
    }

    DTO_FIELD(Int64, course_id);
    DTO_FIELD_INFO(course_id) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.course_id");
    }

    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.course_id");
    }

    DTO_FIELD(Int32, quantity);
    DTO_FIELD_INFO(quantity) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.quantity");
    }

    DTO_FIELD(Int32, remaining_quantity);
    DTO_FIELD_INFO(remaining_quantity) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.remaining_quantity");
    }

    DTO_FIELD(Int32, lesson_count);
    DTO_FIELD_INFO(lesson_count) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.lesson_count");
    }

    DTO_FIELD(Int32, expire_days);
    DTO_FIELD_INFO(expire_days) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.expire_days");
    }

    DTO_FIELD(String, end_date);
    DTO_FIELD_INFO(end_date) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.end_date");
    }

    DTO_FIELD(Int8, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.state");
    }

    DTO_FIELD(Int64, creator);
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.creator");
    }

    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.editor");
    }

    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.add_time");
    }

    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.edit_time");
    }

    DTO_FIELD(Int8, deleted);
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.deleted");
    }

    DTO_FIELD(Int64, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("ListenCardRules.field.org_id");
    }
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif 
