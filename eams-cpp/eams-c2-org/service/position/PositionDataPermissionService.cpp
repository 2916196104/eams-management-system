#include "stdafx.h"
#include "PositionDataPermissionService.h"
#include "../../domain/do/position/PositionDataPermissionDO.h"
#include "../../domain/dto/position/DataPermissionItemDTO.h"

PositionDataPermissionService::PositionDataPermissionService(std::unique_ptr<PositionDataPermissionDao> dao)
    : m_dao(std::move(dao)) {
}

oatpp::Object<PositionDataPermissionPageDTO> PositionDataPermissionService::getListByPositionId(int positionId, int page, int size) {
    if (page < 1) page = 1;
    if (size < 1) size = 30;
    int offset = (page - 1) * size;

    int64_t total = m_dao->countByPositionId(positionId);
    auto doList = m_dao->selectByPositionId(positionId, offset, size);

    auto pageResult = PositionDataPermissionPageDTO::createShared();
    pageResult->total = total;

    auto list = oatpp::Vector<oatpp::Object<DataPermissionItemDTO>>::createShared();
    for (const auto& item : doList) {
        auto dto = DataPermissionItemDTO::createShared();
        dto->id = item.id;
        dto->dataTableName = item.dataTableName.c_str();
        dto->dataScopeType = item.dataScopeType.c_str();
        dto->dataTableCode = item.dataTableCode.c_str();
        dto->dataOwnerField = item.dataOwnerField.c_str();
        dto->dataOrgField = item.dataOrgField.c_str();
        list->push_back(dto);
    }
    pageResult->list = list;
    return pageResult;
}