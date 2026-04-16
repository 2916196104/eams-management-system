#pragma once

#ifndef _IDQUERY_H_
#define _IDQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 根据ID查询参数
 */
class IdQuery : public  oatpp::DTO {
    DTO_INIT(IdQuery, oatpp::DTO);
    // 必传ID字段
    API_DTO_FIELD(String, id, "id", true, String(""));
};

#include OATPP_CODEGEN_END(DTO)

#endif
