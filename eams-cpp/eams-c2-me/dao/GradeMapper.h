#pragma once
#include "Mapper.h"
#include "../domain/do/GradeDO.h"

/**
 * Ê¾Àı±í×Ö¶ÎÆ¥ÅäÓ³Éä
 */
class GradeMapper : public Mapper<GradeDO>
{
public:
    GradeDO mapper(ResultSet* resultSet) const override
    {
        GradeDO data;
        data.setName(resultSet->getString("name"));
        return data;
    }
};