#pragma once
#ifndef _SELECTTEACHERDO_H_
#define _SELECTTEACHERDO_H_
#include "../DoInclude.h"

class SelectTeacherViewDO : public BaseDO
{
	//±àºÅ
	MYSQL_SYNTHESIZE(double, id, Id);
	//°à¼¶Ãû³Æ
	MYSQL_SYNTHESIZE(string,name, Name);
public:
	SelectTeacherViewDO() :BaseDO(std::string("")) {}
};
typedef std::shared_ptr<SelectTeacherViewDO> SelectTeacherViewDOPtr;


#endif

