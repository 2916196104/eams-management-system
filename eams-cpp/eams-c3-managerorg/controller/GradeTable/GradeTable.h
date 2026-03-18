#pragma once


#ifndef __GRADETABLE_H__
#define __GRADETABLE_H__
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

/*成绩单控制器*/


class GradeTable: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GradeTable);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif