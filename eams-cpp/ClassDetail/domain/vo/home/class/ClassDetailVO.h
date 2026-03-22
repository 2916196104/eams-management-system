#pragma once

#ifndef _CLASS_STUDENT_VO_
#define _CLASS_STUDENT_VO_

#include "../../../GlobalInclude.h"
// 替换为适配class表的DTO头文件
#include "../../../dto/home/class/ClassDetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 单条数据返回VO：适配ClassDetailDTO
class ClassDetailJsonVO : public JsonVO<ClassDetailDTO::Wrapper> {
    DTO_INIT(ClassDetailJsonVO, JsonVO<ClassDetailDTO::Wrapper>)
};

// 分页数据返回VO：适配ClassStudentPageDTO
class ClassDetailPageJsonVO : public JsonVO<ClassDetailPageDTO::Wrapper> {
    DTO_INIT(ClassDetailPageJsonVO, JsonVO<ClassDetailPageDTO::Wrapper>)
};



#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_VO_
