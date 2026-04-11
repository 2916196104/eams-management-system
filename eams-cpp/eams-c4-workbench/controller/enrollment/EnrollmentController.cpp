#include"EnrollmentController.h"
#include"../../service/EnrollmentService/EnrollmentService.h"
#include"stdafx.h"

StringJsonVO::Wrapper EnrollmentController::execSaveEnrolled(const EnrollDTO::Wrapper& dto, const PayloadDTO& payload)
{
	//定义返回数据对象
	auto Jvo = StringJsonVO::createShared();

	// 1.参数校验
	std::string errorMsg = dto->validate();

	if(errorMsg!="")
	{
		Jvo->init(nullptr, RS_PARAMS_INVALID);
		return Jvo;
	}

	// 2.执行报名保存逻辑
	dto->setPayload(&payload);
	auto id = EnrollmentService().saveEnrollment(dto);
	if(id!="")
	{
		Jvo->success(id);
	}
	else
	{
		Jvo->fail("");
	}
	// 3.响应结果
	return Jvo;
}