#pragma once
#ifndef _COURSE_DO_
#define _COURSE_DO_
#include "../DoInclude.h"

/**
 * 课程套餐表数据库实体类
 * 对应表: course
 */
class CourseDO : public BaseDO
{
	// 主键 (bigint unsigned)
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 科目ID (bigint)
	MYSQL_SYNTHESIZE(uint64_t, subjectId, SubjectId);
	// 课程名 (varchar)
	MYSQL_SYNTHESIZE(string, name, Name);
	// 状态 (tinyint)
	MYSQL_SYNTHESIZE(int, state, State);
	// 提示信息 (varchar)
	MYSQL_SYNTHESIZE(string, info, Info);
	// 创建人 (bigint)
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑者 (bigint)
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 添加时间 (datetime)
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 修改时间 (datetime)
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 有效期月数 (tinyint unsigned)
	MYSQL_SYNTHESIZE(int, expireMonths, ExpireMonths);
	// 单价 (decimal)
	MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);
	// 总价/销售价 (decimal)
	MYSQL_SYNTHESIZE(double, price, Price);
	// 单位名称 (varchar)
	MYSQL_SYNTHESIZE(string, unitName, UnitName);
	// 优惠金额 (decimal)
	MYSQL_SYNTHESIZE(double, discount, Discount);
	// 课次数 (int unsigned)
	MYSQL_SYNTHESIZE(int, lessonCount, LessonCount);
	// 课堂类型 (tinyint)
	MYSQL_SYNTHESIZE(int, lessonType, LessonType);
	// 描述 (text)
	MYSQL_SYNTHESIZE(string, description, Description);
	// 删除标记 (tinyint)
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 是否可以预约 (tinyint)
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	// 是否上架中 (tinyint)
	MYSQL_SYNTHESIZE(int, forSale, ForSale);
	// 是否推荐 (tinyint)
	MYSQL_SYNTHESIZE(int, recommend, Recommend);
	// 封面 (varchar)
	MYSQL_SYNTHESIZE(string, cover, Cover);
	// 报名截止日期 (date)
	MYSQL_SYNTHESIZE(string, closeDate, CloseDate);
	// 师资信息 (varchar)
	MYSQL_SYNTHESIZE(string, teacherInfo, TeacherInfo);
	// 服务说明 (varchar)
	MYSQL_SYNTHESIZE(string, serviceInfo, ServiceInfo);
	// 库存名额 (int)
	MYSQL_SYNTHESIZE(int, storage, Storage);
	// 所属组织ID (bigint)
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
	// 消课课酬 (decimal)
	MYSQL_SYNTHESIZE(double, salary, Salary);
	// 适用年级ID集合 (varchar)
	MYSQL_SYNTHESIZE(string, gradeIds, GradeIds);
	// 适用年级名集合 (varchar)
	MYSQL_SYNTHESIZE(string, gradeNames, GradeNames);

public:
	CourseDO() : BaseDO("course")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("subject_id", "ull", subjectId);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("creator", "ull", creator);
		MYSQL_ADD_FIELD("editor", "ull", editor);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("expire_months", "i", expireMonths);
		MYSQL_ADD_FIELD("unit_price", "d", unitPrice);
		MYSQL_ADD_FIELD("price", "d", price);
		MYSQL_ADD_FIELD("unit_name", "s", unitName);
		MYSQL_ADD_FIELD("discount", "d", discount);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("lesson_type", "i", lessonType);
		MYSQL_ADD_FIELD("description", "s", description);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("bookable", "i", bookable);
		MYSQL_ADD_FIELD("for_sale", "i", forSale);
		MYSQL_ADD_FIELD("recommend", "i", recommend);
		MYSQL_ADD_FIELD("cover", "s", cover);
		MYSQL_ADD_FIELD("close_date", "s", closeDate);
		MYSQL_ADD_FIELD("teacher_info", "s", teacherInfo);
		MYSQL_ADD_FIELD("service_info", "s", serviceInfo);
		MYSQL_ADD_FIELD("storage", "i", storage);
		MYSQL_ADD_FIELD("org_id", "ull", orgId);
		MYSQL_ADD_FIELD("salary", "d", salary);
		MYSQL_ADD_FIELD("grade_ids", "s", gradeIds);
		MYSQL_ADD_FIELD("grade_names", "s", gradeNames);
	}
};

// 给CourseDO智能指针设定一个别名
typedef std::shared_ptr<CourseDO> PtrCourseDO;

#endif // !_COURSE_DO_