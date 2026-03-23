#ifndef _CLASSROOM_DO_
#define _CLASSROOM_DO_
#include "../DoInclude.h"

/**********************************************************************/
/* 当前DO（DTO）中的类型可以对应不上数据库中对应字段的类型，先暂且搁置       */
/**********************************************************************/

class ClassroomDO : public BaseDO {
	// id
	MYSQL_SYNTHESIZE(string, id, Id);
	// 教室名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 地点
	MYSQL_SYNTHESIZE(string, pos, Pos);
public:
	ClassroomDO() : BaseDO("classroom") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("pos", "s", pos);
	}
};

#endif
