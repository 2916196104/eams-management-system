#pragma once
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/Student_Class_Hour Records/StudentClassHourRecordsVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("workbench.tag")

class ClassHourRecordsController : public oatpp::web::server::api::ApiController
{
    // 接口访问入口声明宏
    API_ACCESS_DECLARE(ClassHourRecordsController);
public: // 定义接口
	// 3.1 定义获取学员课时记录接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("workbench.hour.summary"), queryNamePage, StudentClassHourRecordsPageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("workbench.field.name"), "name", true);
	);
	// 3.2 定义获取学员课程进度接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4-workbench/StudentClassHourRecords", queryNamePage, QUERY(String, name), execQueryNamePage(name));

private: // 定义接口执行函数
	//3.3 定义获取学员课程进度接口执行函数
	StudentClassHourRecordsPageJsonVO::Wrapper execQueryNamePage(const oatpp::String& name);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
