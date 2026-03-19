#pragma once
#ifndef _GETTRIALCARDCONTROLLER_
#define _GETTRIALCARDCONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/home/trialCard/GetTrialCardListVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class GetTrialCardListController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetTrialCardListController);
public:
	// 定义ID查询接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("home.trialCard.getTrialCardList.info"), getTrialCardList, GetTrialCardListPageJsonVO::Wrapper, "Schedule",
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("student.id"); , "d934050a8bb373e8f8eed0bf7507ec17", true);
	);
	// 定义ID查询接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/app/sCenter/home/trialCard/GetTrialCardList", 
		getTrialCardList, QUERY(String, id), executeGetCardById(id));
private:
	GetTrialCardListPageJsonVO::Wrapper executeGetCardById(String id);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_GETTRIALCARDCONTROLLER_
