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

// 1 瀹氫箟API鎺у埗鍣ㄤ娇鐢ㄥ畯
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 鑱屼綅鎺у埗鍣?
 */
class PositionController : public oatpp::web::server::api::ApiController // 1 缁ф壙鎺у埗鍣?
{
  // 2 瀹氫箟鎺у埗鍣ㄨ闂叆鍙?
  API_ACCESS_DECLARE(PositionController);
  // 3 瀹氫箟鎺ュ彛
public:
    ENDPOINT("POST", "/positions/data/permissions/list", getPositionDataPermissionList, BODY_DTO(oatpp::Object<PositionDataPermissionQueryDTO>, request));
    ENDPOINT("POST", "/positions/delete", deletePositions,BODY_DTO(oatpp::Object<DeletePositionRequestDTO>, request));
private: // 瀹氫箟鎺ュ彛鎵ц鍑芥暟
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_
