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
private: // 定义接口执行函数
	PointPageJsonVO::Wrapper executeQueryPoint(const PointQuery::Wrapper& query);

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

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
