#pragma once
// domain/query/staff/StaffBatchDeleteQuery.h
#ifndef STAFF_BATCH_DELETE_QUERY_H
#define STAFF_BATCH_DELETE_QUERY_H

#include"domain/GlobalInclude.h"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 批量删除员工的参数DTO（接收前端传的批量ID列表）
 */
class StaffBatchDeleteQuery : public DTO
{
    DTO_INIT(StaffBatchDeleteQuery, DTO);

    // 批量员工ID列表（核心字段）
    API_DTO_FIELD_DEFAULT(List<String>, staffIds, {});  // 默认空列表，避免空指针
    //API_DTO_FIELD_DEFAULT(List<UInt64>, staffIds, "staffIds");
};

#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_BATCH_DELETE_QUERY_H