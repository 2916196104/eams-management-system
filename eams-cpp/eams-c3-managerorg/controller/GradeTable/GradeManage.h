#pragma once


#ifndef __GRADEMANAGE_H__
#define __GRADEMANAGE_H__
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

/*成绩管理控制器*/


class GradeManage: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GradeManage);
public:		//定义接口

	//// 3.1 定义导入接口描述
	//API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("sample.import.summary"), importGrade, SampleImportDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	//// 3.2 定义导入接口处理
	//API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c3/org/Grade", importGrade, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportGrade(request, authObject->getPayload()));



private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif