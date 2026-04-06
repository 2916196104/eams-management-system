#include "stdafx.h"
#include "StudentController.h"
#include "./service/GradeService.h"


GradeListJsonVO::Wrapper StudentController::executeQueryGrade() {
	
	GradeService gs;
	auto vo = GradeListJsonVO::createShared();
	vo->success(gs.listAllGrade());
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
#include "StudentController.h"

//======================接口1获取用户详细信息接口执行函数定义========================//
StringJsonVO::Wrapper StudentController::executeQueryOne(const String& id)
{
    ////UserService us;
    auto jvo = StringJsonVO::createShared();
    ////auto data = us.getUserDetail(id);
    ////if (data)
    ////    jvo->success(data);
    ////else
    ////    jvo->fail({});
    return jvo;

    // 模拟纯文本响应
    //return createResponse(Status::CODE_200, "Hello, World!");
}

//==========================接口2 新增用户信息接口执行函数定义========================//
//StringJsonVO::Wrapper StudentController::executeAddStudnet(const StudentAddDTO::Wrapper& dto)
StringJsonVO::Wrapper StudentController::executeAddStudent(const StudentAddDTO::Wrapper& dto)
{
    //UserService us;
    auto jvo = StringJsonVO::createShared();
    //auto id = us.saveUser(dto);
    //if (id != "")
    //    jvo->success(id);
    //else
    //    jvo->fail({});
    return jvo;
}