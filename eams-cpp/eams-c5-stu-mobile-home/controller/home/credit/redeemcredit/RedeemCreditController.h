
#ifndef _TESTCONTROLLER_H_
#define _TESTCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/dto/home/credit/redeemcredit/RedeemCreditDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("redeemcredit.tag")

class RedeemCreditController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(RedeemCreditController);
public:

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("redeemcredit.summary"), redeemcredit, StringJsonVO::Wrapper, API_TAG);

	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c5home/credit/redeemcredit", redeemcredit, BODY_DTO(RedeemCreditDTO::Wrapper, dto), execRedeemCredit(dto, authObject->getPayload()));


private:
	StringJsonVO::Wrapper execRedeemCredit(const RedeemCreditDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)


#endif