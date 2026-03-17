#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeListDTO.h"
#include "domain/query/GradeTable/GradeListQuery.h"

class GradeListService
{
public:
    GradeListPageDTO::Wrapper QueryGradeList(
        const GradeListQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};