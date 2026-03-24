#pragma once


#include "../lib-oatpp/include/ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
//#include "domain/query/PageQuery.h"

#define API_TAG "机构管理"

#include OATPP_CODEGEN_BEGIN(ApiController)

//#define API_TAG ZH_WORDS_GETTER("institution.tags.management")

/**
 * 机构控制器
 */
class InstitutionController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(InstitutionController);

public:
    // ==================== 1. 获取机构列表 ====================
    ENDPOINT_INFO(queryInstitutionList) {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("institution.list.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_PAGE_PARAMS();
        API_DEF_ADD_QUERY_PARAMS(Int64, "pid", ZH_WORDS_GETTER("institution.field.pid"), 0LL, false);
        API_DEF_ADD_QUERY_PARAMS(Int32, "type", ZH_WORDS_GETTER("institution.field.type"), 0, false);
        API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("institution.field.name"), "", false);
    }
    ENDPOINT(API_M_GET, "/org/institution/list", queryInstitutionList,
        QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_RESP_VO(execQueryInstitutionList());
    }

    // ==================== 2. 获取机构详情 ====================
    ENDPOINT_INFO(queryInstitutionDetail) {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("institution.detail.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_QUERY_PARAMS(Int64, "id", ZH_WORDS_GETTER("institution.field.id"), 1LL, true);
    }
    ENDPOINT(API_M_GET, "/org/institution/detail", queryInstitutionDetail,
        QUERY(Int64, id), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_RESP_VO(execQueryInstitutionDetail(id));
    }

    // ==================== 3. 删除机构 ====================
    ENDPOINT_INFO(deleteInstitution) {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("institution.delete.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(BooleanJsonVO);
        API_DEF_ADD_TAG(API_TAG);
    }
    ENDPOINT(API_M_POST, "/org/institution/delete", deleteInstitution,
        BODY_STRING(String, id), API_HANDLER_AUTH_PARAME) {
        API_HANDLER_RESP_VO(execDeleteInstitution(id));
    }

private:
    StringJsonVO::Wrapper execQueryInstitutionList();
    StringJsonVO::Wrapper execQueryInstitutionDetail(const Int64& id);
    BooleanJsonVO::Wrapper execDeleteInstitution(const String& id);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)