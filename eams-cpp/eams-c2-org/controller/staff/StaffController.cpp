// controller/staff/StaffController.cpp
#include "stdafx.h"
#include "StaffController.h"
// 确保引入必要的头文件
#include "oatpp/core/Types.hpp"
#include "service/staff/StaffService.h"
#include <list>
#include <string>

// 查询员工详情
StaffDetailJsonVO::Wrapper StaffController::execGetStaffDetail(const String& id)
{
    StaffService us;
    auto jvo = StaffDetailJsonVO::createShared();
    auto data = us.getStaffDetail(id);
    if (data) {
        jvo->success(data);
    }
    else {
        jvo->fail({});
    }
    return jvo;
}

// 批量删除员工
DeleteResultJsonVO::Wrapper StaffController::execRemoveStaffByIds(const StaffBatchDeleteQuery::Wrapper& deleteQuery)
{
    auto jvo = DeleteResultJsonVO::createShared();

    // 1. 提取ID列表并校验
    auto ids = deleteQuery->staffIds;  // 从DTO中提取批量ID列表
    if (ids->empty()) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 2. 调用Service层执行删除
    StaffService staffService;
    bool deleteSuccess = staffService.batchDeleteStaff(ids);
    // 执行数据删除
    if (deleteSuccess) {
        jvo->success(oatpp::String(std::to_string(ids->size())));
    }
    else {
        jvo->fail(nullptr);
    }

    return jvo;
}

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



// 头像修改逻辑实现（和executeQueryTest格式一致）
StringJsonVO::Wrapper StaffController::executeModifyAvatar(const AvatarUploadDTO::Wrapper& dto) {
	// 创建响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("modifyAvatar.resp"));
	return vo;
}

StringJsonVO::Wrapper StaffController::executegetDutyRecord(const DutyRecordQueryDTO::Wrapper& query) {
  //创建一个相应结果
  auto vo = StringJsonVO::createShared();
  vo->success(ZH_WORDS_GETTER("getDutyRecord.resp"));
  return vo;
}
ListJsonVO<String>::Wrapper StaffController::execSetRole(const List<String>& ids, const PayloadDTO& payload)
{
	return {};
}

ListJsonVO<String>::Wrapper StaffController::execSetJob(const List<String>& ids, const PayloadDTO& payload)
{
	return {};
}

ListJsonVO<String>::Wrapper StaffController::execSetInstitution(const List<String>& ids, const PayloadDTO& payload)
{
	return {};
}
StringJsonVO::Wrapper StaffController::executeStaffPassWordChange(const StaffChangePasswordDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	//serviceʵ���޸�����
	jvo->success("");
	return jvo;
}

StringJsonVO::Wrapper StaffController::executeStaffListExport(const StaffExportQueryDto::Wrapper& exportQuery)
{
	auto jvo = StringJsonVO::createShared();
	jvo->success("");
	return jvo;
}
