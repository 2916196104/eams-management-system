#include "InstitutionController.h"

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