#pragma once
#ifndef _POSITION_CONTROLLER_
#define _POSITION_CONTROLLER_

#include "domain/dto/position/PositionDTO.h"
#include "domain/vo/JsonVO.h"
#include "domain/vo/NoDataJsonVO.h"
#include "oatpp/core/Types.hpp"

#include "domain/dto/position/PositionDataPermissionQueryDTO.h"
#include "domain/dto/position/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/position/DeletePositionRequestDTO.h"
#include "domain/dto/position/JsonResponseDTO.h"
#include "domain/dto/position/EmptyDTO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/position/PositionVO.h"
// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("position.tag")

/*
 * 职位控制器
 */
class PositionController
    : public oatpp::web::server::api::ApiController // 1 继承控制器
{
    // 2 定义控制器访问入口
    API_ACCESS_DECLARE(PositionController);
    // 3 定义接口
public:
  ENDPOINT_INFO(fetchPositionAll) {

    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("position.interface.fetchAll"));
    API_DEF_ADD_TAG(ZH_WORDS_GETTER("position.interface.title"));
    API_DEF_ADD_AUTH();

    auto &example = info->addResponse<oatpp::Object<ALLPositionsVO>>(
        Status::CODE_200, "application/json");

    auto vo = ALLPositionsVO::createShared();
    vo->code = 10000;
    vo->message = u8"10000成功9998服务繁忙";
    auto data = Vector<PositionItemDTO::Wrapper>::createShared();
    auto positionItem = PositionItemDTO::createShared();
    positionItem->id = 10;
    positionItem->name = u8"校长";
    data->push_back(positionItem);
    vo->data = data;
    example.addExample("example", vo);
  }
  ENDPOINT("GET", "/c2-org/position/all", fetchPositionAll,
           AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, auth));

  ENDPOINT_INFO(fetchPositionList) {

    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("position.interface.pageQuery"));
    API_DEF_ADD_TAG(ZH_WORDS_GETTER("position.interface.title"));
    API_DEF_ADD_AUTH();

    auto &example = info->addResponse<oatpp::Object<PositionListVO>>(
        Status::CODE_200, "application/json");

    auto vo = PositionListVO::createShared();
    vo->code = 10000;
    vo->message = u8"10000成功9995参数错误";
    auto data = Vector<PositionItemDTO::Wrapper>::createShared();
    auto positionItem = PositionItemDTO::createShared();
    positionItem->id = 10;
    positionItem->name = u8"校长";
    data->push_back(positionItem);
    vo->data = data;
    vo->limit = 1;
    vo->totalPages = 1;
    vo->total = 1;
    vo->page = 1;
    example.addExample("example", vo);
  }
  ENDPOINT("GET", "/c2-org/position/list", fetchPositionList,
           AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, auth),
           QUERY(Int32, pageNum, "pageNum", 1),
           QUERY(Int32, pageSize, "pageSize", 10),
           QUERY(String, keyWord, "keyWord", ""));

  ENDPOINT_INFO(savePosition) {

    API_DEF_ADD_TITLE(ZH_WORDS_GETTER("position.interface.save"));
    API_DEF_ADD_TAG(ZH_WORDS_GETTER("position.interface.title"));
    API_DEF_ADD_AUTH();

    auto &example = info->addResponse<oatpp::Object<JsonVO<oatpp::Int64>>>(
        Status::CODE_200, "application/json");

    auto vo = JsonVO<oatpp::Int64>::createShared();
    vo->code = 10000;
    vo->message =
        u8"10000成功9998服务繁忙 9995参数错误 data>0时表示新增返回的id";
    vo->data = 10;
    example.addExample("example", vo);
  }
  ENDPOINT("POST", "/c2-org/position/save", savePosition,
           AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, auth),
           BODY_DTO(PositionSaveRequestDTO::Wrapper, dto));


  // 为第一个接口添加标签（英文测试，确保功能）
  ENDPOINT_INFO(getPositionDataPermissionList) {
    info->addTag(API_TAG);
  }
  ENDPOINT("POST", "/c2-org/positions/data/permissions/list", getPositionDataPermissionList, BODY_DTO(oatpp::Object<PositionDataPermissionQueryDTO>, request));

    // 为第二个接口添加标签
  ENDPOINT_INFO(deletePositions) {
    info->addTag(API_TAG);
  }
  ENDPOINT("POST", "/c2-org/positions/delete", deletePositions, BODY_DTO(oatpp::Object<DeletePositionRequestDTO>, request));
private: // 定义接口执行函数
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif                                    // !_POSITION_CONTROLLER_
