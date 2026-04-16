#ifndef _COURSE_DO_
#define _COURSE_DO_
#include "DoInclude.h"

class CourseDO : public BaseDO {
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 科目id
	MYSQL_SYNTHESIZE(string, subject_id, Subject_id);
	// 课程名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 启用状态
	MYSQL_SYNTHESIZE(int, state, State);
	// 提示信息
	MYSQL_SYNTHESIZE(string, info, Info);
	// 创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	// 编辑者
	MYSQL_SYNTHESIZE(string, editor, Editor);
	// 添加时间
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	// 修改时间
	MYSQL_SYNTHESIZE(string, edit_time, Edit_time);
	// 有效期月数
	MYSQL_SYNTHESIZE(int, expire_months, Expire_months);
	// 单价
	MYSQL_SYNTHESIZE(string, unit_price, Unit_price);
	// 总价 销售价
	MYSQL_SYNTHESIZE(string, price, Price);
	// 单位名称
	MYSQL_SYNTHESIZE(string, unit_name, Unit_name);
	// 优惠金额
	MYSQL_SYNTHESIZE(string, discount, Discount);
	// 课次数
	MYSQL_SYNTHESIZE(int, lesson_count, Lesson_count);
	// 课堂类型1大课2小班课31v1
	MYSQL_SYNTHESIZE(int, lesson_type, Lesson_type);
	// 描述
	MYSQL_SYNTHESIZE(string, description, Description);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 是否可以预约
	MYSQL_SYNTHESIZE(int, bookable, Bookable);
	// 是否上架中
	MYSQL_SYNTHESIZE(int, for_sale, For_sale);
	// 是否推荐
	MYSQL_SYNTHESIZE(int, recommend, Recommend);
	// 封面
	MYSQL_SYNTHESIZE(string, cover, Cover);
	// 报名截止日期
	MYSQL_SYNTHESIZE(string, close_date, Close_date);
	// 师资信息
	MYSQL_SYNTHESIZE(string, teacher_info, Teacher_info);
	// 服务说明
	MYSQL_SYNTHESIZE(string, service_info, Service_info);
	// 库存名额
	MYSQL_SYNTHESIZE(int, storage, Storage);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(string, org_id, Org_id);
	// 消课课酬(元/课)
	MYSQL_SYNTHESIZE(string, salary, Salary);
	// 适用年级
	MYSQL_SYNTHESIZE(string, grade_ids, Grade_ids);
	// 适用年级名
	MYSQL_SYNTHESIZE(string, grade_names, Grade_names);

public:
	CourseDO() : BaseDO("course") {
		// 主键
		MYSQL_ADD_FIELD_PK("id", "s", id);
		// 科目id
		MYSQL_ADD_FIELD("subject_id", "s", subject_id);
		// 课程名
		MYSQL_ADD_FIELD("name", "s", name);
		// 启用状态
		MYSQL_ADD_FIELD("state", "i", state);
		// 提示信息
		MYSQL_ADD_FIELD("info", "s", info);
		// 创建人
		MYSQL_ADD_FIELD("creator", "s", creator);
		// 编辑者
		MYSQL_ADD_FIELD("editor", "s", editor);
		// 添加时间
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		// 修改时间
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		// 有效期月数
		MYSQL_ADD_FIELD("expire_months", "i", expire_months);
		// 单价
		MYSQL_ADD_FIELD("unit_price", "s", unit_price);
		// 总价 销售价
		MYSQL_ADD_FIELD("price", "s", price);
		// 单位名称
		MYSQL_ADD_FIELD("unit_name", "s", unit_name);
		// 优惠金额
		MYSQL_ADD_FIELD("discount", "s", discount);
		// 课次数
		MYSQL_ADD_FIELD("lesson_count", "i", lesson_count);
		// 课堂类型
		MYSQL_ADD_FIELD("lesson_type", "i", lesson_type);
		// 描述
		MYSQL_ADD_FIELD("description", "s", description);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 是否可以预约
		MYSQL_ADD_FIELD("bookable", "i", bookable);
		// 是否上架中
		MYSQL_ADD_FIELD("for_sale", "i", for_sale);
		// 是否推荐
		MYSQL_ADD_FIELD("recommend", "i", recommend);
		// 封面
		MYSQL_ADD_FIELD("cover", "s", cover);
		// 报名截止日期
		MYSQL_ADD_FIELD("close_date", "s", close_date);
		// 师资信息
		MYSQL_ADD_FIELD("teacher_info", "s", teacher_info);
		// 服务说明
		MYSQL_ADD_FIELD("service_info", "s", service_info);
		// 库存名额
		MYSQL_ADD_FIELD("storage", "i", storage);
		// 创建者所属组织ID
		MYSQL_ADD_FIELD("org_id", "s", org_id);
		// 消课课酬(元/课)
		MYSQL_ADD_FIELD("salary", "s", salary);
		// 适用年级
		MYSQL_ADD_FIELD("grade_ids", "s", grade_ids);
		// 适用年级名
		MYSQL_ADD_FIELD("grade_names", "s", grade_names);
	}
};

typedef std::shared_ptr<CourseDO> PtrCourseDO;

#endif