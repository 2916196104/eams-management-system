#pragma once

#ifndef _TIMEABLE_VO_
#define _TIMEABLE_VO_

#include "../../GlobalInclude.h"
// 替换为适配class_student表的DTO头文件
//#include "../../../dto/home/class/ClassStudentDTO.h"
#include"../../dto/schedule/GetTimeableDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// 单条数据返回VO：适配ClassStudentDTO

//class ClassStudentJsonVO : public JsonVO<ClassStudentDTO::Wrapper> {
//    DTO_INIT(ClassStudentJsonVO, JsonVO<ClassStudentDTO::Wrapper>)
//};
class GetTimeableJsonVO :public JsonVO<GetTimeableDTO::Wrapper>
{
    DTO_INIT(GetTimeableJsonVO, JsonVO<GetTimeableDTO::Wrapper>)
};

// 分页数据返回VO：适配ClassStudentPageDTO

//class ClassStudentPageJsonVO : public JsonVO<ClassStudentPageDTO::Wrapper> {
//    DTO_INIT(ClassStudentPageJsonVO, JsonVO<ClassStudentPageDTO::Wrapper>)
//};
class GetTimeablePageJsonVO : public JsonVO<GetTimeablePageDTO::Wrapper> {
    DTO_INIT(GetTimeablePageJsonVO, JsonVO<GetTimeablePageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_TIMEABLE_VO_