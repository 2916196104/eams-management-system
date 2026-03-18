#pragma once


#ifndef __SENDHOMEWORK_H__
#define __SENDHOMEWORK_H__

#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(ApiController)


//作业提交控制器

class SendHomework: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SendHomework);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif