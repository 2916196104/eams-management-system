#include "InstitutionController.h"
#include "../../service/InstitutionService.h"

InstitutionController::TreeResultVO InstitutionController::execQueryTree() {
    auto jvo = ListJsonVO<InstitutionDTO::Wrapper>::createShared();

    // 呼叫 Service 层干活
    InstitutionService service;
    auto treeList = service.getTree();

    jvo->success(treeList);
    return jvo;
}

StringJsonVO::Wrapper InstitutionController::execSaveInstitution(const InstitutionDTO::Wrapper& dto, const PayloadDTO& payload) {
    auto jvo = StringJsonVO::createShared();

    if (!dto->name || dto->name->empty()) {
        jvo->fail("save failed: institution name can't be empty");
        return jvo;
    }

    // 提取操作人 ID，呼叫 Service 层干活
    oatpp::String operatorId = payload.getId();

    InstitutionService service;
    auto res = service.saveInstitution(dto, operatorId);

    if (res && res != "") {
        jvo->success("save successful");
    }
    else {
        jvo->fail("save failed: internal error");
    }

    return jvo;
}