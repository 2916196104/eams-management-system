#pragma once
#ifndef _STUDENTVO_H_
#define _STUDENTVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/student/StudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个用户信息显示JsonVO对象，用于响应给客户端
 */
class UserJsonVO : public JsonVO<StudentDTO::Wrapper>
{
	DTO_INIT(UserJsonVO, JsonVO<StudentDTO::Wrapper>);
};

 

/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class StudentPageJsonVO : public JsonVO<StudentPageDTO::Wrapper>
{
	DTO_INIT(StudentPageJsonVO, JsonVO<StudentPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif  