#pragma once

#ifndef _POSITIONDATA_CONTROLLER_ 
#define _POSITIONDATA_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "../../domain/dto/position/PositionDataDTO.h"

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("position.tag")

/*
 * 职位数据权限控制器
 */
class PositionDataController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(PositionDataController);
	// 3 定义接口
public:

	// -01: 修改或者新增职位数据权限接口，只完成了新增的逻辑，修改的逻辑还需要完善；并且新增数据是还会报错
	// 定义新增职位数据权限接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("position.datapermission.endpoint.modifyoradd"), savePositionDataPermission, Uint64JsonVO::Wrapper, API_TAG);

	// 定义新增职位数据权限接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c2-org/position/dataPermissionSave", savePositionDataPermission, BODY_DTO(PositionDataDTO::Wrapper, dto), executesavePositionDataPermission(dto));

	// -02: 删除职位数据权限的接口(支持批量删除)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("position.datapermission.endpoint.delete"), deletePositionDataPermission, ListJsonVO<UInt64>::Wrapper, API_TAG);

	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/c2-org/position/dataPermissionDelete", deletePositionDataPermission, BODY_DTO(List<UInt64>, ids), execdeleteDataPermission(ids));


private: // 定义接口执行函数
	
	// 新增职位数据区权限或者修改职位数据权限函数
	Uint64JsonVO::Wrapper executesavePositionDataPermission(const PositionDataDTO::Wrapper& dto);

	// 删除职位数据权限函数
	ListJsonVO<UInt64>::Wrapper execdeleteDataPermission(const List<UInt64>& ids); //oatpp中的List<>这样的数据结构里面的模板参数必须是一个类，如果要表示uint
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_POSITION_CONTROLLER_