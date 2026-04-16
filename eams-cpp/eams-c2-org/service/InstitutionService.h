#pragma once
#include "../domain/dto/institution/InstitutionDTO.h"
#include "oatpp/core/Types.hpp"

class InstitutionService {
public:
    oatpp::List<oatpp::Object<InstitutionDTO>> getTree();
    oatpp::String saveInstitution(const oatpp::Object<InstitutionDTO>& dto, const oatpp::String& username);
};