#pragma once
#ifndef _PARENTINFO_SERVICE_
#define _PARENTINFO_SERVICE_
#include "domain/vo/parent/ParentInfoVO.h"
#include "domain/dto/parent/ParentInfoDTO.h"

class ParentInfoService {
public:
	ParentInfoDTO::Wrapper getParentInfo(const ParentInfoDTO::Wrapper& dto);
};

#endif // !_PARENTINFO_SERVICE_
