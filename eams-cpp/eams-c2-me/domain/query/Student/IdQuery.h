#pragma once

#ifndef _IDQUERY_H_
#define _IDQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个查询用户id
 */
class IdQuery : public  oatpp::DTO {
	DTO_INIT(IdQuery, oatpp::DTO);
	//和DTO保持一致
	API_DTO_FIELD(Int64, id, "id", true, Int64());

};

#include OATPP_CODEGEN_END(DTO)


#endif
