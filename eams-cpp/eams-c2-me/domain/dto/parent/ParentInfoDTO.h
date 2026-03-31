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
  DTO_FIELD(String, name);
  DTO_FIELD(String, phone);
  // 注册时间
  DTO_FIELD(String, regDate);

};

#include OATPP_CODEGEN_END(DTO)
#endif // _PARENTDTO_H_
