#pragma once
#ifndef _SELECTCLASSCONTROLLER_H_
#define _SELECTCLASSCONTROLLER_H_

//#include "oatpp/web/server/api/ApiController.hpp"
//#include "oatpp/core/macro/codegen.hpp"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/Schedule/SelectClassVO.h"
#include "domain/query/Schedule/SelectClassQuery.h"
//#include "ApiHelper.h"
//#include "domain/query/PageQuery.h"
//#include "ServerInfo.h"
//#include "Macros.h"

/*
* 班级数据控制器
*/
#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin ApiController codegen section

class SelectClassController : public oatpp::web::server::api::ApiController {
    //public:

        //MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) /* Inject object mapper */)
        //    : oatpp::web::server::api::ApiController(objectMapper)
        //{
        //}

        //ENDPOINT("GET", "/", root) {
        //    return createResponse(Status::CODE_200, "Hello World!");
        //}

        //// TODO - more endpoints here
    API_ACCESS_DECLARE(SelectClassController);
public:
    //    API_DEF_ENDPOINT_INFO_AUTH();
    //
    // /**
    // * API描述定义，定义的时候添加授权定义
    // * @param __TITLE__: Api描述标题
    // * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
    // * @param __RESP_TYPE__: 响应数据类型如：XxxJsonVO::Wrapper
    // * @param __TAG__: Api描述标签
    // * @param ...: 扩展选项
    // * 1234
    // */
    //#define API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, ...) \
    //ENDPOINT_INFO(__ENDPOINT_FUN_NAME__) { \
    //	API_DEF_ADD_COMMON_AUTH(__TITLE__, __RESP_TYPE__, __TAG__); \
    //	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
    //}
    //
    // /**
    //  * API描述添加通用参数定义，定义的时候会定义授权参数
    //  * @param _TITLE_: 接口标题
    //  * @param __RESP_TYPE__: 接口响应参数类型。如："UserPageJsonVO::Wrapper"、"StringJsonVO::Wrapper"
    //  * @param __TAG__: 标签名称
    //  * 1234
    //  */
    //#define API_DEF_ADD_COMMON_AUTH(_TITLE_, __RESP_TYPE__, __TAG__) \
    //API_DEF_ADD_AUTH(); \
    //API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__)
    //
    //  /**
    //   * API描述添加通用参数定义
    //   * @param _TITLE_: 接口标题
    //   * @param __RESP_TYPE__: 接口响应参数类型。如："UserPageJsonVO::Wrapper"、"StringJsonVO::Wrapper"
    //   * @param __TAG__: 标签名称
    //   * 234
    //   */
    //#define API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__) \
    //API_DEF_ADD_TITLE(_TITLE_); \
    //API_DEF_ADD_TAG(__TAG__); \
    //API_DEF_ADD_RSP_JSON(__RESP_TYPE__)
    //
    //   // 描述定义扩展参数展开相关宏
    //#define API_DEF_EXPAND( x ) x
    //// 定义空标记
    //#define API_DEF_NOTHING


    // /**
    // * API描述添加查询参数说明
    // * @param _TYPE_: 字段数据类型。如：String、UInt32等
    // * @param _FIELD_NAME_: 字段名称。如："age"、"sex"
    // * @param _DESCRIPTION_: 字段描述。
    // * @param _EXAMPLE_VAL_: 示例值。如："li si"、123
    // * @param _REQUIRE_: 是否必传参数，bool值。如：true、false
    // */
    //#define API_DEF_ADD_QUERY_PARAMS(_TYPE_, _FIELD_NAME_, _DESCRIPTION_, _EXAMPLE_VAL_, _REQUIRE_) \
    //info->queryParams.add<_TYPE_>(_FIELD_NAME_).description = _DESCRIPTION_; \
    //info->queryParams[_FIELD_NAME_].addExample("default", _TYPE_(_EXAMPLE_VAL_)); \
    //info->queryParams[_FIELD_NAME_].required = _REQUIRE_

        //API_DEF_ADD_PAGE_PARAMS();

    //// 处理跨平台描述信息中文乱码问题
    //#ifndef LINUX
    //#define API_PAGE_INDEX_DESC u8"查询页码"
    //#define API_PAGE_SIZE_DESC u8"查询条数"
    //#else
    //#define API_PAGE_INDEX_DESC "page index"
    //#define API_PAGE_SIZE_DESC "page size"
    //#endif
    //// API描述添加分页参数说明
    //#define API_DEF_ADD_PAGE_PARAMS() \
    //info->queryParams.add<UInt64>("pageIndex").description = API_PAGE_INDEX_DESC;\
    //info->queryParams["pageIndex"].addExample("default", oatpp::UInt64(1)); \
    //info->queryParams.add<UInt64>("pageSize").description = API_PAGE_SIZE_DESC; \
    //info->queryParams["pageSize"].addExample("default", oatpp::UInt64(10))

        //API_DEF_ENDPOINT_INFO_AUTH(
        //    ZH_WORDS_GETTER("select_class.A"), querySelectClassNameList, SelectClassListJsonVO::Wrapper, ZH_WORDS_GETTER("select_class.tag"),
        //    API_DEF_ADD_QUERY_PARAMS(String, "name,", ZH_WORDS_GETTER("select_class.id"), "sss", false);
        //);

        //ENDPOINT_INFO(querySelectClass) {
        //    //info->summary = ZH_WORDS_GETTER("select_class.summary");
        //    API_DEF_ADD_TAG(ZH_WORDS_GETTER("select_class.tag"));//3
        //    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("select_class.summary"));//2
        //    API_DEF_ADD_AUTH();//1
        //    API_DEF_ADD_PAGE_PARAMS();
        //    API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);//4
        //    API_DEF_ADD_QUERY_PARAMS(String, "name,", ZH_WORDS_GETTER("select_class.name"), "", false);
            //info->addConsumes<Object<UserDto>>("application/json");
            //info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        //}


    //    /**
    // * API端点定义，定义的时候添加授权定义
    // * @param _METHOD_: 请求方式。如：API_M_GET
    // * @param _PATH_: 端点访问地址。如：/user/query-by-name
    // * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
    // * @param _PARAM_MACRO_: 指定一个参数解析操作宏。如：BODY_DTO(SampleDTO::Wrapper, dto)
    // * @param _EXECUTE_: 处理逻辑，调用execXXX函数。如：execModifySample(dto)
    // */
    //#define API_HANDLER_ENDPOINT_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, _EXECUTE_) \
    //ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, API_HANDLER_AUTH_PARAME) { \
    //	API_HANDLER_RESP_VO(_EXECUTE_); \
    //}

        //API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c7/workbench/selectclass/byname", querySelectClassNameList, QUERY(String, name), executeQueryNameList(name));

        //ENDPOINT(API_M_GET, "/select_class", querySelectClass,QUERIES(QueryParams,params),API_HANDLER_AUTH_PARAME) {
        //    API_HANDLER_QUERY_PARAM(query, PageQuery, params);
        //    API_HANDLER_RESP_VO(executeQuerySelectClass(query));
        //}
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("select_class.B"), querySelectClassPage, SelectClassQuery, SelectClassPageJsonVO::Wrapper, ZH_WORDS_GETTER("select_class.tag"));
    API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c7-workbench/selectclass", querySelectClassPage, QUERIES(QueryParams, queryParams),
        API_HANDLER_QUERY_PARAM(query, SelectClassQuery, queryParams); API_HANDLER_RESP_VO(executeQueryClassPage(query)););
private:
    //StringJsonVO::Wrapper executeQuerySelectClass(const PageQuery::Wrapper& query);
   // SelectClassListJsonVO::Wrapper executeQueryNameList(const oatpp::String& name);
    SelectClassPageJsonVO::Wrapper executeQueryClassPage(const SelectClassQuery::Wrapper& query);
};

#include OATPP_CODEGEN_END(ApiController) ///< End ApiController codegen section
#endif