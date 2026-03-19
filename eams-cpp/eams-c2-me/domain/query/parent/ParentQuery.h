#pragma once

#ifndef _PARENTQUERY_H_
#define _PARENTQUERY_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	家长信息查询类
 */
class ParentQuery : public oatpp::DTO { // query本质上就是一种DTO
  // 定义初始化
  DTO_INIT(ParentDTO, DTO);

  // 家长姓名
  API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("parent.field.name"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // _PARENTQUERY_H_
