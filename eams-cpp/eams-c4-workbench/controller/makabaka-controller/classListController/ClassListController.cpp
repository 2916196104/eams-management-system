#include"stdafx.h"
#include"ClassListController.h"
#include"../../../service/makabaka-service/ClassListService.h"
#include"../../../domain/vo/makabaka-vo/class/classVO.h"

ClassPageJsonVO::Wrapper ClassListController::executeGetClassList(const ClassQuery::Wrapper& query) {
	//查询数据
	auto result = ClassListService().listAll(query);
	//响应结果
	auto jvo = ClassPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}