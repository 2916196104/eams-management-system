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

#include "StudentController.h"
#include "service/student/StudentService.h"

//JsonVO<oatpp::Any>::Wrapper StudentController::executeRemoveUser(const IdQuery::Wrapper& query)
//{
//    //只需要返回状态就行
//    auto vo = JsonVO<oatpp::Any>::createShared();
//    StudentService serv;
//    //获取query中的id参数给serv，调用service的deleteStudent方法
//    bool ok = serv.deleteStudent(query->id.getValue(0));
//    if (ok)
//        vo->success(nullptr);
//    else
//        vo->fail(nullptr);
//    //根据逻辑值响应前端
//    return vo;
//}
#include "StudentController.h"
//#include "service/student/StudentService.h"
#include <cstdint>
#include <stdexcept>

// ========== 1. 查询学员列表实现 ==========
StudentPageJsonVO::Wrapper StudentController::executeQueryAll(const StudentQuery::Wrapper& query)
{
    StudentService serv;
    auto vo = StudentPageJsonVO::createShared();
    vo->success(serv.listAll(query));
    return vo;
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
// ========== 2. 删除学员实现 ==========
JsonVO<oatpp::Any>::Wrapper StudentController::executeRemoveUser(const IdQuery::Wrapper& query)
{
    auto vo = JsonVO<oatpp::Any>::createShared();
    StudentService serv;

    // 字符串ID转uint64_t
    std::string idStr = query->id->c_str();
    uint64_t targetId;

    try {
        targetId = (uint64_t)std::stoll(idStr);
    }
    catch (const std::invalid_argument&) {
        vo->fail(nullptr);
        return vo;
    }
    catch (const std::out_of_range&) {
        vo->fail(nullptr);
        return vo;
    }

    bool ok = serv.deleteStudent(targetId);
    ok ? vo->success(nullptr) : vo->fail(nullptr);
    return vo;
}

// ========== 3. 切换学员实现 ==========
JsonVO<oatpp::Any>::Wrapper StudentController::executeSwitchStudent(const IdQuery::Wrapper& query)
{
    auto vo = JsonVO<oatpp::Any>::createShared();
    StudentService serv;

    // 字符串ID转uint64_t
    std::string idStr = query->id->c_str();
    uint64_t targetId;

    try {
        targetId = std::stoull(idStr);
    }
    catch (...) {
        vo->fail(nullptr);
        return vo;
    }

    bool exists = serv.findById(targetId);
    exists ? vo->success(nullptr) : vo->fail(nullptr);
    return vo;
}