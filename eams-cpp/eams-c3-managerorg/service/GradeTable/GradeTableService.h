#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/GradeTable/GradeTableDTO.h"
#include "domain/query/GradeTable/GradeTableQuery.h"
#include "oatpp/core/Types.hpp"

/* Delete List */
class DeleteListService
{
public:
    oatpp::Vector<oatpp::Int64> DeleteListQuery(
        const DeleteListQuery::Wrapper& query);
};

/* Save List */

class SaveListService
{
public:
    oatpp::Int64 SaveListQuery(const SaveListQuery::Wrapper& query);
};