#include "stdafx.h"
#include "PostStudentInfoController.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"
#include "PdfComponent.h"
#include "../../service/AddStudent/StudentInfoService.h"
#include "../ApiDeclarativeServicesHelper.h"

StringJsonVO::Wrapper PostStudentInfoController::execAddStudent(const AddStudentDTO::Wrapper& studentDto, const PayloadDTO& payload) {
    //定义返回数据对象
    auto jvo = StringJsonVO::createShared();

    //参数校验
    std::string errmsg = studentDto->validate();

    if (errmsg != "") {
        jvo->init(errmsg, RS_PARAMS_INVALID);
        return jvo;
    }

    //执行数据自增
    studentDto->setPayload(&payload);
    std::string id = StudentInfoService().saveStudentInfo(studentDto);
    if (id != "") {
        jvo->success(id);
    }
    else {
        jvo->fail("");
    }

    return jvo;
}