// controller/staff/StaffController.cpp
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