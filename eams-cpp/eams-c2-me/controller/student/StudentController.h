#pragma once

#ifndef _STUDENT_CONTROLLER_ 
#define _STUDENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/vo/Student/StudentVO.h"
// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 学员控制器
 */
class StudentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(StudentController);
  // 3 定义接口
public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "Select Users List",              // 接口标题
        queryAllUser,               // 端点函数名
        UserQuery,                  // Query类型（自动生成参数文档）
        StudentPageJsonVO::Wrapper,    // 响应类型
        API_TAG                     // 标签
    );
    // 定义接口端点（实际处理逻辑）
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,                  // HTTP方法：GET
        "/me/getStudentList",          // 路径
        queryAllUser,               // 函数名
        UserQuery,                  // Query类型（自动解析参数）
        executeQueryAll(query)      // 调用执行方法
    );

private: // 定义接口执行函数
    StudentPageJsonVO::Wrapper executeQueryAll(const UserQuery::Wrapper& query);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
