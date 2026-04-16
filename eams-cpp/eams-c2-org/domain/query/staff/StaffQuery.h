#pragma once
// domain/query/staff/StaffQuery.h
#ifndef STAFF_QUERY_H
#define STAFF_QUERY_H

#include"domain/GlobalInclude.h"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/data/mapping/type/Object.hpp"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

class StaffQuery : public DTO
{
    DTO_INIT(StaffQuery, DTO);

    API_DTO_FIELD_DEFAULT(String, id, "id");
    //API_DTO_FIELD_DEFAULT(List<UInt64>, staffIds, "staffIds");
};

#include OATPP_CODEGEN_END(DTO)

#endif // STAFF_QUERY_H