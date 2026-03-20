#pragma once
#include "stdafx.h"


#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"


#include "../domain/gw-domain/homework_domain.h" 
#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 * @apiDefine HomeworkApiGroup 作业模块
 * @apiDescription 作业查询、布置、点评等核心业务接口
 */
class HomeworkController : public oatpp::web::server::api::ApiController {
public:
    /**
     * 构造函数
     */
    explicit HomeworkController(const std::shared_ptr<ObjectMapper>& objectMapper)
        : oatpp::web::server::api::ApiController(objectMapper) {}

   
    static std::shared_ptr<HomeworkController> createShared(const std::shared_ptr<ObjectMapper>& objectMapper = nullptr) {
        auto mapper = objectMapper ? objectMapper : std::make_shared<oatpp::parser::json::mapping::ObjectMapper>();
        return std::make_shared<HomeworkController>(mapper);
    }

    // -------------------------- 接口1：获取作业列表 --------------------------
    /**
     * @api {get} /c4-workbench/homework/list 获取作业列表
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName getHomeworkList
     * @apiDescription 分页查询管理员可管理的作业列表，包含提交人数统计
     * @apiParam {String} admin_id 管理员ID（必填，权限校验）
     * @apiParam {String} class_id 班级ID（可选，筛选对应班级作业）
     * @apiParam {Int32} page 页码（默认1，分页查询）
     * @apiParam {Int32} size 每页条数（默认10，分页查询）
     * @apiSuccess (200) {Int32} code 响应码，0=成功
     * @apiSuccess (200) {String} msg 提示信息，success=成功
     * @apiSuccess (200) {Object[]} data 作业列表数据
     * @apiSuccess (200) {String} data.homework_id 作业ID
     * @apiSuccess (200) {String} data.title 作业标题
     * @apiSuccess (200) {String} data.class_name 班级名称
     * @apiSuccess (200) {Int32} data.submit_count 提交人数
     * @apiSuccess (200) {String} data.create_time 创建时间
     * @apiSuccessExample {json} 成功响应示例:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": [
     *     {
     *       "homework_id": "hw001",
     *       "title": "测试作业标题",
     *       "class_name": "5班",
     *       "submit_count": 0,
     *       "create_time": "2026-03-16"
     *     }
     *   ]
     * }
     */
    ENDPOINT("GET", "/c4-workbench/homework/list", getHomeworkList,
        QUERY(String, admin_id),
        QUERY(String, class_id),
        QUERY(Int32, page),
        QUERY(Int32, size)) {
        return createDtoResponse(Status::CODE_200,
            oatpp::String(R"({"code":0,"msg":"success","data":[{"homework_id":"hw001","title":"测试作业标题","class_name":"5班","submit_count":0,"create_time":"2026-03-16"}]})"));
    }

    // -------------------------- 接口2：获取作业详情 --------------------------
    /**
     * @api {get} /c4-workbench/homework/detail 获取作业详情
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName getHomeworkDetail
     * @apiDescription 查询单条作业的完整信息，包含学生提交记录和点评
     * @apiParam {String} homework_id 作业ID（必填）
     * @apiParam {String} admin_id 管理员ID（必填）
     * @apiSuccess (200) {Int32} code 响应码
     * @apiSuccess (200) {String} msg 提示信息
     * @apiSuccess (200) {Object} data 作业详情
     * @apiSuccessExample {json} 成功响应示例:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "homework_id": "hw001",
     *     "title": "测试作业标题",
     *     "class_name": "5班",
     *     "content": "作业要求内容"
     *   }
     * }
     */
    ENDPOINT("GET", "/c4-workbench/homework/detail", getHomeworkDetail,
        QUERY(String, homework_id),
        QUERY(String, admin_id)) {
        return createDtoResponse(Status::CODE_200,
            oatpp::String(R"({"code":0,"msg":"success","data":{"homework_id":"hw001","title":"测试作业标题","class_name":"5班","content":"作业要求内容"}})"));
    }

    // -------------------------- 接口3：布置新作业 --------------------------
    /**
     * @api {post} /c4-workbench/homework/add 布置新作业
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName addHomework
     * @apiDescription 管理员发布新作业
     * @apiParam {String} admin_id 发布人ID（必填）
     * @apiParam {String} class_id 班级ID（必填）
     * @apiParam {String} title 作业标题（必填）
     * @apiSuccess (200) {Int32} code 响应码
     * @apiSuccess (200) {String} msg 提示信息
     * @apiSuccess (200) {Object} data 新建作业信息
     * @apiSuccessExample {json} 成功响应示例:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "homework_id": "hw002",
     *     "title": "新作业"
     *   }
     * }
     */
    ENDPOINT("POST", "/c4-workbench/homework/add", addHomework,
        BODY_STRING(String, body)) {
        return createDtoResponse(Status::CODE_200,
            oatpp::String(R"({"code":0,"msg":"success","data":{"homework_id":"hw002","title":"新作业"}})"));
    }

    // -------------------------- 接口4：获取可管理班级列表 --------------------------
    /**
     * @api {get} /c4-workbench/class/list 获取可管理班级列表
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName getClassList
     * @apiDescription 查询管理员有权限管理的班级列表
     * @apiParam {String} admin_id 管理员ID（必填）
     * @apiSuccess (200) {Int32} code 响应码
     * @apiSuccess (200) {String} msg 提示信息
     * @apiSuccess (200) {Object[]} data 班级列表
     * @apiSuccessExample {json} 成功响应示例:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": [
     *     {
     *       "class_id": "class001",
     *       "class_name": "5班"
     *     }
     *   ]
     * }
     */
    ENDPOINT("GET", "/c4-workbench/class/list", getClassList,
        QUERY(String, admin_id)) {
        return createDtoResponse(Status::CODE_200,
            oatpp::String(R"({"code":0,"msg":"success","data":[{"class_id":"class001","class_name":"5班"}]})"));
    }

    // -------------------------- 接口5：提交作业点评 --------------------------
    /**
     * @api {post} /c4-workbench/homework/comment 提交作业点评
     * @apiGroup HomeworkApiGroup
     * @apiVersion 1.0.0
     * @apiName commentHomework
     * @apiDescription 老师对学生作业进行评分和写评语
     * @apiParam {String} submit_id 提交记录ID（必填）
     * @apiParam {String} admin_id 点评老师ID（必填）
     * @apiParam {Int32} score 评分（1-5，必填）
     * @apiSuccess (200) {Int32} code 响应码
     * @apiSuccess (200) {String} msg 提示信息
     * @apiSuccess (200) {Object} data 点评信息
     * @apiSuccessExample {json} 成功响应示例:
     * {
     *   "code": 0,
     *   "msg": "success",
     *   "data": {
     *     "comment_id": "comment001",
     *     "score": 5,
     *     "content": "完成得很好！"
     *   }
     * }
     */
    ENDPOINT("POST", "/c4-workbench/homework/comment", commentHomework,
        BODY_STRING(String, body)) {
        return createDtoResponse(Status::CODE_200,
            oatpp::String(R"({"code":0,"msg":"success","data":{"comment_id":"comment001","score":5,"content":"完成得很好！"}})"));
    }
};


#include OATPP_CODEGEN_END(ApiController)