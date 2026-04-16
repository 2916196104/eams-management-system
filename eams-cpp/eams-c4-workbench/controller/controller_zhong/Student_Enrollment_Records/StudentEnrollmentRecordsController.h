#pragma once

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/Student_Enrollment_Records/StudentEnrollmentRecordsVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("workbench.tag")

class EnrollmentRecordsController : public oatpp::web::server::api::ApiController
{
    // 接口访问入口声明宏
    API_ACCESS_DECLARE(EnrollmentRecordsController);
public: // 定义接口
	// 3.1 定义获取学员报名记录接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("workbench.enrollment.summary"), queryNamePage, StudentEnrollmentRecordsPageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("workbench.field.name"), "name", true);
	);
	// 3.2 定义获取学员课程进度接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c4-workbench/StudentEnrollmentRecords", queryNamePage, QUERY(String, name), execQueryNamePage(name));

private: // 定义接口执行函数
	//3.3 定义获取学员报名记录接口执行函数
	StudentEnrollmentRecordsPageJsonVO::Wrapper execQueryNamePage(const oatpp::String& name);
};

#include OATPP_CODEGEN_END(ApiController)

