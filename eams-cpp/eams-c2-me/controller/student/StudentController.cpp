#include "stdafx.h"
#include "StudentController.h"
#include "./service/GradeService.h"


GradePageJsonVO::Wrapper StudentController::executeQueryGrade(const GradeQuery::Wrapper& query) {
	GradeService gs;
	auto vo = GradePageJsonVO::createShared();
	vo->success(gs.listAllGrade(query));
	return vo;
}

#include "./domain/vo/PointPageJsonVO.h"
#include "./domain/query/PointQuery.h"
#include "./service/PointService.h"
PointPageJsonVO::Wrapper StudentController::executeQueryPoint(const PointQuery::Wrapper & query)
{
	PointService ps;
	auto vo = PointPageJsonVO::createShared();
	vo->success(ps.listAll(query));
	return vo;
}


JsonVO<oatpp::Any>::Wrapper StudentController::executeSwitchStudent(int64_t id)
{
    return JsonVO<oatpp::Any>::createShared();
}
#include "StudentController.h"
#include "service/Student/StudentService.h"

JsonVO<oatpp::Any>::Wrapper StudentController::executeRemoveUser(const IdQuery::Wrapper& query)
{
    //只需要返回状态就行
    auto vo = JsonVO<oatpp::Any>::createShared();
    StudentService serv;
    //获取query中的id参数给serv，调用service的deleteStudent方法
    bool ok = serv.deleteStudent(query->id.getValue(0));
    if (ok)
        vo->success(nullptr);
    else
        vo->fail(nullptr);
    //根据逻辑值响应前端
    return vo;
}
#include "StudentController.h"


StudentPageJsonVO::Wrapper StudentController::executeQueryAll(const UserQuery::Wrapper& query)
{
	return StudentPageJsonVO::createShared();
}
