#include "stdafx.h"
#include "addintendedstudentcontroller.h"
#include "../../service/service-huitailang/intendstudent/intendstudentservice.h"


StringJsonVO::Wrapper addintendedstudent::executeaddintendedstudent(const intendedstudentDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();

	// 参数校验
	std::string errmsg = dto->validate();
	if (errmsg != "")
	{
		//jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	 //执行数据新增
	dto->setPayload(&payload);
	uint64_t id = IntendstudentService().addintendstudent(dto);
	if (id != 0) {
		jvo->success(std::to_string(id));
	}
	else
	{
		jvo->fail("");
	}
	//响应结果
	return jvo;
	
	
}