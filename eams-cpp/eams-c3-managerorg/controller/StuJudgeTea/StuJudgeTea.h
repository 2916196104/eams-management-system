#pragma once
#ifndef __STU_JUDGE_TEA_H__  // 规范：全大写+下划线，修正原小写宏
#define __STU_JUDGE_TEA_H__

// 补充：通用VO基类（必须引入）
#include "domain/vo/BaseJsonVO.h"
#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"

// 补充：引入对应VO/Query/DTO（学评教专属）
#include "../../domain/vo/StuJudgeTea/StuJudgeTeaVO.h"       // 学评教分页VO
#include "../../domain/query/StuJudgeTea/StuJudgeTeaQuery.h" // 学评教查询参数
#include "../../domain/dto/StuJudgeTea/StuJudgeTeaDTO.h"     // 学评教DTO

#include OATPP_CODEGEN_BEGIN(ApiController)

// 补充：定义API标签（国际化配置）
#define API_TAG ZH_WORDS_GETTER("StuJudgeTea.tags")

/*学评教控制器（管理端仅查询场景）*/
class StuJudgeTea : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(StuJudgeTea);

public:     // 定义接口（仅查询，无增删改）
    // 1. 定义获取学评教列表接口描述
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("StuJudgeTea.query"),  // 接口标题（国际化）
        queryPageStuJudgeTea,                                 // 端点函数名
        StuJudgeTeaQuery,                                     // 查询参数类型
        StuJudgeTeaPageJsonVO::Wrapper,                       // 响应VO类型
        API_TAG                                              // 接口标签
    );

    // 2. 定义获取学评教列表接口处理
    API_HANDLER_ENDPOINT_OPTION_AUTH(
        API_M_GET,                                           // 请求方式（GET）
        "c3-org/StuJudgeTea/get-stu-review-list",                       // 接口路径（模块专属）
        queryPageStuJudgeTea,                                 // 端点函数名
        QUERIES(QueryParams, queryParams),                   // 参数解析：查询参数
        // 处理逻辑
        API_HANDLER_QUERY_PARAM(query, StuJudgeTeaQuery, queryParams);
    API_HANDLER_RESP_VO(execQueryPageStuJudgeTea(query));
        );

private:    // 定义接口执行函数
    // 声明获取学评教列表执行函数
    StuJudgeTeaPageJsonVO::Wrapper execQueryPageStuJudgeTea(const StuJudgeTeaQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG
#endif 