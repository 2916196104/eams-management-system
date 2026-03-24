#include "stdafx.h"
#include "bulletinController.h"
#include"../../service/bulletin/bulletinService.h"
//实现接口执行函数

titleJsonVO::Wrapper bulletinController::executeQueryTitle()
{
	//return {};


	// 调用Service层获取最新公告
	auto result = bulletinService().getLatest();

	// 包装响应结果
	auto jvo = titleJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

listPageJsonVO::Wrapper bulletinController::executeQueryList(const PageQuery::Wrapper& query)
{

	//return {};
	auto result = bulletinService().listAll(query);

	// 包装响应结果
	auto jvo = listPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}

redJsonVO::Wrapper bulletinController::executeQueryRed(const Int64& student_id)
{
	//return {};
	// 调用Service层获取未读数
	auto result = redService().getRed(student_id);

	 //包装响应结果
	auto jvo = redJsonVO::createShared();
	jvo->success(result);
	return jvo;
}