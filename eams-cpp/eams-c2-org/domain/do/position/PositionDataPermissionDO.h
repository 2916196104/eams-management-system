// domain/do/position/PositionDataPermissionDO.h
#pragma once
#include <string>

class PositionDataPermissionDO {
public:
    int id;
    int positionId;
    std::string dataTableName;
    std::string dataScopeType;
    std::string dataTableCode;
    std::string dataOwnerField;
    std::string dataOrgField;
};