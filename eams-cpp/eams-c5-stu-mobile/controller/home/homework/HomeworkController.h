#pragma once

#ifndef _HOMEWORK_CONTROLLER_H_
#define _HOMEWORK_CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
// 替换为Homework相关Query/DTO/VO头文件（路径按项目实际结构调整）
#include "domain/query/home/homework/HomeworkQuery.h"
#include "domain/dto/home/homework/HomeworkDTO.h"
#include "domain/vo/home/homework/HomeworkVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

// 控制器类名改为HomeworkController，继承ApiController不变
class HomeworkController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(HomeworkController); // 适配控制器类名
public:
    ENDPOINT_INFO(Homework) { // 端点名称改为Homework
        info->summary = ZH_WORDS_GETTER("Homework.query-all.summary"); // 国际化key适配作业业务
        API_DEF_ADD_AUTH(); // 保留鉴权逻辑，与项目规范一致
        // 替换为Homework分页VO，匹配作业表分页结果
        API_DEF_ADD_RSP_JSON(HomeworkPageJsonVO::Wrapper);
        API_DEF_ADD_RSP_JSON_WRAPPER(HomeworkPageJsonVO);
        API_DEF_ADD_PAGE_PARAMS(); // 保留分页参数（pageIndex/pageSize）

        // ========== 适配homework表的查询参数（核心：删除无关字段，新增表内字段） ==========
        // 1. 班级ID（homework表核心索引字段，必选查询条件）
        info->queryParams.add<Int64>("class_id").description = ZH_WORDS_GETTER("Homework.field.class_id");
        info->queryParams["class_id"].addExample("default", oatpp::Int64(1));

        // 2. 删除标记（homework表deleted字段，可选）
        info->queryParams.add<Boolean>("deleted").description = ZH_WORDS_GETTER("Homework.field.deleted");
        info->queryParams["deleted"].addExample("default", oatpp::Boolean(false));

        // 3. 创建人（homework表creator字段，可选，索引字段）
        info->queryParams.add<Int64>("creator").description = ZH_WORDS_GETTER("Homework.field.creator");
        info->queryParams["creator"].addExample("default", oatpp::Int64(10001));

        // 4. 组织ID（homework表org_id字段，可选，索引字段）
        info->queryParams.add<Int64>("org_id").description = ZH_WORDS_GETTER("Homework.field.org_id");
        info->queryParams["org_id"].addExample("default", oatpp::Int64(999));
    }

    // 端点路径适配作业业务，参数/鉴权逻辑保留
    ENDPOINT(API_M_GET, "/app/sCenter/homework/list", Homework, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        // 查询参数绑定为HomeworkQuery（适配作业表查询条件）
        API_HANDLER_QUERY_PARAM(query, HomeworkQuery, params);
        // 响应VO替换为HomeworkPageJsonVO
        API_HANDLER_RESP_VO(executeQueryHomework(query));
    }
private:
    // 私有方法名/参数/返回值适配Homework
    HomeworkPageJsonVO::Wrapper executeQueryHomework(const HomeworkQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORK_CONTROLLER_H_