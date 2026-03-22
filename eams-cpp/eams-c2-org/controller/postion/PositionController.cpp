#include "stdafx.h"
#include "PositionController.h"
#include "domain/dto/postion/PermissionDTO.h"
#include "domain/dto/postion/PositionDataDTO.h"
#include "domain/dto/postion/PositionDataPermissionQueryDTO.h"
#include "domain/dto/postion/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include "domain/dto/postion/DeletePositionRequestDTO.h"
#include "domain/dto/postion/JsonResponseDTO.h"
#include "domain/dto/postion/EmptyDTO.h"

using namespace oatpp::web::protocol::http;
std::shared_ptr<PositionController::OutgoingResponse> PositionController::getPositionDataPermissionList(
    const oatpp::Object<PositionDataPermissionQueryDTO>& request) {

    // 模拟数据（实际应从数据库查询）
    auto pageResult = PositionDataPermissionPageDTO::createShared();
    pageResult->total = 7;  // 共7条

    auto list = oatpp::Vector<oatpp::Object<DataPermissionItemDTO>>::createShared();

    // 模拟第1条
    auto item1 = DataPermissionItemDTO::createShared();
    item1->id = 1;
    item1->dataTableName = "员工数据";
    item1->dataScopeType = "本校数据";
    item1->dataTableCode = "staff";
    item1->dataOwnerField = "id";
    item1->dataOrgField = "";
    list->push_back(item1);

    // 模拟第2条（重复项可以多条）
    auto item2 = DataPermissionItemDTO::createShared();
    item2->id = 2;
    item2->dataTableName = "员工账号表(a)";
    item2->dataScopeType = "本校数据";
    item2->dataTableCode = "staff";
    item2->dataOwnerField = "creator";
    item2->dataOrgField = "org_id";
    list->push_back(item2);

    // ... 可以继续添加模拟数据直到7条

    pageResult->list = list;

    // 构建统一响应
    auto response = JsonVO<oatpp::Object<PositionDataPermissionPageDTO>>::createShared();
    response->code = 0;
    response->message = "";
    response->data = pageResult;

    return createDtoResponse(Status::CODE_200, response);
}

// 新增：批量删除职位接口
std::shared_ptr<PositionController::OutgoingResponse> PositionController::deletePositions(
    const oatpp::Object<DeletePositionRequestDTO>& request) {

    // 校验 ids 不能为空
    if (!request->ids || request->ids->empty()) {
        auto error = JsonResponseDTO<oatpp::Object<EmptyDTO>>::createShared();
        error->errCode = 400;
        error->msg = "ids 不能为空";
        error->data = EmptyDTO::createShared();
        return createDtoResponse(Status::CODE_400, error);
    }

    // TODO: 调用 Service 执行批量删除（例如 positionService->deleteByIds(ids)）
    // 目前返回模拟成功响应
    auto response = JsonResponseDTO<oatpp::Object<EmptyDTO>>::createShared();
    response->errCode = 0;
    response->msg = "";
    response->data = EmptyDTO::createShared();

    return createDtoResponse(Status::CODE_200, response);
}
