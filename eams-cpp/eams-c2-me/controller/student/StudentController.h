#pragma once

#ifndef _STUDENT_CONTROLLER_
#define _STUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/Student/StudentQuery.h"
#include "domain/query/Student/IdQuery.h"
#include "domain/vo/Student/StudentVO.h"

// 生成API控制器代码宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/**
 * 学员控制器（整合查询/删除/切换功能）
 */
class StudentController : public oatpp::web::server::api::ApiController
{
    // 控制器访问入口声明
    API_ACCESS_DECLARE(StudentController);

public:
    // ========== 1. 查询学员列表 ==========
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "查询学员列表",
        queryAllUser,
        StudentQuery,
        StudentPageJsonVO::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/getStudentList",
        queryAllUser,
        StudentQuery,
        executeQueryAll(query)
    );

    // ========== 2. 删除学员 ==========
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "删除学员",
        removeStudent,
        IdQuery,
        JsonVO<oatpp::Any>::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/removeStudent",
        removeStudent,
        IdQuery,
        executeRemoveUser(query)
    );

    // ========== 3. 切换学员 ==========
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "切换学员",
        switchStudent,
        IdQuery,
        JsonVO<oatpp::Any>::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/switchStudent",
        switchStudent,
        IdQuery,
        executeSwitchStudent(query)
    );

private:
    // 执行查询学员列表
    StudentPageJsonVO::Wrapper executeQueryAll(const StudentQuery::Wrapper& query);
    // 执行删除学员
    JsonVO<oatpp::Any>::Wrapper executeRemoveUser(const IdQuery::Wrapper& query);
    // 执行切换学员
    JsonVO<oatpp::Any>::Wrapper executeSwitchStudent(const IdQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) // 结束代码生成

#endif // !_STUDENT_CONTROLLER_