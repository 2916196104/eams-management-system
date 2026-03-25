#pragma once

#include "ApiHelper.h"
#include "Macros.h"
#ifndef _POSITIONDTO_H_
#define _POSITIONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
        职位数据传输对象
 */
class PositionDTO : public oatpp::DTO {
	DTO_INIT(PositionDTO, DTO);
	DTO_FIELD(Int32, id);               // 职位ID
	DTO_FIELD(String, name);             // 职位名称
	DTO_FIELD(String, description);      // 职位描述
};

/*
 *
 * 单个职位信息对象
 *
 * */
class PositionItemDTO : public oatpp::DTO {

  DTO_INIT(PositionItemDTO, DTO);

#define HC_AUTODTO(v, name, r)                                                 \
  API_DTO_FIELD_REQUIRE(v, name, ZH_WORDS_GETTER("position.field.#name#"), r);

  HC_AUTODTO(Int64, id, true);
  HC_AUTODTO(String, name, true);
#undef HC_AUTODTO
};

class PositionSaveRequestDTO : public oatpp::DTO {
  DTO_INIT(PositionSaveRequestDTO, DTO);

#define HC_AUTODTO(v, name, r)                                                 \
  API_DTO_FIELD_REQUIRE(v, name, ZH_WORDS_GETTER("position.field.#name#"), r);

  HC_AUTODTO(Int64, id, false);
  HC_AUTODTO(String, name, true);
#undef HC_AUTODTO
};

#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONDTO_H_
