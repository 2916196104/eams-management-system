#pragma once

#ifndef _PARENTDTO_H_
#define _PARENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	家长数据传输对象
 */
class ParentDTO : public oatpp::DTO {
  DTO_INIT(ParentDTO, DTO);
<<<<<<< Updated upstream

  // 姓名(必传)
  API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("parent.field.name"), true);
  // 手机号(必传)
  API_DTO_FIELD_REQUIRE(UInt64, phone, ZH_WORDS_GETTER("parent.field.phone"), true);
  // 注册时间(必传)
  API_DTO_FIELD_REQUIRE(String, regDate, ZH_WORDS_GETTER("parent.field.regDate"), true);
=======
  DTO_FIELD(String, name);
  DTO_FIELD(String, phone);
  // 注册时间
  DTO_FIELD(String, regDate);

>>>>>>> Stashed changes
};

#include OATPP_CODEGEN_END(DTO)
#endif // _PARENTDTO_H_
