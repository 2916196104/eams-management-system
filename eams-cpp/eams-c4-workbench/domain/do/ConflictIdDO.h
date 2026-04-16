#pragma once 

#include "DoInclude.h"

class ConflictIdDO :public BaseDO {
	//³åÍ»id
	MYSQL_SYNTHESIZE(string, id, Id);
public:
	ConflictIdDO():BaseDO("lesson_schedule") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
	}
};

typedef shared_ptr<ConflictIdDO> PtrConflictIdDO;
