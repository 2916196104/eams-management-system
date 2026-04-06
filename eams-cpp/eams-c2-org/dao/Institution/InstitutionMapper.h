#pragma once
#include "../../domain/do/Institution/InstitutionDO.h"
#include "Mapper.h" // 引入你们框架的 Mapper 基类

class PtrInstitutionMapper : public Mapper<PtrInstitutionDO> {
public:
    PtrInstitutionDO mapper(ResultSet* resultSet) const override {
        auto data = std::make_shared<InstitutionDO>();
        data->setId(resultSet->getUInt64("id"));
        data->setName(resultSet->getString("name"));
        data->setPid(resultSet->getUInt64("pid"));
        data->setLevel(resultSet->getInt("level"));
        data->setShortname(resultSet->getString("shortname"));
        data->setContactName(resultSet->getString("contact_name"));
        data->setPhone(resultSet->getString("phone"));
        data->setFax(resultSet->getString("fax"));
        data->setEmail(resultSet->getString("email"));
        data->setSortNum(resultSet->getInt("sort_num"));
        data->setState(resultSet->getInt("state"));
        data->setInfo(resultSet->getString("info"));
        return data;
    }
};