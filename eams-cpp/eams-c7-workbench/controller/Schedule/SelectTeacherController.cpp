#include "stdafx.h"
#include "SelectTeacherController.h"
#include "../../service/Schedule/SelectTeacherService.h"

//StringJsonVO::Wrapper SelectTeacherController::executeQuerySelectTeacher(const PageQuery::Wrapper& query)
//{
//	auto vo = StringJsonVO::createShared();
//	vo->success(ZH_WORDS_GETTER("select_teacher.resp"));
//	return vo;
//}

SelectTeacherPageJsonVO::Wrapper SelectTeacherController::executeQueryTeacherPage(const SelectTeacherQuery::Wrapper& query)
{
	// 查询数据
	auto result = SelectTeacherService().listAll(query);
	// 响应结果
	auto jvo = SelectTeacherPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}