#pragma once

#ifndef _LESSONDTO_H_
#define _LESSONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	鎺堣璁板綍鏁版嵁浼犺緭瀵硅薄
 */
class LessonDTO : public oatpp::DTO {
  DTO_INIT(LessonDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _LESSONDTO_H_
