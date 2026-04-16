#pragma once

#ifndef _STUDENTQUERY_H_
#define _STUDENTQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 学员列表分页查询参数（继承PageQuery自动包含pageIndex/pageSize）
 */
class StudentQuery : public PageQuery {
    DTO_INIT(StudentQuery, PageQuery);
};

#include OATPP_CODEGEN_END(DTO)
#endif