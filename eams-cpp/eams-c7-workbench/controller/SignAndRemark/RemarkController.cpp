#include"stdafx.h"
#include "RemarkController.h"
#include "service/SignAndRemark/RemarkService.h"


RemarkPageJsonVO::Wrapper RemarkController::execQueryRemarkPage(const RemarkQuery::Wrapper& query, const PayloadDTO& payload)
{
	// ÏÔÊ½ÉèÖÃ PayloadDTO
	query->setPayload(&payload);

	RemarkService us;
	auto vo = RemarkPageJsonVO::createShared();
	vo->success(us.listAll(query));
	return vo;
}
