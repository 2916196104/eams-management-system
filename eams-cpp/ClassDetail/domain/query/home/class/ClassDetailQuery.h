#pragma once

#ifndef _CLASS_DETAIL_QUERY_
#define _CLASS_DETAIL_QUERY
#include "../../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class ClassDetailQuery : public PageQuery
{
    DTO_INIT(ClassDetailQuery, PageQuery);  // 初始化宏同步替换类名
    DTO_FIELD(Int32, student_id);            // 字段名保持不变（与数据库字段对应）
    DTO_FIELD_INFO(student_id) {
        info->description = "";
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CLASS_STUDENT_QUERY