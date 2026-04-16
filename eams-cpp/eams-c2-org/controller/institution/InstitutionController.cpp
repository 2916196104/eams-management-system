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

StringJsonVO::Wrapper InstitutionController::execQueryInstitutionList()
{
    auto jvo = StringJsonVO::createShared();
    jvo->success(ZH_WORDS_GETTER("institution.list.tips"));
    return jvo;
}

StringJsonVO::Wrapper InstitutionController::execQueryInstitutionDetail(const Int64& id)
{
    auto jvo = StringJsonVO::createShared();
    std::string msg = std::string(ZH_WORDS_GETTER("institution.detail.tips")) + ": " + std::to_string(id);
    jvo->success(msg);
    return jvo;
}

BooleanJsonVO::Wrapper InstitutionController::execDeleteInstitution(const String& id)
{
    auto jvo = BooleanJsonVO::createShared();
    jvo->success(true);
    jvo->message = ZH_WORDS_GETTER("institution.delete.tips");
    return jvo;
}