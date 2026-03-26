#pragma once

#ifndef _CLASS_STUDENT_QUERY
#define _CLASS_STUDENT_QUERY
#include "../../../GlobalInclude.h"
//#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
// 类名从 ClassQuery 改为 ClassStudentQuery，继承关系不变
class ClassStudentQuery : public oatpp::DTO
{
    DTO_INIT(ClassStudentQuery, oatpp::DTO);  // 初始化宏同步替换类名
    DTO_FIELD(Int32, class_id);            // 字段名保持不变（与数据库字段对应）
    DTO_FIELD_INFO(class_id) {
        info->description = "";
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_QUERY