#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class DeletePositionRequestDTO : public oatpp::DTO {
    DTO_INIT(DeletePositionRequestDTO, DTO)
        DTO_FIELD(Vector<Int32>, ids);
    DTO_FIELD_INFO(ids) {
        info->description = ZH_WORDS_GETTER("position.delete.ids.description");
        info->required = true;
    }
};

#include OATPP_CODEGEN_END(DTO)