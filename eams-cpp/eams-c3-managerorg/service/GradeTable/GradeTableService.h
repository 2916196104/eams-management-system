#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeTableDTO.h"
#include "domain/query/GradeTable/GradeTableQuery.h"

class RecordListService
{
public:
    RecordListDTO::Wrapper QueryRecordList(
        const RecordListQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};