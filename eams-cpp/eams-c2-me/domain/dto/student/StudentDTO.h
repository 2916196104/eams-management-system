#pragma once

#ifndef _STUDENTDTO_H_
#define _STUDENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	学生数据传输对象
 */
class StudentDTO : public oatpp::DTO {
  DTO_INIT(StudentDTO, DTO);
};

/**
 * 定义一个用户信息分页传输对象
 */
class StudentPageDTO : public PageDTO<StudentDTO::Wrapper>
{
	DTO_INIT(StudentPageDTO, PageDTO<StudentDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _STUDENTDTO_H_
