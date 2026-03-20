
#include "RedeemCreditController.h"


StringJsonVO::Wrapper RedeemCreditController::execRedeemCredit(const RedeemCreditDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();


	dto->setPayload(&payload);


	jvo->success(ZH_WORDS_GETTER("redeemcredit.request-success"));
	return jvo;

}