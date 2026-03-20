#include "stdafx.h"
#include "StaffController.h"

StringJsonVO::Wrapper StaffController::executegetDutyRecord(const DutyRecordQueryDTO::Wrapper& query) {
    //创建一个相应结果
    auto vo = StringJsonVO::createShared();
    vo->success(ZH_WORDS_GETTER("getDutyRecord.resp"));
    return vo;
}