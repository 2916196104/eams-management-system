#pragma once
#ifndef __GRADE_TABLE_H__
#define __GRADE_TABLE_H__

#include "domain/vo/BaseJsonVO.h"
#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"

// 引入成绩单相关VO、查询参数、数据传输对象
#include "../../domain/vo/GradeTable/GradeTableVO.h"
#include "../../domain/query/GradeTable/GradeTableQuery.h"
#include "../../domain/dto/GradeTable/GradeTableDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * 成绩单控制器
 * 负责成绩单相关接口的定义与处理
 */
class GradeTable : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(GradeTable);

public:
    /**
     * 分页查询成绩单列表接口描述
     * 接口用途：根据筛选条件分页查询成绩单数据
     */
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("GradeTable.query"),
        queryPageGradeTable,
        GradeTableQuery,
        GradeTablePageJsonVO::Wrapper,
        ZH_WORDS_GETTER("GradeTable.tags")
    );

    /**
     * 分页查询成绩单列表接口处理
     * 请求方式：GET
     * 请求路径：/c3/org/GradeTable/by-item
     */
    API_HANDLER_ENDPOINT_OPTION_AUTH(
        API_M_GET,
        "/c3/org/GradeTable/by-item",
        queryPageGradeTable,
        QUERIES(QueryParams, queryParams),
        API_HANDLER_QUERY_PARAM(query, GradeTableQuery, queryParams);
    API_HANDLER_RESP_VO(execQueryPageGradeTable(query));
        );

private:
    /**
     * 分页查询成绩单列表执行函数
     * @param query 查询参数对象
     * @return 分页查询结果VO
     */
    GradeTablePageJsonVO::Wrapper execQueryPageGradeTable(const GradeTableQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !__GRADE_TABLE_H__