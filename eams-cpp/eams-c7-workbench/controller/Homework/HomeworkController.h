#pragma once

#ifndef _HOMEWORKCONTROLLER_H_
#define _HOMEWORKCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/Homework/HomeworkVO_xxyj.h"
#include "domain/query/Homework/HomeworkQuery_xxyj.h"
#include "domain/dto/Homework/HomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("homework.tag")

class HomeworkController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(HomeworkController);

public:
    // 布置作业
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.assign.summary"), assignHomework, StringJsonVO::Wrapper, API_TAG,
        info->addConsumes<oatpp::Object<AssignHomeworkDTO>>("application/json");
    )
        API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/homework/assign", assignHomework,
            BODY_DTO(oatpp::Object<AssignHomeworkDTO>, dto),
            execAssignHomework(dto));

    // 获取作业详情
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.detail.summary"), getHomeworkDetail, HomeworkDetailJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(UInt64, "homeworkId", ZH_WORDS_GETTER("homework.field.id"), 10086, true);   // 改为 UInt64
    )
        API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7-workbench/homework/detail", getHomeworkDetail,
            QUERY(UInt64, homeworkId, "homeworkId"),
            execGetHomeworkDetail(homeworkId));

    // 点评作业
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.review.summary"), reviewHomework, ReviewResultJsonVO::Wrapper, API_TAG,
        info->addConsumes<oatpp::Object<ReviewHomeworkDTO>>("application/json");
    )
        API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/homework/review", reviewHomework,
            BODY_DTO(oatpp::Object<ReviewHomeworkDTO>, dto),
            execReviewHomework(dto));

private:
    StringJsonVO::Wrapper execAssignHomework(const oatpp::Object<AssignHomeworkDTO>& dto);
    HomeworkDetailJsonVO::Wrapper execGetHomeworkDetail(const oatpp::UInt64& homeworkId);   // 参数类型改为 UInt64
    ReviewResultJsonVO::Wrapper execReviewHomework(const oatpp::Object<ReviewHomeworkDTO>& dto);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORKCONTROLLER_H_