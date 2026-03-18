#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeListDTO.h"
#include "domain/query/GradeTable/GradeListQuery.h"

class RecordListDAO
{
public:
    uint64_t count(
        const RecordListQuery::Wrapper& query,
        const PayloadDTO& payload
    );

    std::list<RecordListDTO::Wrapper> SelectPage(
        const RecordListQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};