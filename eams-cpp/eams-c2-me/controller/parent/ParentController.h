#pragma once

#ifndef _PARENT_CONTROLLER_ 
#define _PARENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"

// 1 瀹氫箟API鎺у埗鍣ㄤ娇鐢ㄥ畯
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 瀹堕暱鎺у埗鍣?
 */
class ParentController : public oatpp::web::server::api::ApiController // 1 缁ф壙鎺у埗鍣?
{
  // 2 瀹氫箟鎺у埗鍣ㄨ闂叆鍙?
  API_ACCESS_DECLARE(ParentController);
  // 3 瀹氫箟鎺ュ彛
public:

private: // 瀹氫箟鎺ュ彛鎵ц鍑芥暟
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_
