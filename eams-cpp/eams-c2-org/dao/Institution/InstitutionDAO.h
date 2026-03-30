#pragma once
#include "BaseDAO.h"
#include "../../domain/do/Institution/InstitutionDO.h"
#include <vector>


class InstitutionDAO : public BaseDAO {
public:
    int insert(const InstitutionDO& data);
    int update(const InstitutionDO& data);
    std::list<PtrInstitutionDO> selectAllInstitutions();
};