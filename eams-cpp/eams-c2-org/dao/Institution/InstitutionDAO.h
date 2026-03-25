#pragma once
#include "BaseDAO.h"
#include "../../domain/do/Institution/InstitutionDO.h"

class InstitutionDAO : public BaseDAO {
public:
    std::list<PtrInstitutionDO> selectAllInstitutions();
};