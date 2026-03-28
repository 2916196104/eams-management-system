#include"stdafx.h"
#include "SchedulingController.h"
#include"../../service/makabaka-service/SchedulingService.h"

StringJsonVO::Wrapper SchedulingController::executeaddRepateScheduling(const RepeatedSchedulingDTO::Wrapper& dto,const PayloadDTO& payload){
	//定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	//参数校验
	std::string errmsg = dto->validate();
	if (errmsg != "") {
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}
	//执行插入
	dto->setPayload(&payload);
	if(SchedulingService().addRepeatScheduling(dto,payload)) {
		jvo->success(std::string("add repeat scheduling success."));
	}
	else {
		jvo->fail(std::string("add repeat scheduling failed."));
	}
	//响应结果
	return jvo;
}

StringJsonVO::Wrapper SchedulingController::executeaddFreeScheduling(const FreeSchedulingDTO::Wrapper& dto, const PayloadDTO& payload) {
	//定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	//参数校验
	std::string errmsg = dto->validate();
	if(errmsg != "") {
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}
	//执行插入
	dto->setPayload(&payload);
	if(SchedulingService().addFreeScheduling(dto,payload)) {
		jvo->success(std::string("add free scheduling success."));
	}
	else {
		jvo->fail(std::string("add free scheduling failed."));
	}
	//响应结果
	return jvo;
}