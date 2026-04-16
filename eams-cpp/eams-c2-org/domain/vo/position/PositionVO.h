#include "ApiHelper.h"
#include "Macros.h"
#include "domain/vo/JsonVO.h"
#include "oatpp/core/Types.hpp"
#ifndef _POSITIONVO_H_
#define _POSITIONVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/position/PositionDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
 *
 *  所有职位传输对象
 *
 * */

class ALLPositionsVO : public JsonVO<oatpp::Vector<PositionItemDTO::Wrapper>> {

  DTO_INIT(ALLPositionsVO, JsonVO<Vector<PositionItemDTO::Wrapper>>);
};

/*
        职位列表传输对象
 */
class PositionListVO : public JsonVO<oatpp::Vector<PositionItemDTO::Wrapper>> {
  DTO_INIT(PositionListVO, JsonVO<Vector<PositionItemDTO::Wrapper>>);

  API_DTO_FIELD_REQUIRE(Int32, total, ZH_WORDS_GETTER("position.field.total"),
                        true);
  API_DTO_FIELD_REQUIRE(Int32, page, ZH_WORDS_GETTER("position.field.page"),
                        true);
  API_DTO_FIELD_REQUIRE(Int32, limit, ZH_WORDS_GETTER("position.field.limit"),
                        true);
  API_DTO_FIELD_REQUIRE(Int32, totalPages,
                        ZH_WORDS_GETTER("position.field.totalPages"), true);
};
#include OATPP_CODEGEN_END(DTO)
#endif // _POSITIONVO_H_
