
#include"stdafx.h"
#include"GettimeableController.h"
ScheduleTimeableJsonVO::Wrapper GettimeableController::executequerygettimeable(const ScheduleTimeableQuery::Wrapper & query)
{

	//// 调用ClassStudentService的listAll方法（适配class_student表查询）
	//auto result = ClassStudentService().listAll(query);
	//// 实例化ClassStudent分页VO（适配class_student表分页结果）
	//auto jvo = ClassStudentPageJsonVO::createShared();

	//// 封装成功响应（数据为class_student表的分页结果）
	//jvo->success(result);
	//return jvo;

	//创建一个响应结果
	auto vo = ScheduleTimeableJsonVO::createShared();
	vo->success("success");
	return vo;

}