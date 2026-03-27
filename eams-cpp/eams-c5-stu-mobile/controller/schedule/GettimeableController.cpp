
#include"stdafx.h"
#include"GettimeableController.h"
#include "../../service/schedule/GettimeableService.h"
GetTimeablePageJsonVO::Wrapper GettimeableController::executequerygettimeable(const GetTimeableQuery::Wrapper & query)
{

	// 调用ClassStudentService的listAll方法（适配class_student表查询）
	//查询数据
	auto result = GettimeableService().listAll(query);

	// 实例化ClassStudent分页VO（适配class_student表分页结果）
	//响应结果
	auto jvo = GetTimeablePageJsonVO::createShared();

	// 封装成功响应（数据为class_student表的分页结果）
	jvo->success(result);
	return jvo;

	/*创建一个响应结果
	auto vo = ScheduleTimeableJsonVO::createShared();
	vo->success("success");
	return vo;*/

}
//StringJsonVO::Wrapper GettimeableController::executeQueryTest(const PageQuery::Wrapper& query)
//{
//	// 创建一个响应结果
//	auto vo = StringJsonVO::createShared();
//	// vo->success("操作成功"); 代码里面有中文错误写法有中文从中文词典中读取
//	vo->success(ZH_WORDS_GETTER("test.resp"));
//	return vo;
//}

