#pragma once


#ifndef __RECORD_COMMENT_H__
#define __RECORD_COMMENT_H__

#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(ApiController)


class Record_comment : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_comment);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif