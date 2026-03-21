#pragma once
#ifndef CLASSDETAILVO_H_
#define CLASSDETAILVO_H_
#include"../../GlobalInclude.h"
#include"../../dto/classDTO/classDetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ClassJsonVO : public ClassDTO
{
	DTO_INIT(ClassJsonVO,JsonVO<ClassDTO::Wrapper>);
};

/*
* 获取班级详情，响应客户端的Json对象
*/
class ClassDetailJsonVO : public JsonVO<ClassDetailDTO::Wrapper>
{
	DTO_INIT(ClassDetailJsonVO, JsonVO<ClassDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !CLASSDETAILVO_H_
