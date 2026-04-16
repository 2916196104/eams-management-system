#pragma once
#ifndef CLASSDETAIL_DO_
#define CLASSDETAIL_DO_
#include"../DoInclude.h"

class ClassDetailDO :public BaseDO
{
	//唯一ID
	MYSQL_SYNTHESIZE(string,id,Id)
	//班级名称
	MYSQL_SYNTHESIZE(string,className,ClassName);
	//班主任名称
	MYSQL_SYNTHESIZE(string,staffName,StaffName);
	//教室名称
	MYSQL_SYNTHESIZE(string,roomName,RoomName);
	//课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	//课程开始时间
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	//课程结束时间
	MYSQL_SYNTHESIZE(string,endDate,EndDate);
	//课程进度
	MYSQL_SYNTHESIZE(int,courseLessons,CourseLessons);
	//预招生人数
	MYSQL_SYNTHESIZE(int,planedStudentCount,PlanedStudentCount);
	//备注
	MYSQL_SYNTHESIZE(string,remark,Remark);
	//班级状态-是否完结
	MYSQL_SYNTHESIZE(int,beOver,BeOver);

public:
	ClassDetailDO() :BaseDO("class_detail")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("class_name", "s", className);
		MYSQL_ADD_FIELD("staff_name", "s", staffName);
		MYSQL_ADD_FIELD_NULLABLE("room_name", "s", roomName,true);
		MYSQL_ADD_FIELD("course_name", "s", courseName);
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		MYSQL_ADD_FIELD("end_date", "s", endDate);
		MYSQL_ADD_FIELD("course_lessons","i", courseLessons);
		MYSQL_ADD_FIELD("planed_student_count", "i", planedStudentCount);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("be_over", "i", beOver);
	}
};
typedef std::shared_ptr<ClassDetailDO>PtrClassDetailDO;

#endif // !CLASSDETAIL_DO_

