#pragma once

#ifndef _LESSONDTO_H_
#define _LESSONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	授课记录数据传输对象
 */
class LessonDTO : public oatpp::DTO {
  DTO_INIT(LessonDTO, DTO);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _LESSONDTO_H_
