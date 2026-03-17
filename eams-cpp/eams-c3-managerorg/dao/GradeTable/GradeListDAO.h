#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeListDTO.h"
#include "domain/query/GradeTable/GradeListQuery.h"

class GradeListDAO
{
public:
    uint64_t count(
        const GradeListQuery::Wrapper& query,
        const PayloadDTO& payload
    );

    std::list<GradeListDTO::Wrapper> SelectPage(
        const GradeListQuery::Wrapper& query,
        const PayloadDTO& payload,
        uint64_t limit,
        uint64_t offset
    );
};