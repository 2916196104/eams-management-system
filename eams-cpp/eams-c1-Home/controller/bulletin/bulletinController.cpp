#include "stdafx.h"
#include "bulletinController.h"
#include"../../service/bulletin/bulletinService.h"
//实现接口执行函数

titleJsonVO::Wrapper bulletinController::executeQueryTitle()
{
	// 调用Service层获取最新公告
	auto result = bulletinService().getLatest();

	// 包装响应结果
	auto jvo = titleJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

listPageJsonVO::Wrapper bulletinController::executeQueryList(const PageQuery::Wrapper& query)
{
	auto result = bulletinService().listAll(query);

	// 包装响应结果
	auto jvo = listPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

redJsonVO::Wrapper bulletinController::executeQueryRed(const Int64& student_id)
{
	//std::cout << "=== 开始处理redpoint请求 ===" << std::endl;
	//std::cout << "接收到的student_id: " << student_id.getValue(0) << std::endl;

	auto result = redService().getRed(student_id);

	//std::cout << "Service返回结果: "
	//    << "grade=" << result->grade_count
	//    << ", evaluate=" << result->evaluate_count
	//    << ", homework=" << result->homework_count << std::endl;
	//std::cout << "=== 结束处理redpoint请求 ===" << std::endl;

	// 包装响应结果
	auto jvo = redJsonVO::createShared();
	jvo->success(result);
	return jvo;
}