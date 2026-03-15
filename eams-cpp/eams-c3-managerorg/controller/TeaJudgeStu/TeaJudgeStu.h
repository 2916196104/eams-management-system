#pragma once


#ifndef __TeaJudgeStu_H__
#define __TeaJudgeStu_H__
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)


/*教评学控制器*/


class TeaJudgeStu : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(TeaJudgeStu);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif