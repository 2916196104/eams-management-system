#pragma once


#ifndef __STUJUDGETEA_H__
#define __STUJUDGETEA_H__

#include OATPP_CODEGEN_BEGIN(ApiController)


/*学评教控制器*/


class StuJudgeTea: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(StuJudgeTea);
public:		//定义接口

private:	//定义接口执行函数

};

#include OATPP_CODEGEN_END(ApiController)

#endif