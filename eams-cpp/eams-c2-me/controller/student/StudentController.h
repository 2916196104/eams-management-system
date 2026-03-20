#pragma once

#ifndef _STUDENT_CONTROLLER_ 
#define _STUDENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"

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
	//切换用户
	API_DEF_ENDPOINT_INFO_AUTH("Switch Student", switchStudent, StringJsonVO::Wrapper,
		API_TAG);
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/me/switchStudent",
		switchStudent,
		QUERY(Int64,id),
		executeSwitchStudent(id)
	)

private: // 定义接口执行函数
	JsonVO<oatpp::Any>::Wrapper executeSwitchStudent(int64_t id);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
