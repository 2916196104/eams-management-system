#include "stdafx.h"
#include "Macros.h"
#include "ParentController.h"
#include "domain/vo/ParentVO.h"
#include "service/UsageGuideService.h"
using namespace std;

UsageGuideJsonVO::Wrapper ParentController:: executeQueryAll(const ListQuery::Wrapper& query)
{
	auto vo = UsageGuideJsonVO::createShared();
	UsageGuideService service;
	auto listData = service.listAll(query);
	vo->success(std::move(listData));
	return vo;
}

UsageDeatailJsonVO::Wrapper ParentController::executeQueryOne(const String& id)
{
	auto vo = UsageDeatailJsonVO::createShared();
	UsageGuideService service;
	auto pageData = service.getById(id);
	vo->success(pageData);
	return vo;
}



//UsageGuidePageDto::Wrapper  getList(const PageQuery::Wrapper& query)
//{
//	// 创建一个响应结果
//	auto vo = UsageGuidePageDto::createShared();
//	// vo->success("操作成功"); 代码里面有中文错误写法有中文从中文词典中读取
//	//vo->success(ZH_WORDS_GETTER("test.resp"));
//	return vo;
//}
//
//UsageGuideDetailDto::Wrapper  getDetail(const PageQuery::Wrapper& query)
//{
//	// 创建一个响应结果
//	auto vo = UsageGuideDetailDto::createShared();
//	// vo->success("操作成功"); 代码里面有中文错误写法有中文从中文词典中读取
//	//vo->success(ZH_WORDS_GETTER("test.resp"));
//	return vo;
//}