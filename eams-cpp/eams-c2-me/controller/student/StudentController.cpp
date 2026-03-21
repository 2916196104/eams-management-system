#include "stdafx.h"
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