#pragma once

#include"../../../dto/makabaka-dto/teacher/teacherDTO.h"
#include"../../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)

/*
定义一个教师信息显示JsonVo对象，用于响应客户端
*/
class TeacherJsonVO :public JsonVO<TeacherDTO::Wrapper> {
	DTO_INIT(TeacherJsonVO, JsonVO <TeacherDTO::Wrapper>);
};

/*
定义一个教师信息分页显示JsonVO对象，用于响应给客户端
*/
class TeacherPageJsonVO :public JsonVO<TeacherPageDTO::Wrapper> {
	DTO_INIT(TeacherPageJsonVO, JsonVO<TeacherPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)