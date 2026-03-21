#pragma once
#ifndef _PARENT_QUERY_
#define _PARENT_QUERY_

#include "../../GlobalInclude.h"
#include "../../dto/parent/ParentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户信息的数据传输模型
 */
class ParentQuery : public oatpp::DTO
{
  // 定义初始化
  DTO_INIT(ParentQuery, DTO);
  // 昵称
  API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("parent.field.name"));
  // 电话号
  API_DTO_FIELD_DEFAULT(UInt64, phone, ZH_WORDS_GETTER("parent.field.phone"));
  // 密码
  API_DTO_FIELD_DEFAULT(String, password, ZH_WORDS_GETTER("parent.field.password"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PARENT_QUERY_
