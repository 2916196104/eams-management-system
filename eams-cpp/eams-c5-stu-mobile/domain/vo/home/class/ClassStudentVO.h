#pragma once

#ifndef _CLASS_STUDENT_VO_
#define _CLASS_STUDENT_VO_

#include "../../../GlobalInclude.h"
// 替换为适配class_student表的DTO头文件
#include "../../../dto/home/class/ClassStudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 单条数据返回VO：适配ClassStudentDTO
class ClassStudentJsonVO : public JsonVO<ClassStudentDTO::Wrapper> {
    DTO_INIT(ClassStudentJsonVO, JsonVO<ClassStudentDTO::Wrapper>)
};

// 分页数据返回VO：适配ClassStudentPageDTO
class ClassStudentPageJsonVO : public JsonVO<ClassStudentPageDTO::Wrapper> {
    DTO_INIT(ClassStudentPageJsonVO, JsonVO<ClassStudentPageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_VO_