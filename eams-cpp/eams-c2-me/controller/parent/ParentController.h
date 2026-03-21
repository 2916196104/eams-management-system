#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/parent/ParentDTO.h"
#include "domain/vo/ParentVO.h"
#include "domain/query/PageQuery.h"
#include "dao/DocClient.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "dao/parentDao.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 家长控制器
 */
class ParentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(ParentController);

  // 3 定义接口
public:
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("help.querylist"), // 接口标题
        getList, // 端点函数名
        ListQuery, // Query类型（自动生成参数文档）
        UsageGuideJsonVO::Wrapper, // 响应类型
        ZH_WORDS_GETTER("help.querylist") // 标签
    );

    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("help.querydetail"), // 接口标题
        getDetail, // 端点函数名
        DetailQuery, // Query类型（自动生成参数文档）
        UsageDeatailJsonVO::Wrapper, // 响应类型
        ZH_WORDS_GETTER("help.querydetail") // 标签
    );

    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET, // HTTP方法：GET
        "/me/parent/getList", // 路径
        getList, // 函数名
        ListQuery, // Query类型（自动解析参数）
        executeQueryAll(query) // 调用执行方法
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,
        "/me/parent/getDetail",
        getDetail,
        QUERY(String, id), // 接收单个查询参数
        executeQueryOne(id) // 调用执行方法
    );

private: // 定义接口执行函数
    std::shared_ptr<oatpp::orm::Executor> executor;
    UsageGuideJsonVO::Wrapper executeQueryAll(const ListQuery::Wrapper& query);
    UsageDeatailJsonVO::Wrapper executeQueryOne(const String& id);



    //=====================================================================

    //ENDPOINT_INFO(getList) {
    //    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("help.querylist"));
    //    API_DEF_ADD_PAGE_PARAMS(); // 自动添加pageIndex和pageSize
    //    API_DEF_ADD_AUTH();
    //}
    //ENDPOINT_INFO(getDetail) {
    //    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("help.querydetail"));
    //    API_DEF_ADD_PAGE_PARAMS(); // 自动添加pageIndex和pageSize
    //    API_DEF_ADD_AUTH();
    //}

    //ENDPOINT(API_M_GET, "/me/parent/getList", getList,
    //    QUERY(Int32, pageIndex, "pageIndex", 1), QUERY(Int32, pageSize, "pageSize", 20),
    //    AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)
    //)
    //{
    //    OATPP_COMPONENT(std::shared_ptr<oatpp::orm::Executor>, executor);
    //    //从第几条开始查询(数据库从零开始取条数)
    //    oatpp::Int32 offset = (pageIndex - 1) * pageSize;
    //    //从数据库拿到需要的数据
    //    DocClient user(executor);
    //    auto result = user.showList(offset, pageSize);
    //    //拿到数据库的总条数total
    //    auto count_result = user.countList();
    //    oatpp::Int32 total = count_result->fetch<oatpp::Int32>();//新版
    //    //打包返回
    //    auto pageDto = UsageGuidePageDto::createShared();
    //    pageDto->total = total;
    //    pageDto->pageIndex = pageIndex;
    //    pageDto->pageSize = pageSize;
    //    pageDto->list = result->fetch<oatpp::Vector<oatpp::Object<UsageGuideDto>>>();//新版
    //    return createDtoResponse(Status::CODE_200, pageDto);
    //}
    ////=====================================================================================
   
    //ENDPOINT(API_M_GET, "/me/parent/getDetail", getDetail,
    //    PATH(Int32, id, "id"), AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject) // 从URL路径获取ID
    //) {
    //    OATPP_COMPONENT(std::shared_ptr<oatpp::orm::Executor>, executor);
    //    DocClient user(executor);
    //    // 1. 获取DocClient的Executor，直接执行SQL
    //    auto dbResult = user.getDoc(id);
    //    auto detailDto = UsageGuideDetailDto::createShared();
    //    oatpp::Int32 id1 = dbResult->fetch<oatpp::Int32>();
    //    oatpp::String title = dbResult->fetch<oatpp::String>();
    //    oatpp::String content = dbResult->fetch<oatpp::String>();
    //    if (dbResult) {
    //        // 方式1：直接赋值（如果结构一致）
    //        detailDto->id = id1;
    //        detailDto->title = title;
    //        detailDto->content = content;
    //        return createDtoResponse(Status::CODE_200, detailDto);
    //    }
    //    else {
    //        // 处理数据不存在的情况
    //        OATPP_LOGD("ParentController", "Data not found for id: %d", id);
    //        // 可以抛出 404 异常或返回空 DTO
    //    }

    //   
    //}

    /*UsageGuidePageDto::Wrapper  getList(const PageQuery::Wrapper& query);
    UsageGuideDetailDto::Wrapper  geDetail(const PageQuery::Wrapper& query);*/
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_
