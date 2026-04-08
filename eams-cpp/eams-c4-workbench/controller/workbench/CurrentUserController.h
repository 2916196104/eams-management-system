#pragma once
#ifndef _CURRENT_USER_CONTROLLER_H_
#define _CURRENT_USER_CONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/workbench/CurrentUserVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("workbench-he.tag")

class CurrentUserController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(CurrentUserController);
public:
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("workbench-he.queryCurrentUserInfo.summary"), queryCurrentUserInfo, CurrentUserInfoJsonVO::Wrapper, API_TAG);
	ENDPOINT(API_M_GET, "/c4-workbench/queryCurrentUserInfo", queryCurrentUserInfo, API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(execQueryCurrentUserInfo(authObject));
	}

private:
	CurrentUserInfoJsonVO::Wrapper execQueryCurrentUserInfo(const std::shared_ptr<CustomerAuthorizeObject>& authObject);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif
