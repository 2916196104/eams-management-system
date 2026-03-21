#include "stdafx.h"
#include "PostStudentInfo.h"

StringJsonVO::Wrapper PostStudentInfoController::executeCreateStudent(const AddStudentDTO::Wrapper& studentDto) {
    auto vo = StringJsonVO::createShared();
    vo->success(ZH_WORDS_GETTER("translation.resp"));
    return vo;
}