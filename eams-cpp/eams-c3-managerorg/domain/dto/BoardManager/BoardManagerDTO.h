#ifndef _BOARDMANAGERDTO_H_
#define _BOARDMANAGERDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*公共管理DTO类*/


class BoardManager : public oatpp::DTO
{
	DTO_INIT(BoardManager, DTO)
};

#include OATPP_CODEGEN_END(DTO)

#endif