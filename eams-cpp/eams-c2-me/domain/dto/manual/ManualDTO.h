#pragma once

#ifndef _MANUALDTO_H_
#define _MANUALDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	浣跨敤璇存槑鏁版嵁浼犺緭瀵硅薄
 */
class ManualDTO : public oatpp::DTO {
  DTO_INIT(ManualDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _MANUALDTO_H_
