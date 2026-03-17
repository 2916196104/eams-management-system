#pragma once


#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "domain/GlobalInclude.h"
#include "ApiHelper.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/backhomework/backhomeworkDTO.h"
#include "domain/vo/backhomework/backhomeworkVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/*作业控制器*/

class Homework: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Homework);
public:		//定义接口
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("DelHomework.summary"),DelHomework,StringJsonVO::Wrapper,"Homework");

	API_HANDLER_ENDPOINT_AUTH(API_M_DEL,"/DelHomework",DelHomework,BODY_DTO(Backhomework::Wrapper, HomeworkIds),executeDelHomework(HomeworkIds));


private:	//定义接口执行函数
	StringJsonVO::Wrapper executeDelHomework(const Backhomework::Wrapper& backhomework);
};

#include OATPP_CODEGEN_END(ApiController)

#endif