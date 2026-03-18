#pragma once

#ifndef _TIMEABLE_QUERY
#define _TIMEABLE_QUERY
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)
// 类名从 ClassQuery 改为 ClassStudentQuery，继承关系不变
class ScheduleTimeableQuery : public PageQuery
{
    DTO_INIT(ScheduleTimeableQuery, PageQuery);  // 初始化宏同步替换类名
    DTO_FIELD(Int32, student_id);            // 字段名保持不变（与数据库字段对应）
    DTO_FIELD_INFO(student_id) {
        info->description = "";
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_TIMEABLE_QUERY