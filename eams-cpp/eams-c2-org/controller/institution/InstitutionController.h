#pragma once
#include "domain/vo/BaseJsonVO.h" // 假设你们返回包装体在这个文件
#include "../eams-c2-org/domain/dto/institution/InstitutionDTO.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG "机构管理"

class InstitutionController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(InstitutionController); // 自动生成构造函数等

public:
    using TreeResultVO = ListJsonVO<InstitutionDTO::Wrapper>::Wrapper;

    // 接口 1：获取机构树 (使用宏自动加上 Bearer Auth 和 Swagger 文档)
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("institution.api.get"), queryTree, TreeResultVO, API_TAG);
    // 因为没有查询参数，我们使用原始方式或对应宏
    ENDPOINT("GET", "org/institution/getInstitutionTree", queryTree, API_HANDLER_AUTH_PARAME) {
        return createDtoResponse(Status::CODE_200, execQueryTree());
    }

    // 接口 2：保存机构 [cite: 697-710]
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("institution.api.save"), saveInstitution, StringJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "org/institution/saveInstitution",
        saveInstitution,
        BODY_DTO(InstitutionDTO::Wrapper, dto),
        execSaveInstitution(dto, authObject->getPayload()) // authObject 由宏自动提取
    );

private:
    TreeResultVO execQueryTree();
    StringJsonVO::Wrapper execSaveInstitution(const InstitutionDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)