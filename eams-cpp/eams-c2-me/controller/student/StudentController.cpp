#include "stdafx.h"
#include "StudentController.h"
#include "service/Student/StudentService.h"
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