#pragma once
#ifndef _LEAVECONTROLLER_H
#define _LEAVECONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "../../domain/vo/schedule/LeaveVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("leave.tag")
class LeaveController :public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(LeaveController);
public:
	// 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("leave.summary"), addLeave, LeaveJsonVO::Wrapper, API_TAG);

	// 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c5/schedule/leave", addLeave, BODY_DTO(LeaveDTO::Wrapper, add), execAddLeave(add));

private:
	StringJsonVO::Wrapper execAddLeave(const LeaveDTO::Wrapper& add);
};
#include OATPP_CODEGEN_END(ApiController)


#endif // !_LEAVECONTROLLER_H


