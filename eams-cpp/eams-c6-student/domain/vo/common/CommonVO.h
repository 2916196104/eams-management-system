#pragma once
#ifndef __COMMON_VO_H__
#define __COMMON_VO_H__ 
#include"../../GlobalInclude.h"
#include"../../dto/common/CommonDTO.h"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)
class CourseCountJsonVO : public JsonVO<CourseCountDTO::Wrapper> {
public:
    DTO_INIT(CourseCountJsonVO, JsonVO<CourseCountDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif