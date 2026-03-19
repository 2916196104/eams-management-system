#pragma once


#ifndef __GRADEMANAGE_H__
#define __GRADEMANAGE_H__
#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

//成绩管理控制器


class GradeManage : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GradeManage);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif