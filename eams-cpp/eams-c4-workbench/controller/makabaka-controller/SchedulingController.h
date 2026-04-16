#pragma once
#ifndef _SCHEDULINGCONTROLLER_H_
#define _SCHEDULINGCONTROLLER_H_
#include"ServerInfo.h"
#include"Macros.h"
#include"../../domain/dto/makabaka-dto/RepeatedSchedulingDTO.h"
#include"../../domain/vo/makabaka-vo/RepeateSchedulingVO.h"
#include"../../domain/dto/makabaka-dto/FreeSchedulingDTO.h"
#include"domain/vo/BaseJsonVO.h"
#include"../lib-oatpp/include/ApiHelper.h"
#define API_TAG  ZH_WORDS_GETTER("schedule.api.tag")
#include OATPP_CODEGEN_BEGIN(ApiController)

class SchedulingController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(SchedulingController);
public:
	//定义重复排课接口
	//定义接口描述，添加授权定义
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("schedule.api.createRepeat"),
		addRepateScheduling,
		RepeatedSchedulingVO::Wrapper, 
		API_TAG);
	//定义接口处理函数
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4-workbench/scheduling/repeat/create",
		addRepateScheduling,
		BODY_DTO(RepeatedSchedulingDTO::Wrapper, dto),
		executeaddRepateScheduling(dto, authObject->getPayload()));

	//定义自由排课接口
	//定义接口描述，添加授权定义
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("schedule.api.createFree"),
		addFreeScheduling,
		StringJsonVO::Wrapper,
		API_TAG);
	//定义接口处理函数
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4-workbench/scheduling/free/create",
		addFreeScheduling,
		BODY_DTO(FreeSchedulingDTO::Wrapper, dto),
		executeaddFreeScheduling(dto, authObject->getPayload()));
private:
	StringJsonVO::Wrapper executeaddRepateScheduling(const RepeatedSchedulingDTO::Wrapper& dto,const PayloadDTO& payload);
	StringJsonVO::Wrapper executeaddFreeScheduling(const FreeSchedulingDTO::Wrapper& dto, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG

#endif // !_SCHEDULINGCONTROLLER_H_