#pragma once
#include <memory>
#include "../../domain/dto/position/PositionDataPermissionPageDTO.h"
#include "../../dao/position/PositionDataPermissionDao.h"

class PositionDataPermissionService {
public:
    explicit PositionDataPermissionService(std::unique_ptr<PositionDataPermissionDao> dao);
    oatpp::Object<PositionDataPermissionPageDTO> getListByPositionId(int positionId, int page, int size);
private:
    std::unique_ptr<PositionDataPermissionDao> m_dao;
};