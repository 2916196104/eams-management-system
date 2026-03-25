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
#include "StaffController.h"



// 头像修改逻辑实现（和executeQueryTest格式一致）
StringJsonVO::Wrapper StaffController::executeModifyAvatar(const AvatarUploadDTO::Wrapper& dto) {
	// 创建响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("modifyAvatar.resp"));
	return vo;
}
#include "StaffController.h"

StringJsonVO::Wrapper StaffController::executegetDutyRecord(const DutyRecordQueryDTO::Wrapper& query) {
    //创建一个相应结果
    auto vo = StringJsonVO::createShared();
    vo->success(ZH_WORDS_GETTER("getDutyRecord.resp"));
    return vo;
}