#pragma once
#ifndef _CLASSROOMDO_H_
#define _CLASSROOMDO_H_

#include "../DoInclude.h"

class ClassroomDO : public BaseDO
{
	//主键字段
	MYSQL_SYNTHESIZE(int, id, Id);
	//教室名称
	MYSQL_SYNTHESIZE(string, clsname, ClsName);
	//教室地址
	MYSQL_SYNTHESIZE(string, clsaddress, ClsAddress);

public:
	ClassroomDO() : BaseDO("classroom")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", clsname);
		MYSQL_ADD_FIELD("address", "s", clsaddress);
	}
};

//定义一个点名记录实体的智能指针
typedef std::shared_ptr<ClassroomDO> PtrClassroomDO;


#endif 