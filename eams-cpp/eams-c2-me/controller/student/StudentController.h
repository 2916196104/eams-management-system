#pragma once

#ifndef _STUDENT_CONTROLLER_ 
#define _STUDENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/query/Student/IdQuery.h"


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
    
    //接口文档
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "删除用户",             
        removeStudent,         
        IdQuery,                  
        JsonVO<oatpp::Any>::Wrapper, 
        API_TAG                   
    );
    //返回值修改为JsonVO(oatpp::Any::Wrapper)
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/removeStudent",
        removeStudent,
        IdQuery,  
        executeRemoveUser(query)
    );
    //因为是单个id使用IdQuery更符合规范
   
private: // 定义接口执行函数
    JsonVO<oatpp::Any>::Wrapper executeRemoveUser(const IdQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
