#pragma once

#ifndef __SENDHOMEWORK_H__
#define __SENDHOMEWORK_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/backhomework/backhomeworkDTO.h"
#include "domain/query/backhomework/backhomeworkQuery.h"
#include "domain/vo/backhomework/backhomeworkVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define SENDHOMEWORK_API_TAG ZH_WORDS_GETTER("SendHomework.homeworkSend")

//作业提交控制器
class SendHomework : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SendHomework);
public:		//定义接口
	// 获取作业提交列表（条件+分页）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("GetHomeworkList.summary"), GetHomeworkList, BackhomeworkQuery, oatpp::List<BackhomeworkVO::Wrapper>, SENDHOMEWORK_API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "c3-org/backhomework/get-sendhomework-list", GetHomeworkList, BackhomeworkQuery, executeGetHomeworkList(query));
	
	// 点评作业
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("ReviewHomework.summary"), ReviewHomework, StringJsonVO::Wrapper, SENDHOMEWORK_API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "c3-org/backhomework/review-homework", ReviewHomework, BODY_DTO(ReviewHomework::Wrapper, req), executeReviewHomework(req));

private:	//定义接口执行函数
	//获取作业提交列表（条件+分页）
	oatpp::List<BackhomeworkVO::Wrapper> executeGetHomeworkList(const BackhomeworkQuery::Wrapper& query);
	//点评作业
	StringJsonVO::Wrapper executeReviewHomework(const ReviewHomework::Wrapper& req);
};

#include OATPP_CODEGEN_END(ApiController)

#endif