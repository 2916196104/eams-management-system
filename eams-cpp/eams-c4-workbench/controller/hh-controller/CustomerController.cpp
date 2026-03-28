#include "CustomerController.h"
#include "../../service/workbench/hh-service/HhService.h"

CustomerPageJsonVO::Wrapper CustomerController::execQueryCustomer(const CustomerQuery::Wrapper& query, const PayloadDTO& payload) {
	// 取出查询人ID
	auto creator_id = payload.getId();

	// 查询数据
	auto result = HhService().listAllStudent(query, creator_id);

	// 响应结果
	auto jvo = CustomerPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

CustomerDetailJsonVO::Wrapper CustomerController::execQueryDetailById(const String& id) {
	auto jvo = CustomerDetailJsonVO::createShared();

	if (!id) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据新增
	auto res = HhService().getDetailById(id);
	jvo->success(res);

	return jvo;
}

CustomerLessonListJsonVO::Wrapper CustomerController::execQueryLessonById(const String& id) {
	auto jvo = CustomerLessonListJsonVO::createShared();

	if (!id) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	auto res = HhService().getLessonListById(id);
	jvo->success(res);

	return jvo;
}
