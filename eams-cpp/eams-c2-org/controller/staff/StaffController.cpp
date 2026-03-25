#include "stdafx.h"
#include "StaffController.h"

StringJsonVO::Wrapper StaffController::executeGetEmpList(const StaffPageQuery::Wrapper& query)
{

	//// 查询数据
	//auto result = StaffService().listAll(query);
	// 响应结果
	//auto jvo = StaffPageJsonVO::createShared();
	//jvo->success(result);
	//return jvo;


	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("getEmpList.controller.resp"));
	return vo;
}

StringJsonVO::Wrapper StaffController::executeSaveEmp(const StaffSaveDTO::Wrapper& dto)
{
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("getEmpList.controller.resp"));
	return vo;
}
