#pragma once

#include"../../../dto/makabaka-dto/class/classDTO.h"
#include"../../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个班级信息显示JsonVo对象，用于响应客户端
*/
class ClassJsonVO :public JsonVO<ClassDTO::Wrapper> {
	DTO_INIT(ClassJsonVO, JsonVO <ClassDTO::Wrapper>);
};

/*
定义一个班级信息分页显示JsonVO对象，用于响应给客户端
*/
class ClassPageJsonVO :public JsonVO<ClassPageDTO::Wrapper> {
	DTO_INIT(ClassPageJsonVO, JsonVO<ClassPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)