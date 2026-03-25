#pragma once
// controller/staff/StaffController.h
#ifndef STAFF_CONTROLLER_H
#define STAFF_CONTROLLER_H

#include "domain/vo/BaseJsonVO.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include"domain/query/staff/StaffQuery.h"
#include "domain/vo/staff/StaffVO.h"
#include "domain/query/staff/StaffBatchDeleteQuery.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController) 

#define API_TAG ZH_WORDS_GETTER("staff.tag")

class StaffController : public oatpp::web::server::api::ApiController
{
    // 添加访问定义
    API_ACCESS_DECLARE(StaffController);

public:
    // ==================== 根据ID查询员工详细信息 ====================
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("staff.query-one.summary"),
        getStaffDetail,
        StaffDetailJsonVO::Wrapper,
        API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("field.id"), "", true);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,
        "org/staff/detail",
        getStaffDetail,
        QUERY(String, id),
        execGetStaffDetail(id)
    );

    // ==================== 根据ID批量删除员工 ====================
    // 使用 DeleteResultJsonVO 返回删除结果
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("staff.delete-staff-summary"),
        removeStaffByIds,
        DeleteResultJsonVO::Wrapper,  // 使用专门的删除结果VO
        API_TAG
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_DEL,
        "org/staff/remove",
        removeStaffByIds,
        BODY_DTO(StaffBatchDeleteQuery::Wrapper, deleteQuery),  // 使用完整类型
        execRemoveStaffByIds(deleteQuery)
    );

private:
    StaffDetailJsonVO::Wrapper execGetStaffDetail(const String& id);
    DeleteResultJsonVO::Wrapper execRemoveStaffByIds(const StaffBatchDeleteQuery::Wrapper& deleteQuery);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // STAFF_CONTROLLER_H