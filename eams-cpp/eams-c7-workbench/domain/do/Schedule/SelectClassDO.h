#pragma once
#ifndef _SELECTCLASSDO_H_
#define _SELECTCLASSDO_H_
#include "../DoInclude.h"

class SelectClassViewDO : public BaseDO
{
	//±àºÅ
	MYSQL_SYNTHESIZE(double, id, Id);
	//°à¼¶Ãû³Æ
	MYSQL_SYNTHESIZE(string,name, Name);
public:
	SelectClassViewDO() :BaseDO(std::string("")) {}
};
typedef std::shared_ptr<SelectClassViewDO> SelectClassViewDOPtr;


#endif

