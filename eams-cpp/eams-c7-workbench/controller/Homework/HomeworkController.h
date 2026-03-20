#pragma once

#ifndef _HOMEWORKCONTROLLER_H_
#define _HOMEWORKCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "domain/vo/Homework/HomeworkVO_xxyj.h"
#include "domain/query/Homework/HomeworkQuery_xxyj.h"
#include "domain/dto/Homework/HomeworkDTO_xxyj.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("homework.tag")

class HomeworkController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(HomeworkController);

public:
    // ---------- 布置作业接口 ----------
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.assign.summary"), assignHomework, StringJsonVO::Wrapper, API_TAG,
        info->addConsumes<oatpp::Object<AssignHomeworkDTO>>("application/json");
    );
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/homework/assign", assignHomework,
        BODY_DTO(oatpp::Object<AssignHomeworkDTO>, dto),
        execAssignHomework(dto));

    /* 获取作业详情接口
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.detail.summary"), getHomeworkDetail, HomeworkDetailJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(Int64, "homeworkId", ZH_WORDS_GETTER("homework.field.id"), 10086, true);
    );
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/homework/detail", getHomeworkDetail,
        QUERY(Int64, homeworkId, "homeworkId"),
        execGetHomeworkDetail(homeworkId));
    */

    // 获取作业提交记录列表接口（使用 QUERY_AUTH 自动解析 DTO）
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("homework.record.list.summary"), getHomeworkRecordList, HomeworkRecordListQuery, HomeworkRecordListJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/homework/record/list", getHomeworkRecordList, HomeworkRecordListQuery,
        execGetHomeworkRecordList(query));

    // 点评作业接口
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.review.summary"), reviewHomework, ReviewResultJsonVO::Wrapper, API_TAG,
        info->addConsumes<oatpp::Object<ReviewHomeworkDTO>>("application/json");
    );
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/homework/review", reviewHomework,
        BODY_DTO(oatpp::Object<ReviewHomeworkDTO>, dto),
        execReviewHomework(dto));

private:
    StringJsonVO::Wrapper execAssignHomework(const oatpp::Object<AssignHomeworkDTO>& dto);
    HomeworkDetailJsonVO::Wrapper execGetHomeworkDetail(Int64 homeworkId);
    HomeworkRecordListJsonVO::Wrapper execGetHomeworkRecordList(const oatpp::Object<HomeworkRecordListQuery>& query);
    ReviewResultJsonVO::Wrapper execReviewHomework(const oatpp::Object<ReviewHomeworkDTO>& dto);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_HOMEWORKCONTROLLER_H_