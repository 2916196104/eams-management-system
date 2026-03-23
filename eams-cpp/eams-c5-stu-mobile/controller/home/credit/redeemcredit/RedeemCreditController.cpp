
#include "RedeemCreditController.h"
#include "service/home/credit/redeemcredit/RedeemCreditService.h"

StringJsonVO::Wrapper RedeemCreditController::execRedeemCredit(const RedeemCreditDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();


	dto->setPayload(&payload);
	std::string res = RedeemCreditService().saveData(dto);

	jvo->success(res);
	return jvo;

}