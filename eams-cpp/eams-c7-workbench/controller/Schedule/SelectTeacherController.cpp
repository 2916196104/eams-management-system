#include "stdafx.h"
#include "SelectTeacherController.h"

//StringJsonVO::Wrapper SelectTeacherController::executeQuerySelectTeacher(const PageQuery::Wrapper& query)
//{
//	auto vo = StringJsonVO::createShared();
//	vo->success(ZH_WORDS_GETTER("select_teacher.resp"));
//	return vo;
//}

SelectTeacherPageJsonVO::Wrapper SelectTeacherController::executeQueryTeacherPage(const SelectTeacherQuery::Wrapper& query)
{
	//auto vo = SelectClassPageJsonVO::createShared();
	//vo->success(String((ZH_WORDS_GETTER("select_class.resp"))));
	//return vo;
	return {};
}