#pragma once

#ifndef _STUDENT_CONTROLLER_ 
#define _STUDENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "./domain/vo/GradeJsonVO.h"
#include "./domain/query/GradeQuery.h"
#include "./domain/vo/PointPageJsonVO.h"
#include "./domain/query/PointQuery.h"
#include "domain/query/Student/IdQuery.h"


#include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/vo/Student/StudentVO.h"
// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("student.tag")

/*
 * 学员控制器
 */
class StudentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(StudentController);
  // 3 定义接口
public:
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("student.query.grade"), queryGrade, GradeQuery, GradePageJsonVO::Wrapper, API_TAG);
	// 定义查询所有用户信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/me/getOptionalGrade", queryGrade, GradeQuery, executeQueryGrade(query));
private: // 定义接口执行函数
	
	GradePageJsonVO::Wrapper executeQueryGrade(const GradeQuery::Wrapper& query);

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("student.query.point"), queryPoint, PointQuery, PointPageJsonVO::Wrapper, API_TAG);
	// 定义查询所有用户信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/me/getMyPoint", queryPoint, PointQuery, executeQueryPoint(query));
    
    //接口文档
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("student.removeStudent"),
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
	PointPageJsonVO::Wrapper executeQueryPoint(const PointQuery::Wrapper& query);
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("student.getStudentList"),// 接口标题
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

	//切换用户
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("student.switchStudent"), switchStudent, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(
	  API_M_GET,
	  "/me/switchStudent",
	  switchStudent,
	  QUERY(Int64, id),
	  executeSwitchStudent(id)
	);

private: // 定义接口执行函数
	JsonVO<oatpp::Any>::Wrapper executeSwitchStudent(int64_t id);

    JsonVO<oatpp::Any>::Wrapper executeRemoveUser(const IdQuery::Wrapper& query);
    StudentPageJsonVO::Wrapper executeQueryAll(const UserQuery::Wrapper& query);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
