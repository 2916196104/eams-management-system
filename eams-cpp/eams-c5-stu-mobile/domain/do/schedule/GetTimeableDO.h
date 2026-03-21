#pragma once
#ifndef _TIMEABLE_DO_
#define _TIMEABLE_DO_
#include "../DoInclude.h"

/**
 * 示例数据库实体类
 */
//还需要改数据库的表
class GetTimeableDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);               // 课程记录ID（必要，唯一标识）
	MYSQL_SYNTHESIZE(string, title, Title);         // 课程标题（核心：课名）
	MYSQL_SYNTHESIZE(int, sn, Sn);                  // 课节数（第几节课）
	MYSQL_SYNTHESIZE(string, date, Date);           // 上课日期（核心：当天日期过滤）
	MYSQL_SYNTHESIZE(string, start_time, Start_time); // 开始时间（核心：上课时间）
	MYSQL_SYNTHESIZE(string, end_time, End_time);   // 结束时间（核心：上课时间）
	MYSQL_SYNTHESIZE(int, teacher_id, Teacher_id);  // 主讲人ID（关联教师姓名）
	MYSQL_SYNTHESIZE(int, schedule_id, Schedule_id); // 编排计划ID（关联星期几）
	// 补充：若需要直接存储教师姓名/签到状态，可新增以下字段（根据实际查询需求）
	MYSQL_SYNTHESIZE(string, teacher_name, TeacherName); // 教师姓名（直接存储，无需关联）
	MYSQL_SYNTHESIZE(int, sign_state, SignState);         // 签到状态（从lesson_student关联）




	// 
	// 
	// 编号不清楚有些是什么类型
	//MYSQL_SYNTHESIZE(string, id, Id);
	////课程标题
	//MYSQL_SYNTHESIZE(string, title,Title);
	////课节数 第几节课
	//MYSQL_SYNTHESIZE(int, sn,Sn);
	////课程id
	//MYSQL_SYNTHESIZE(int, course_id, Coures_id);
	////编排计划id
	//MYSQL_SYNTHESIZE(int, schedule_id, Schedule_id);
	////班级id
	//MYSQL_SYNTHESIZE(int, class_id, Class_id);
	////教室id
	//MYSQL_SYNTHESIZE(int, room_id, Room_id);
	////上课日期
	////
	//MYSQL_SYNTHESIZE(string, date, Date);
	////
	////开始时间
	//MYSQL_SYNTHESIZE(string, start_time, Start_time);
	////结束时间
	//MYSQL_SYNTHESIZE(string, end_time, End_time);
	//// 创建人
	//MYSQL_SYNTHESIZE(int, creator, Creator);
	////编辑人
	//MYSQL_SYNTHESIZE(int, editor, Editor);
	////添加时间
	//MYSQL_SYNTHESIZE(string, add_time, Add_time);
	////修改时间
	//MYSQL_SYNTHESIZE(string, edit_time, Edit_time);
	////删除标记
	//MYSQL_SYNTHESIZE(int, deleted, Deleted);
	////应扣课次数
	//MYSQL_SYNTHESIZE(int,dec_count, Dec_count);
	////结课时间
	//MYSQL_SYNTHESIZE(string, close_time, Close_time);
	////结课人
	//MYSQL_SYNTHESIZE(int, close_operator,Close_operator);
	////主讲人(只用于数据权限)
	//MYSQL_SYNTHESIZE(int, teacher_id, Teacher_id);
	////是否开放预约
	//MYSQL_SYNTHESIZE(int, bookable, Bookable);
	////老师所属学校ID
	//MYSQL_SYNTHESIZE(int, school_id, School_id);
	////创建者所属组织ID
	//MYSQL_SYNTHESIZE(int, org_id, Org_id);
	//// 创建时间
	//MYSQL_SYNTHESIZE(string, createTime, CreateTime);
	//// 修改人
	//MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
	//// 修改时间
	//MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);
public:
	GetTimeableDO() : BaseDO("sample")
	{
		// 1. 主键字段（必须保留）
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// 2. 核心字符串类型字段（仅保留业务所需）
		MYSQL_ADD_FIELD("title", "s", title);          // 课程标题（核心：课名）
		MYSQL_ADD_FIELD("date", "s", date);            // 上课日期（核心）
		MYSQL_ADD_FIELD("start_time", "s", start_time);// 开始时间（核心）
		MYSQL_ADD_FIELD("end_time", "s", end_time);    // 结束时间（核心）
		// 新增：教师姓名（从teacher表关联）
		MYSQL_ADD_FIELD("teacher_name", "s", teacher_name);
		// 新增：签到状态（从lesson_student表关联）
		MYSQL_ADD_FIELD("sign_state", "i", sign_state);

		// 3. 核心整型字段（仅保留业务所需）
		MYSQL_ADD_FIELD("sn", "i", sn);                // 课节数（第几节课）
		MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);// 主讲人ID（关联教师姓名用，可选保留）
		MYSQL_ADD_FIELD("schedule_id", "i", schedule_id);// 编排计划ID（关联星期几，可选保留）

		//// 1. 注册主键字段（id是主键）
		//MYSQL_ADD_FIELD_PK("id", "s", id);

		//// 2. 注册普通字符串类型字段（标记 "s"）
		//MYSQL_ADD_FIELD("title", "s", title);          // 课程标题
		//MYSQL_ADD_FIELD("date", "s", date);            // 上课日期
		//MYSQL_ADD_FIELD("start_time", "s", start_time);// 开始时间
		//MYSQL_ADD_FIELD("end_time", "s", end_time);    // 结束时间
		//MYSQL_ADD_FIELD("add_time", "s", add_time);    // 添加时间
		//MYSQL_ADD_FIELD("edit_time", "s", edit_time);  // 修改时间
		//MYSQL_ADD_FIELD("close_time", "s", close_time);// 结课时间

		//// 3. 注册整型字段（标记 "i"）
		//MYSQL_ADD_FIELD("sn", "i", sn);                // 课节数
		//MYSQL_ADD_FIELD("course_id", "i", course_id);  // 课程id
		//MYSQL_ADD_FIELD("schedule_id", "i", schedule_id);// 编排计划id
		//MYSQL_ADD_FIELD("class_id", "i", class_id);    // 班级id
		//MYSQL_ADD_FIELD("room_id", "i", room_id);      // 教室id
		//MYSQL_ADD_FIELD("creator", "i", creator);      // 创建人
		//MYSQL_ADD_FIELD("editor", "i", editor);        // 编辑人
		//MYSQL_ADD_FIELD("deleted", "i", deleted);      // 删除标记
		//MYSQL_ADD_FIELD("dec_count", "i", dec_count);  // 应扣课次数
		//MYSQL_ADD_FIELD("close_operator", "i", close_operator);// 结课人
		//MYSQL_ADD_FIELD("teacher_id", "i", teacher_id);// 主讲人
		//MYSQL_ADD_FIELD("bookable", "i", bookable);    // 是否开放预约
		//MYSQL_ADD_FIELD("school_id", "i", school_id);  // 老师所属学校ID
		//MYSQL_ADD_FIELD("org_id", "i", org_id);        // 创建者所属组织ID
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<GetTimeableDO> PtrGetTimeableDO;
#endif // !_TIMEABLE_DO_