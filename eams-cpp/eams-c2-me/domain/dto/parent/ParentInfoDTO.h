#pragma once

#ifndef _PARENTDTO_H_
#define _PARENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
  家长数据传输对象
 */
class ParentInfoDTO : public oatpp::DTO {
  DTO_INIT(ParentInfoDTO, DTO);
	DTO_FIELD(UInt64, id);
  DTO_FIELD(String, name);
  DTO_FIELD(String, phone);
  // 注册时间
  DTO_FIELD(String, datetime);

};

#include OATPP_CODEGEN_END(DTO)
#endif // _PARENTDTO_H_