#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 家长控制器
 */
class ParentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(ParentController);
	// 3 定义接口
public:

private: // 定义接口执行函数
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_














