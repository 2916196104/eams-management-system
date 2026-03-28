#include "stdafx.h"
#include "Message.h"
#include "ResultStatus.h"
#include "domain/dto/position/PositionDTO.h"
#include "PositionController.h"
#include "service/position/PositionService.h"
#include "domain/dto/position/PermissionDTO.h"
#include "domain/dto/position/PositionDataDTO.h"
#include "domain/dto/position/PositionDataPermissionQueryDTO.h"
#include "domain/dto/position/PositionDataPermissionPageDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/position/DeletePositionRequestDTO.h"
#include "domain/dto/position/JsonResponseDTO.h"
#include "domain/dto/position/EmptyDTO.h"

using namespace oatpp::web::protocol::http;

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::fetchPositionAll(const std::shared_ptr<CustomerAuthorizeObject>& auth) {

    PositionService ser;

    auto vo = ALLPositionsVO::createShared();

    auto data = ser.fetchAllPosition();
    if (data->empty()) {
        vo->init(data, RS_SERVER_BUSY);
    }
    else
        vo->init(data, RS_SUCCESS);

    return createDtoResponse(Status::CODE_200, vo);
};

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::fetchPositionList(const std::shared_ptr<CustomerAuthorizeObject>& auth, const Int32& pageNum,
    const Int32& pageSize,
    const String& keyWord) {

    PositionService ser;

    auto vo = PositionListVO::createShared();
    auto empty = oatpp::Vector<PositionItemDTO::Wrapper>::createShared();

    auto page = pageNum.getValue(1);
    auto limit = pageSize.getValue(10);
    if (page <= 0 || limit <= 0) {
        vo->page = page;
        vo->limit = limit;
        vo->total = 0;
        vo->totalPages = 0;
        vo->init(empty, RS_PARAMS_INVALID);
        return createDtoResponse(Status::CODE_200, vo);
    }

    auto result = ser.pageQueryPosition(pageNum, pageSize, keyWord);

    vo->page = page;
    vo->limit = limit;
    vo->total = result.total;
    vo->totalPages = result.totalPages;
    vo->init(result.data, RS_SUCCESS);

    return createDtoResponse(Status::CODE_200, vo);
};

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::savePosition(const std::shared_ptr<CustomerAuthorizeObject>& auth, const PositionSaveRequestDTO::Wrapper& dto) {

    PositionService ser;

    auto vo = JsonVO<oatpp::Int64>::createShared();
    int64_t id = 0;
    if (!dto || !dto->name || dto->name->empty() || (dto->id && dto->id <= 0)) {
        vo->init(oatpp::Int64(id), RS_PARAMS_INVALID);
        return createDtoResponse(Status::CODE_200, vo);
    }

    id = ser.savePosition(dto);
    if (id < 0) {
        vo->init(oatpp::Int64(id), RS_SERVER_BUSY);
    }
    else {
        vo->init(oatpp::Int64(id), RS_SUCCESS);
    }

    return createDtoResponse(Status::CODE_200, vo);
}

// ==================== 获取职位数据权限列表 ====================
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

    // 模拟第2条
    auto item2 = DataPermissionItemDTO::createShared();
    item2->id = 2;
    item2->dataTableName = "员工账号表(a)";
    item2->dataScopeType = "本校数据";
    item2->dataTableCode = "staff";
    item2->dataOwnerField = "creator";
    item2->dataOrgField = "org_id";
    list->push_back(item2);

    pageResult->list = list;

    auto response = JsonVO<oatpp::Object<PositionDataPermissionPageDTO>>::createShared();
    response->code = 0;
    response->message = "";
    response->data = pageResult;

    return createDtoResponse(Status::CODE_200, response);
}

// ==================== 批量删除职位 ====================
std::shared_ptr<PositionController::OutgoingResponse> PositionController::deletePositions(
    const oatpp::Object<DeletePositionRequestDTO>& request) {

    if (!request->ids || request->ids->empty()) {
        auto error = JsonResponseDTO<oatpp::Object<EmptyDTO>>::createShared();
        error->errCode = 400;
        error->msg = "ids 不能为空";
        error->data = EmptyDTO::createShared();
        return createDtoResponse(Status::CODE_400, error);
    }

    std::vector<int64_t> ids;
    for (auto& id : *request->ids) {
        ids.push_back(id);
    }

    PositionService ser;
    bool success = ser.deletePositions(ids);

    auto response = JsonResponseDTO<oatpp::Object<EmptyDTO>>::createShared();
    response->errCode = success ? 0 : 500;
    response->msg = success ? "" : "删除失败";
    response->data = EmptyDTO::createShared();
    return createDtoResponse(Status::CODE_200, response);
}