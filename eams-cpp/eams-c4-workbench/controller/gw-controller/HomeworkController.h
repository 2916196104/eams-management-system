#pragma once
#include "stdafx.h"


#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"


#include "domain/query/gw-query/HomeworkListQuery.h"
#include "domain/query/gw-query/HomeworkDetailQuery.h"
#include "domain/query/gw-query/HomeworkAddQuery.h"
#include "domain/query/gw-query/HomeworkCommentQuery.h"
#include "domain/vo/gw-vo/HomeworkListItemVO.h"
#include "domain/vo/gw-vo/HomeworkDetailVO.h"
#include "domain/vo/gw-vo/HomeworkAddVO.h"
#include "domain/vo/gw-vo/HomeworkCommentVO.h"
#include "domain/dto/gw-dto/CommonResponseDTO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG u8"\u4F5C\u4E1A"

/**
 * @apiDefine HomeworkApiGroup ??????
 * @apiDescription ????????????????????????????
 */
class HomeworkController : public oatpp::web::server::api::ApiController {
public:
    /**
     * ??????
     */
    explicit HomeworkController(const std::shared_ptr<ObjectMapper>& objectMapper)
        : oatpp::web::server::api::ApiController(objectMapper) {}

   
    static std::shared_ptr<HomeworkController> createShared(const std::shared_ptr<ObjectMapper>& objectMapper = nullptr) {
        auto mapper = objectMapper ? objectMapper : std::make_shared<oatpp::parser::json::mapping::ObjectMapper>();
        return std::make_shared<HomeworkController>(mapper);
    }

    // -------------------------- ???1???????????? --------------------------
    /**
     * @api {get} /c4-class/homework/list ??????????
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName getHomeworkList
     * @apiDescription ????????????????????????????????????????
     * @apiParam {String} admin_id ?????ID?????????????
     * @apiParam {String} class_id ??ID???????????????????
     * @apiParam {Int32} page ??????1??????????
     * @apiParam {Int32} size ???????????10??????????
     * @apiSuccess (200) {Int32} code ?????0=???
     * @apiSuccess (200) {String} msg ????????success=???
     * @apiSuccess (200) {Object[]} data ???????????
     * @apiSuccess (200) {String} data.homework_id ???ID
     * @apiSuccess (200) {String} data.title ???????
     * @apiSuccess (200) {String} data.class_name ??????
     * @apiSuccess (200) {Int32} data.submit_count ??????
     * @apiSuccess (200) {String} data.create_time ???????
     * @apiSuccessExample {json} ?????????:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": [
     *     {
     *       "homework_id": "hw001",
     *       "title": "???????????",
     *       "class_name": "5??",
     *       "submit_count": 0,
     *       "create_time": "2026-03-16"
     *     }
     *   ]
     * }
     */
    ENDPOINT_INFO(getHomeworkList) {
      info->summary = u8"\u67E5\u8BE2\u4F5C\u4E1A\u5217\u8868";
      info->addTag(API_TAG);
      info->addResponse<oatpp::Object<HomeworkListPageJsonVO>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("GET", "/c4/homework/list", getHomeworkList,
        QUERY(String, admin_id),
        QUERY(String, class_id),
        QUERY(Int32, page),
        QUERY(Int32, size)) {
        HomeworkListQuery query{
            admin_id,
            class_id,
            page > 0 ? page : 1,
            size > 0 ? size : 10
        };
        (void)query;
        auto row = HomeworkListRowDTO::createShared();
        row->homework_id = "hw001";
        row->title = "sample title";
        row->class_name = "class-5";
        row->submit_count = 0;
        row->create_time = "2026-03-16";

        auto pageData = HomeworkListPageDTO::createShared();
        pageData->pageIndex = page > 0 ? page : 1;
        pageData->pageSize = size > 0 ? size : 5;
        pageData->total = 1;
        pageData->pages = 1;
        pageData->rows->push_back(row);

        auto result = HomeworkListPageJsonVO::createShared();
        result->code = 10000;
        result->message = "success";
        result->data = pageData;
        return createDtoResponse(Status::CODE_200, result);
    }

    // -------------------------- ???2???????????? --------------------------
    /**
     * @api {get} /c4-class/homework/detail ??????????
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName getHomeworkDetail
     * @apiDescription ??????????????????????????????????????
     * @apiParam {String} homework_id ???ID??????
     * @apiParam {String} admin_id ?????ID??????
     * @apiSuccess (200) {Int32} code ?????
     * @apiSuccess (200) {String} msg ??????
     * @apiSuccess (200) {Object} data ???????
     * @apiSuccessExample {json} ?????????:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "homework_id": "hw001",
     *     "title": "???????????",
     *     "class_name": "5??",
     *     "content": "??????????"
     *   }
     * }
     */
    ENDPOINT_INFO(getHomeworkDetail) {
      info->summary = u8"\u67E5\u8BE2\u4F5C\u4E1A\u8BE6\u60C5";
      info->addTag(API_TAG);
      info->addResponse<oatpp::Object<HomeworkDetailJsonVO>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("GET", "/c4/homework/detail", getHomeworkDetail,
        QUERY(String, homework_id),
        QUERY(String, admin_id)) {
        HomeworkDetailQuery query{
            homework_id,
            admin_id
        };
        (void)query;
        auto data = HomeworkDetailDataDTO::createShared();
        data->homework_id = "hw001";
        data->title = "sample title";
        data->class_name = "class-5";
        data->content = "sample content";

        auto result = HomeworkDetailJsonVO::createShared();
        result->code = 10000;
        result->message = "success";
        result->data = data;
        return createDtoResponse(Status::CODE_200, result);
    }

    // -------------------------- ???3??????????? --------------------------
    /**
     * @api {post} /c4-class/homework/add ?????????
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName addHomework
     * @apiDescription ??????????????
     * @apiParam {String} admin_id ??????ID??????
     * @apiParam {String} class_id ??ID??????
     * @apiParam {String} title ???????????
     * @apiSuccess (200) {Int32} code ?????
     * @apiSuccess (200) {String} msg ??????
     * @apiSuccess (200) {Object} data ?????????
     * @apiSuccessExample {json} ?????????:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "homework_id": "hw002",
     *     "title": "?????"
     *   }
     * }
     */
    ENDPOINT_INFO(addHomework) {
      info->summary = u8"\u53D1\u5E03\u4F5C\u4E1A";
      info->addTag(API_TAG);
      info->addResponse<oatpp::Object<HomeworkAddJsonVO>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", "/c4/homework/add", addHomework,
        BODY_STRING(String, body)) {
        HomeworkAddQuery query;
        (void)query;
        (void)body;
        auto data = HomeworkAddDataDTO::createShared();
        data->homework_id = "hw002";
        data->title = "new homework";

        auto result = HomeworkAddJsonVO::createShared();
        result->code = 10000;
        result->message = "success";
        result->data = data;
        return createDtoResponse(Status::CODE_200, result);
    }

    // -------------------------- ???5??????????? --------------------------
    /**
     * @api {post} /c4-class/homework/comment ?????????
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName commentHomework
     * @apiDescription ??????????????????????????
     * @apiParam {String} submit_id ?????ID??????
     * @apiParam {String} admin_id ???????ID??????
     * @apiParam {Int32} score ?????1-5??????
     * @apiSuccess (200) {Int32} code ?????
     * @apiSuccess (200) {String} msg ??????
     * @apiSuccess (200) {Object} data ???????
     * @apiSuccessExample {json} ?????????:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "comment_id": "comment001",
     *     "score": 5,
     *     "content": "????????"
     *   }
     * }
     */
    ENDPOINT_INFO(commentHomework) {
      info->summary = u8"\u70B9\u8BC4\u4F5C\u4E1A";
      info->addTag(API_TAG);
      info->addResponse<oatpp::Object<HomeworkCommentJsonVO>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", "/c4/homework/comment", commentHomework,
        BODY_STRING(String, body)) {
        HomeworkCommentQuery query;
        (void)query;
        (void)body;
        auto data = HomeworkCommentDataDTO::createShared();
        data->comment_id = "comment001";
        data->score = 5;
        data->content = "good work";

        auto result = HomeworkCommentJsonVO::createShared();
        result->code = 10000;
        result->message = "success";
        result->data = data;
        return createDtoResponse(Status::CODE_200, result);
    }
};


#include OATPP_CODEGEN_END(ApiController)

