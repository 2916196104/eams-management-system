
#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StudentClassHourRecordsQuery : public PageQuery
{
    DTO_INIT(StudentClassHourRecordsQuery, PageQuery);

    //¿Î³ÌÃû³Æ
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("file.field.ft"), true);
};

#include OATPP_CODEGEN_END(DTO)