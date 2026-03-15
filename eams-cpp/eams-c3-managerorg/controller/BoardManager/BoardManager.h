#pragma once


#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)

/*公告管理控制器*/


class BoardManager: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	//API_ACCESS_DECLARE(BoardManager);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif