#include "stdafx.h"
#include "getrollcallrecord.h"
#include "../../service/service-huitailang/rollcallrecord/rollcallrecordservice.h"
RollCallJsonVO::Wrapper getrollrecllrecord::executeQueryRollCall(const RollcallQuery::Wrapper& query)
{
	//查询数据
	auto result = RollcallrecordService().listAll(query);
	//响应结果
	auto jvo = RollCallJsonVO::createShared();
	jvo->success(result);
	return jvo;
	
}