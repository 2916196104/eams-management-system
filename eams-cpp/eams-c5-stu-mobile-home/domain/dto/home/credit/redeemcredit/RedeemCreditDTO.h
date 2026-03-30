#pragma once



#ifndef _REDEEMCREDIT_DTO_
#define _REDEEMCREDIT_DTO_
#include "../../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RedeemCreditDTO : public oatpp::DTO
{
	DTO_INIT(RedeemCreditDTO, DTO);

	DTO_FIELD(UInt64, credit_id);
	DTO_FIELD_INFO(credit_id) {
		info->description = ZH_WORDS_GETTER("redeemcredit.field.credit_id");
	}

	DTO_FIELD(UInt64, student_id);
	DTO_FIELD_INFO(student_id) {
		info->description = ZH_WORDS_GETTER("redeemcredit.field.student_id");
	}

	DTO_FIELD(UInt64, school_id);
	DTO_FIELD_INFO(school_id) {
		info->description = ZH_WORDS_GETTER("redeemcredit.field.school_id");
	}

	DTO_FIELD(Int32, redeem_count);
	DTO_FIELD_INFO(redeem_count) {
		info->description = ZH_WORDS_GETTER("redeemcredit.field.redeem_count");
	}

	
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};






#include OATPP_CODEGEN_END(DTO)
#endif