#pragma once
#ifndef STUDENTDO_H
#define STUDENTDO_H 

#include "../DoInclude.h"
class StaffDO : public BaseDO {
public:
	// 职工id
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 职工姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 手机号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 微信登录id
	MYSQL_SYNTHESIZE(int, wxAccessId, WxAccessId);
	// email
	MYSQL_SYNTHESIZE(string, email, Email);
	//生日
	MYSQL_SYNTHESIZE(string, birthday, BirthDay);
	//性别
	MYSQL_SYNTHESIZE(int, sex, Sex);
	//身份证
	MYSQL_SYNTHESIZE(string, idCard, IdCard);
	//毕业学校
	MYSQL_SYNTHESIZE(string, school, School);
	//学历
	MYSQL_SYNTHESIZE(int, degree, Degree);
	//备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//在职状态
	MYSQL_SYNTHESIZE(int, state, State);
	//是否是管理者
	MYSQL_SYNTHESIZE(int, isManager, IsManager);
	//头像
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	//入职日期
	MYSQL_SYNTHESIZE(string, hireDate, HireDate);
	//离职日期
	MYSQL_SYNTHESIZE(string, fireDate, FireDate);
	//介绍
	MYSQL_SYNTHESIZE(string, introduction, Introduction);
	//创建时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	//编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	//创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	//编辑人
	MYSQL_SYNTHESIZE(string, editor, Editor);
	//是否删除
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//密码
	MYSQL_SYNTHESIZE(string, password, Password);
	//课时费
	MYSQL_SYNTHESIZE(int, classFee, ClassFee);
	//助教费
	MYSQL_SYNTHESIZE(int, assistantFee, AssistantFee);
	//staff所属组织id
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);
	//是否内部人员
	MYSQL_SYNTHESIZE(int, isInner, IsInner);
public:
	StaffDO() : BaseDO("staff")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "i", mobile);
		MYSQL_ADD_FIELD("wxAccessId", "i", wxAccessId);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("sex", "i", sex);
		MYSQL_ADD_FIELD("idCard", "s", idCard);
		MYSQL_ADD_FIELD("school", "s", school);
		MYSQL_ADD_FIELD("degree", "i", degree);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("isManager", "i", isManager);
		MYSQL_ADD_FIELD("headImg", "s", headImg);
		MYSQL_ADD_FIELD("hireDate", "s", hireDate);
		MYSQL_ADD_FIELD("fireDate", "s", fireDate);
		MYSQL_ADD_FIELD("introduction", "s", introduction);
		MYSQL_ADD_FIELD("addTime", "s", addTime);
		MYSQL_ADD_FIELD("editTime", "s", editTime);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("classFee", "i", classFee);
		MYSQL_ADD_FIELD("assistantFee", "i", assistantFee);
		MYSQL_ADD_FIELD("orgId", "i", orgId);
		MYSQL_ADD_FIELD("isInner", "i", isInner);
	}
};

class UserDO : public BaseDO
{
	MYSQL_SYNTHESIZE(uint64_t, id, Id);//id` bigint unsigned NOT NULL COMMENT '用户主键',

	MYSQL_SYNTHESIZE(string, name, Name);//`name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '家长姓名',

	MYSQL_SYNTHESIZE(int, wx_access_id, Wx_access_id);//`wx_access_id` int DEFAULT NULL COMMENT '微信id',

	MYSQL_SYNTHESIZE(string, mobile, Mobile);//`mobile` varchar(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '手机号账号',

	MYSQL_SYNTHESIZE(string, email, Email);//`email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT 'email',

	MYSQL_SYNTHESIZE(int, state, State);	//`state` tinyint(1) DEFAULT '1' COMMENT '账号状态'

	MYSQL_SYNTHESIZE(string, password, Password);//`password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '密码',

	MYSQL_SYNTHESIZE(int, login_times, Login_times);//`login_times` int DEFAULT '0' COMMENT '登录次数',

	MYSQL_SYNTHESIZE(string, latest_login_time, Latest_login_time);//`latest_login_time` datetime DEFAULT NULL COMMENT '上次登录时间',

	MYSQL_SYNTHESIZE(string, latest_login_ip, Latest_login_ip);//`latest_login_ip` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '上次登录ip',

	MYSQL_SYNTHESIZE(string, add_time, Add_time);//`add_time` datetime DEFAULT NULL COMMENT '加入时间',

	MYSQL_SYNTHESIZE(string, remark, Remark);//`remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL COMMENT '备注',

	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);//`creator` bigint DEFAULT NULL COMMENT '添加者',

	MYSQL_SYNTHESIZE(uint64_t, school_id, School_id);//`school_id` bigint DEFAULT NULL COMMENT '所属学校id',

	MYSQL_SYNTHESIZE(uint64_t, org_id, Org_id);//`org_id` bigint DEFAULT NULL COMMENT '创建者所属组织ID',


public:
	UserDO() : BaseDO("user")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("wx_access_id", "i", wx_access_id);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("email", "s", email);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("password", "s", password);
		MYSQL_ADD_FIELD("login_times", "i", login_times);
		MYSQL_ADD_FIELD("latest_login_time", "s", latest_login_time);
		MYSQL_ADD_FIELD("latest_login_ip", "s", latest_login_ip);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("school_id", "s", school_id);
		MYSQL_ADD_FIELD("org_id", "s", org_id);

	}
};
class ParentAccountQueryDO : public BaseDO
{
public:
	ParentAccountQueryDO() : BaseDO("")
	{
		MYSQL_ADD_FIELD_PK("user_id", "i", userId);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		MYSQL_ADD_FIELD("wx_name", "s", wxName);
		MYSQL_ADD_FIELD("login_times", "i", loginTimes);
		MYSQL_ADD_FIELD("latest_login_time", "s", latestLoginTime);
		MYSQL_ADD_FIELD("latest_login_ip", "s", latestLoginIp);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("state", "i", state);
	}

	MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, wxName, WxName);
	MYSQL_SYNTHESIZE(int32_t, loginTimes, LoginTimes);
	MYSQL_SYNTHESIZE(string, latestLoginTime, LatestLoginTime);
	MYSQL_SYNTHESIZE(string, latestLoginIp, LatestLoginIp);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int32_t, state, State);
};
class QueryStudentbyIdDO : public BaseDO {
public:
	// 瀛︾敓id
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 瀛︾敓濮撳悕
	MYSQL_SYNTHESIZE(string, name, Name);
	// 鎵嬫満鍙?
	MYSQL_SYNTHESIZE(string, phone, Phone);
	// 鍥剧墖璺緞
	MYSQL_SYNTHESIZE(string, picturePath, PicturePath);
	// 鍓╀綑璇剧▼鏁?
	MYSQL_SYNTHESIZE(int, leftCourseCount, LeftCourseCount);
	// 鍓╀綑绉垎
	MYSQL_SYNTHESIZE(int, leftPoints, LeftPoints);
	// 闃舵
	MYSQL_SYNTHESIZE(int, stage, Stage);
	// 鎬у埆
	MYSQL_SYNTHESIZE(int, sex, Sex);
	// 骞撮緞
	MYSQL_SYNTHESIZE(int, age, Age);
	// 鐢熸棩
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	// 韬唤璇佸彿
	MYSQL_SYNTHESIZE(string, identificationNumber, IdentificationNumber);
	// 瀹堕暱濮撳悕
	MYSQL_SYNTHESIZE(string, parentName, ParentName);
	// 鍏崇郴绫诲瀷
	MYSQL_SYNTHESIZE(string, relationType, RelationType);
	// 骞寸骇
	MYSQL_SYNTHESIZE(int, grade, Grade);
	// 鍏ュ鏃堕棿
	MYSQL_SYNTHESIZE(string, enterTime, EnterTime);
	// 绮剧‘鍏ュ鏃堕棿
	MYSQL_SYNTHESIZE(string, accurateEnterTime, AccurateEnterTime);
	// 澶囨敞
	MYSQL_SYNTHESIZE(string, note, Note);
	// 璇剧▼杩涘害
	MYSQL_SYNTHESIZE(string, courseProgress, CourseProgress);

public:
	QueryStudentbyIdDO() : BaseDO("student")  // 鍋囪琛ㄥ悕涓?"student"锛岃鏍规嵁瀹為檯琛ㄥ悕淇敼
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("phone", "s", phone);
		MYSQL_ADD_FIELD("head_img", "s", picturePath);
		MYSQL_ADD_FIELD("left_course_count", "i", leftCourseCount);
		MYSQL_ADD_FIELD("left_points", "i", leftPoints);
		MYSQL_ADD_FIELD("stage", "i", stage);
		MYSQL_ADD_FIELD("sex", "i", sex);
		MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("identification_number", "s", identificationNumber);
		MYSQL_ADD_FIELD("parent_name", "s", parentName);
		MYSQL_ADD_FIELD("relation_type", "s", relationType);
		MYSQL_ADD_FIELD("grade", "i", grade);
		MYSQL_ADD_FIELD("enter_time", "s", enterTime);
		MYSQL_ADD_FIELD("accurate_enter_time", "s", accurateEnterTime);
		MYSQL_ADD_FIELD("note", "s", note);
		MYSQL_ADD_FIELD("course_progress", "s", courseProgress);
	}
};

class FinishStudentQueryDO : public BaseDO
{
public:
	FinishStudentQueryDO() : BaseDO("")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		MYSQL_ADD_FIELD("parent_name", "s", parentName);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("counselor", "s", counselor);
		MYSQL_ADD_FIELD("grade", "s", grade);
		MYSQL_ADD_FIELD("school_name", "s", schoolName);
		MYSQL_ADD_FIELD("lesson_count", "i", lessonCount);
		MYSQL_ADD_FIELD("points", "i", points);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("age", "i", age);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
	}

	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, parentName, ParentName);
	MYSQL_SYNTHESIZE(int32_t, familyRel, FamilyRel);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, counselor, Counselor);
	MYSQL_SYNTHESIZE(string, grade, Grade);
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName);
	MYSQL_SYNTHESIZE(int32_t, lessonCount, LessonCount);
	MYSQL_SYNTHESIZE(int32_t, points, Points);
	MYSQL_SYNTHESIZE(int32_t, gender, Gender);
	MYSQL_SYNTHESIZE(int32_t, age, Age);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
};
class FinishStudentDO : public BaseDO
{
public:
	FinishStudentDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		MYSQL_ADD_FIELD("name", "s", studentName);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("credit", "i", points);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
	}

	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	MYSQL_SYNTHESIZE(string, parentName, ParentName);
	MYSQL_SYNTHESIZE(int32_t, familyRel, FamilyRel);
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	MYSQL_SYNTHESIZE(string, counselor, Counselor);
	MYSQL_SYNTHESIZE(string, grade, Grade);
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName);
	MYSQL_SYNTHESIZE(int32_t, lessonCount, LessonCount);
	MYSQL_SYNTHESIZE(int32_t, points, Points);
	MYSQL_SYNTHESIZE(int32_t, gender, Gender);
	MYSQL_SYNTHESIZE(int32_t, age, Age);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
};


typedef std::shared_ptr<StaffDO> PtrStaffDO;


// 班级学员数据库实体类
class ClassStudentDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 班级id
	MYSQL_SYNTHESIZE(string, classId, ClassId);
	// 学生id
	MYSQL_SYNTHESIZE(string, studentId, StudentId);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 创建人
	MYSQL_SYNTHESIZE(string, creator, Creator);
	// 加入原因
	MYSQL_SYNTHESIZE(int, reason, Reason);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 备注信息
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 默认消费课程
	MYSQL_SYNTHESIZE(string, consumeCourseId, ConsumeCourseId);

public:
	ClassStudentDO() : BaseDO("class_student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("class_id", "s", classId);
		MYSQL_ADD_FIELD("student_id", "s", studentId);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("reason", "i", reason);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("consume_course_id", "s", consumeCourseId);
	}
};

/**
班级列表数据库实体类
**/
class getClassListDO : public BaseDO
{
	// 序号
	MYSQL_SYNTHESIZE(string, id, Id);
	// 班级名称
	MYSQL_SYNTHESIZE(string, className, ClassName);
	// 科目
	MYSQL_SYNTHESIZE(string, subject, Subject);
	// 教室
	MYSQL_SYNTHESIZE(string, classroom, Classroom);
	// 学生数
	MYSQL_SYNTHESIZE(int, studentCount, StudentCount);
	// 人数上限
	MYSQL_SYNTHESIZE(int, maxStudentCount, MaxStudentCount);

public:
	getClassListDO() : BaseDO("")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("class_name", "s", className);
		MYSQL_ADD_FIELD("subject", "s", subject);
		MYSQL_ADD_FIELD("classroom", "s", classroom);
		MYSQL_ADD_FIELD("student_count", "i", studentCount);
		MYSQL_ADD_FIELD("max_student_count", "i", maxStudentCount);
	}
};
typedef std::shared_ptr<getClassListDO> PtrgetClassListDO;


/**
 课程统计数据库实体类
**/
class getCourseStatisticsDO : public BaseDO
{
	// 课程
	MYSQL_SYNTHESIZE(string, course, Course);
	// 总课时
	MYSQL_SYNTHESIZE(int, totalHours, TotalHours);
	// 剩余课时
	MYSQL_SYNTHESIZE(int, remainingHours, RemainingHours);
	// 已上课时
	MYSQL_SYNTHESIZE(int, attendedHours, AttendedHours);
	// 到期日期
	MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
	// 清课优先级
	MYSQL_SYNTHESIZE(int, cancelPriority, CancelPriority);

public:
	getCourseStatisticsDO() : BaseDO("")
	{
		MYSQL_ADD_FIELD_PK("course", "s", course);
		MYSQL_ADD_FIELD("total_hours", "i", totalHours);
		MYSQL_ADD_FIELD("remaining_hours", "i", remainingHours);
		MYSQL_ADD_FIELD("attended_hours", "i", attendedHours);
		MYSQL_ADD_FIELD("expire_date", "s", expireDate);
		MYSQL_ADD_FIELD("cancel_priority", "i", cancelPriority);
	}
};
typedef std::shared_ptr<getCourseStatisticsDO> PtrgetCourseStatisticsDO;


/**
? 加入班级数据库实体类
**/
class JoinclassDO : public BaseDO
{
	// 班级名称
	MYSQL_SYNTHESIZE(string, className, ClassName);
	// 分校
	MYSQL_SYNTHESIZE(string, school, School);

public:
	JoinclassDO() : BaseDO("")
	{
		MYSQL_ADD_FIELD_PK("class_name", "s", className);
		MYSQL_ADD_FIELD("school", "s", school);
	}
};
typedef std::shared_ptr<JoinclassDO> PtrJoinclassDO;

/**
*  Excel导入导出数据库实体类
**/
class ExcelStudentDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, userId, UserId);
	MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
	MYSQL_SYNTHESIZE(string, schoolId, SchoolId);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	MYSQL_SYNTHESIZE(int, stage, Stage);
	MYSQL_SYNTHESIZE(int, gender, Gender);
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	MYSQL_SYNTHESIZE(string, joinWay, JoinWay);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
	MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	MYSQL_SYNTHESIZE(string, counselor, Counselor);
	MYSQL_SYNTHESIZE(string, creator, Creator);
	MYSQL_SYNTHESIZE(string, editor, Editor);
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	MYSQL_SYNTHESIZE(string, idcard, Idcard);
	MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
	MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
	MYSQL_SYNTHESIZE(int, grade, Grade);
	MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
	MYSQL_SYNTHESIZE(string, wxAccessId, WxAccessId);
	MYSQL_SYNTHESIZE(int, credit, Credit);
	MYSQL_SYNTHESIZE(string, orgId, OrgId);
	MYSQL_SYNTHESIZE(int, gradeId, GradeId);

public:
	ExcelStudentDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("user_id", "s", userId);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("school_id", "s", schoolId);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("stage", "i", stage);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		MYSQL_ADD_FIELD("join_way", "s", joinWay);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
		MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("counselor", "s", counselor);
		MYSQL_ADD_FIELD("creator", "s", creator);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("idcard", "s", idcard);
		MYSQL_ADD_FIELD("redpoint_grade", "s", redpointGrade);
		MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpointEvaluate);
		MYSQL_ADD_FIELD("grade", "i", grade);
		MYSQL_ADD_FIELD("join_date", "s", joinDate);
		MYSQL_ADD_FIELD("wx_access_id", "s", wxAccessId);
		MYSQL_ADD_FIELD("credit", "i", credit);
		MYSQL_ADD_FIELD("org_id", "s", orgId);
		MYSQL_ADD_FIELD("grade_id", "i", gradeId);
	}
};
typedef std::shared_ptr<ExcelStudentDO> PtrExcelStudentDO;

#endif
