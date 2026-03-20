#include "stdafx.h"
#include "ParentController.h"

<<<<<<< Updated upstream
ParentJsonVO::Wrapper ParentController::execQueryOne(const oatpp::UInt64& phone) {
=======
ParentJsonVO::Wrapper ParentController::execQueryInfo(const ParentDTO::Wrapper &dto) {
  return {};
}

ParentJsonVO::Wrapper ParentController::execModifyName(const ParentDTO::Wrapper& dto, const PayloadDTO& payload)
{
  return {};
}

ParentJsonVO::Wrapper ParentController::execModifyPassword(const ParentDTO::Wrapper& dto)
{
>>>>>>> Stashed changes
  return {};
}
