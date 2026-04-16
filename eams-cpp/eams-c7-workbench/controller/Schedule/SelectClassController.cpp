#include "stdafx.h"
#include "SelectClassController.h"
#include "../../service/Schedule/SelectClassService.h"

//StringJsonVO::Wrapper SelectClassController::executeQuerySelectClass(const PageQuery::Wrapper& query)
//{
//	auto vo = StringJsonVO::createShared();
//	vo->success(ZH_WORDS_GETTER("select_class.resp"));
//	return vo;
//}

//SelectClassListJsonVO::Wrapper SelectClassController::executeQueryNameList(const oatpp::String& name)
//{
//	return {};
//}
SelectClassPageJsonVO::Wrapper SelectClassController::executeQueryClassPage(const SelectClassQuery::Wrapper& query)
{
	//auto vo = SelectClassPageJsonVO::createShared();
	//vo->success(String((ZH_WORDS_GETTER("select_class.resp"))));
	//return vo;
// 查询数据
	auto result = SelectClassService().listAll(query);
	// 响应结果
	auto jvo = SelectClassPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}