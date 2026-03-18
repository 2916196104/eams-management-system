#pragma once
#ifndef _CREDITEXCHANGELIST_DTO_
#define _CREDITEXCHANGELIST_DTO_

#include "../../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class CreditexchangelistDTO : public oatpp::DTO
{
	DTO_INIT(CreditexchangelistDTO, DTO);

	DTO_FIELD(Int32, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.id");
	}

	DTO_FIELD(Int32, credit_mall_id);
	DTO_FIELD_INFO(credit_mall_id) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.credit-mall-id");
	}

	DTO_FIELD(String, credit_mall_name);
	DTO_FIELD_INFO(credit_mall_name) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.credit-mall-name");
	}

	DTO_FIELD(Int32, num);
	DTO_FIELD_INFO(num) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.num");
	}

	DTO_FIELD(Int32, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.school-id");
	}

	DTO_FIELD(Int32, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.creator");
	}

	DTO_FIELD(Int32, editor);
	DTO_FIELD_INFO(editor) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.editor");
	}

	DTO_FIELD(String, add_time);
	DTO_FIELD_INFO(add_time) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.add-time");
	}

	DTO_FIELD(String, edit_time);
	DTO_FIELD_INFO(edit_time) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.edit-time");
	}

	DTO_FIELD(Int32, deleted);
	DTO_FIELD_INFO(deleted) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.deleted");
	}

	DTO_FIELD(Int32, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.student-id");
	}

	DTO_FIELD(Int32, user_id);
	DTO_FIELD_INFO(user_id) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.user-id");
	}

	DTO_FIELD(String, credit);
	DTO_FIELD_INFO(credit) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.credit");
	}

	DTO_FIELD(Int32, verify_state);
	DTO_FIELD_INFO(verify_state) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.verify-state");
	}

	DTO_FIELD(Int32, verify_staff);
	DTO_FIELD_INFO(verify_staff) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.verify-staff");
	}

	DTO_FIELD(String, verify_time);
	DTO_FIELD_INFO(verify_time) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.verify-time");
	}

	DTO_FIELD(String, verify_remark);
	DTO_FIELD_INFO(verify_remark) {
		info->description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.verify-remark");
	}
};

class CreditexchangelistPageDTO : public PageDTO<CreditexchangelistDTO::Wrapper>
{
	DTO_INIT(CreditexchangelistPageDTO, PageDTO<CreditexchangelistDTO::Wrapper>);
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_CREDITEXCHANGELIST_DTO_
