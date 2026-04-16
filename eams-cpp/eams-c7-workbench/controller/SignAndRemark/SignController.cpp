#include"stdafx.h"
#include "SignController.h"
#include "service/SignAndRemark/SignService.h"

SignPageJsonVO::Wrapper SignController::execQuerySignPage(const SignQuery::Wrapper& query, const PayloadDTO& payload)
{
	// ÏÔÊ½ÉèÖÃ PayloadDTO
	query->setPayload(&payload);

	SignService us;
	auto vo = SignPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}
