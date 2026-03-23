#ifndef _CUSTOMER_DO_
#define _CUSTOMER_DO_
#include "../DoInclude.h"

/**********************************************************************/
/* 当前DO（DTO）中的类型可以对应不上数据库中对应字段的类型，先暂且搁置       */
/**********************************************************************/
class CustomerDO : public BaseDO {
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 电话号码
	MYSQL_SYNTHESIZE(string, phone, Phone);
public:
	CustomerDO() : BaseDO("student") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("phone", "s", phone);
	}
};

class CustomerDetailDO : public BaseDO {
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 手机号码
	MYSQL_SYNTHESIZE(string, phone, Phone);
	// 性别
	MYSQL_SYNTHESIZE(string, sex, Sex);
	// 年龄（不能直接查到）
	// MYSQL_SYNTHESIZE(uint16_t, age, Age);
	// 生日
	MYSQL_SYNTHESIZE(string, birth, Birth);
	// 类型
	MYSQL_SYNTHESIZE(string, type, Type);
	// 备注
	MYSQL_SYNTHESIZE(string, note, Note);
public:
	CustomerDetailDO() : BaseDO("student") {
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("phone", "s", phone);
		MYSQL_ADD_FIELD("sex", "s", sex);
		// 这里使用"i"作为占位符，可能有一定问题
		// MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("birth", "s", birth);
		MYSQL_ADD_FIELD("type", "s", type);
		MYSQL_ADD_FIELD("note", "s", note);
	}
};

class CustomerLessonDO : public BaseDO {
	// 课程名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 学习进度（已经上了的次数和总次数）
	MYSQL_SYNTHESIZE(string, count, Count);
	MYSQL_SYNTHESIZE(string, total, Total);
	// 有效期（课程添加时间和时限）
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	MYSQL_SYNTHESIZE(string, expire_month, Expire_month);
	// 剩余次数（总次数-已经上了的次数）
public:
	CustomerLessonDO() : BaseDO("course") {
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("count", "s", count);
		MYSQL_ADD_FIELD("total", "s", total);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("expire_month", "s", expire_month);
	}
};

#endif
