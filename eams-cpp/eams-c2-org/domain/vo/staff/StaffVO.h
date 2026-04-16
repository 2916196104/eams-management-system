#pragma once
// domain/vo/staff/StaffVO.h
#ifndef STAFF_VO_H
#define STAFF_VO_H

#include"domain/GlobalInclude.h"
#include "domain/dto/staff/StaffDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 员工详情响应
class StaffDetailJsonVO : public JsonVO<StaffDetailDTO::Wrapper>
{
    DTO_INIT(StaffDetailJsonVO, JsonVO<StaffDetailDTO::Wrapper>);
};

// 员工删除响应
class DeleteResultJsonVO : public JsonVO<oatpp::String>
{
    DTO_INIT(DeleteResultJsonVO, JsonVO<oatpp::String>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_VO_H