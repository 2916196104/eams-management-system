#pragma once
#include "domain/vo/BaseJsonVO.h" // 假设你们返回包装体在这个文件
#include "../eams-c2-org/domain/dto/institution/InstitutionDTO.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include "../lib-oatpp/include/ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG "机构管理"

class InstitutionController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(InstitutionController); // 自动生成构造函数等

public:
    using TreeResultVO = ListJsonVO<InstitutionDTO::Wrapper>::Wrapper;

    // 接口 1：获取机构树 (使用宏自动加上 Bearer Auth 和 Swagger 文档)
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("institution.api.get"), queryTree, TreeResultVO, API_TAG);
    // 因为没有查询参数，我们使用原始方式或对应宏
    ENDPOINT("GET", "c2-org/institution/getInstitutionTree", queryTree, API_HANDLER_AUTH_PARAME) {
        return createDtoResponse(Status::CODE_200, execQueryTree());
    }

    // 接口 2：保存机构 [cite: 697-710]
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("institution.api.save"), saveInstitution, StringJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "c2-org/institution/saveInstitution",
        saveInstitution,
        BODY_DTO(InstitutionDTO::Wrapper, dto),
        execSaveInstitution(dto, authObject->getPayload()) // authObject 由宏自动提取
    );

private:
    TreeResultVO execQueryTree();
    StringJsonVO::Wrapper execSaveInstitution(const InstitutionDTO::Wrapper& dto, const PayloadDTO& payload);

    // ==================== 1. 获取机构列表 ====================
    ENDPOINT_INFO(queryInstitutionList) {
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("institution.list.summary"));
        API_DEF_ADD_AUTH();
        API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_PAGE_PARAMS();
        //API_DEF_ADD_QUERY_PARAMS(UInt64, "pid", ZH_WORDS_GETTER("institution.field.pid"), 0LL, false);
        API_DEF_ADD_QUERY_PARAMS(Int32, "type", ZH_WORDS_GETTER("institution.field.type"), 0, false);
        API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("institution.field.name"), "", false);
    }
    ENDPOINT(API_M_GET, "/c2-org/institution/list", queryInstitutionList,
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
    ENDPOINT(API_M_GET, "/c2-org/institution/detail", queryInstitutionDetail,
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
    ENDPOINT(API_M_POST, "/c2-org/institution/delete", deleteInstitution,
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