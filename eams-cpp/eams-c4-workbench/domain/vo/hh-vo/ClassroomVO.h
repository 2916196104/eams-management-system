#pragma once
#ifndef _CLASSROOM_VO_
#define _CLASSROOM_VO_

#include "../../GlobalInclude.h"
#include "domain/dto/hh-dto/ClassroomDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 教室数据分页显示JsonVO，用于响应给客户端的Json对象
class ClassroomPageJsonVO : public JsonVO<ClassroomPageDTO::Wrapper> {
	DTO_INIT(ClassroomPageJsonVO, JsonVO<ClassroomPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
