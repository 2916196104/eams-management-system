#pragma once

#ifndef _POSITION_CONTROLLER_ 
#define _POSITION_CONTROLLER_ 

#include "domain/dto/postion/PositionDataPermissionQueryDTO.h"
#include "domain/dto/postion/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/postion/DeletePositionRequestDTO.h"
#include "domain/dto/postion/JsonResponseDTO.h"
#include "domain/dto/postion/EmptyDTO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 职位控制器
 */
class PositionController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(PositionController);
  // 3 定义接口
public:
    ENDPOINT("POST", "/positions/data/permissions/list", getPositionDataPermissionList, BODY_DTO(oatpp::Object<PositionDataPermissionQueryDTO>, request));
    ENDPOINT("POST", "/positions/delete", deletePositions,BODY_DTO(oatpp::Object<DeletePositionRequestDTO>, request));
private: // 定义接口执行函数
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_
