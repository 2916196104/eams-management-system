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


/*作业提交控制器*/

class SendHomework: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(SendHomework);
public:		//定义接口
//----------------------获取作业提交列表（条件+分页）------------------------------
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("GetHomeworkList.summary"),
        GetHomeworkList,
        BackhomeworkQuery,
        oatpp::List<BackhomeworkVO::Wrapper>,
        "SendHomework"
    );

    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/GetHomeworkList",
        GetHomeworkList,
        BackhomeworkQuery,
        executeGetHomeworkList(query)
    );

//----------------------点评作业------------------------------
    //获取作业详情（用于点评前查看）
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("GetHomeworkDetail.summary"),
        GetHomeworkDetail,
        BackhomeworkVO::Wrapper,
        "SendHomework",
        API_DEF_ADD_QUERY_PARAMS(oatpp::UInt64, "id", ZH_WORDS_GETTER("field.id"), 1, true);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,
        "/GetHomeworkDetail",
        GetHomeworkDetail,
        QUERY(UInt64, id),
        executeGetHomeworkDetail(id)
    );

    //提交点评
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("SubmitReview.summary"),
        SubmitReview,
        StringJsonVO::Wrapper,
        "SendHomework"
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/SubmitReview",
        SubmitReview,
        BODY_DTO(ReviewHomeworkDTO::Wrapper, req),
        executeSubmitReview(req)
    );


private:	//定义接口执行函数
    //----------------------获取作业提交列表（条件+分页）------------------------------
    oatpp::List<BackhomeworkVO::Wrapper> executeGetHomeworkList(const BackhomeworkQuery::Wrapper& query);
    StringJsonVO::Wrapper executeDelHomework(const BackhomeworkQuery::Wrapper& req);

    //----------------------点评作业------------------------------
    BackhomeworkVO::Wrapper executeGetHomeworkDetail(UInt64 id);
    StringJsonVO::Wrapper executeSubmitReview(const ReviewHomeworkDTO::Wrapper& req);
};

#include OATPP_CODEGEN_END(ApiController)

#endif