#pragma once
#include "../../domain/do/Institution/InstitutionDO.h"
#include "Mapper.h" // 引入你们框架的 Mapper 基类

class PtrInstitutionMapper : public Mapper<PtrInstitutionDO> {
public:
    PtrInstitutionDO mapper(ResultSet* resultSet) const override {
        auto data = std::make_shared<InstitutionDO>();
        // 索引从 1 开始
        data->setId(resultSet->getUInt64(1));
        data->setName(resultSet->getString(2));
        data->setPid(resultSet->getUInt64(3));
        return data;
    }
};