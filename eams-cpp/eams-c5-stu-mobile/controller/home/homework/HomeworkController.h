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
#define API_TAG ZH_WORDS_GETTER("Homework.tag")


// 控制器类名改为HomeworkController，继承ApiController不变
class HomeworkController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(HomeworkController); // 适配控制器类名
public:
    ENDPOINT_INFO(Homework) { // 端点名称改为Homework
        info->summary = ZH_WORDS_GETTER("Homework.query-all.summary"); // 国际化key适配作业业务
        API_DEF_ADD_AUTH(); // 保留鉴权逻辑，与项目规范一致
        // 替换为Homework分页VO，匹配作业表分页结果
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_RSP_JSON(HomeworkPageJsonVO::Wrapper);
        API_DEF_ADD_RSP_JSON_WRAPPER(HomeworkPageJsonVO);
        API_DEF_ADD_PAGE_PARAMS(); // 保留分页参数（pageIndex/pageSize）

        // 查询参数
        API_DEF_ADD_QUERY_PARAMS(Int32, "student_id", ZH_WORDS_GETTER("Homework.field.student_id"), 1, true);


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