#pragma once
#ifndef _INSTITUTION_DTO_
#define _INSTITUTION_DTO_

#include "../../GlobalInclude.h"
#include "../../lib-oatpp/include/ApiHelper.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class InstitutionDTO : public oatpp::DTO {
    DTO_INIT(InstitutionDTO, DTO);

    API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("institution.field.id"));
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("institution.field.name"));
    API_DTO_FIELD_DEFAULT(String, parentId, ZH_WORDS_GETTER("institution.field.parentId"));
    API_DTO_FIELD_DEFAULT(List<Object<InstitutionDTO>>, children, ZH_WORDS_GETTER("institution.field.children"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // _INSTITUTION_DTO_