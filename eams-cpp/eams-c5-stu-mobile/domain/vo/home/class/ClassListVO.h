#pragma once
#pragma once

#ifndef _CLASSLISTVO_H_
#define _CLASSLISTVO_H_

#include "../../../GlobalInclude.h"
// 替换为适配class表的DTO头文件
#include "../../../dto/home/class/ClassListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 单条数据返回VO：适配ClassDetailDTO
class ClassListJsonVO : public JsonVO<ClassListDTO::Wrapper> {
    DTO_INIT(ClassListJsonVO, JsonVO<ClassListDTO::Wrapper>)
};

// 分页数据返回VO：适配ClassStudentPageDTO
class ClassListPageJsonVO : public JsonVO<ClassListPageDTO::Wrapper> {
    DTO_INIT(ClassListPageJsonVO, JsonVO<ClassListPageDTO::Wrapper>)
};



#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_VO_
