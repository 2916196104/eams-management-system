#pragma once

#ifndef _CLASS_STUDENT_VO_
#define _CLASS_STUDENT_VO_

#include "../../../GlobalInclude.h"
// 替换为适配class_student表的DTO头文件
#include "../../../dto/home/class/ClassStudentDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 列表VO，专门用于返回ClassStudentDTO列表
class ClassStudentJsonVO : public JsonVO<oatpp::List<ClassStudentDTO::Wrapper>> {
    DTO_INIT(ClassStudentJsonVO, JsonVO<oatpp::List<ClassStudentDTO::Wrapper>>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_VO_