#pragma once


#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)


/*作业控制器*/

class Homework: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Homework);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif