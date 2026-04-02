#pragma once
#ifndef COMMOMQUERY_H
#define COMMONQUERY_H
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class RegistrationPageQuery :public PageQuery {
	DTO_INIT(RegistrationPageQuery, PageQuery);
	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("common.field.student.id"));
};

/**
 * 示例分页查询对象
 */
class FollowUprecordsQuery : public PageQuery
{
	DTO_INIT(FollowUprecordsQuery, PageQuery);


	// 姓名
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	// 跟进阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	// 跟进人
	API_DTO_FIELD_DEFAULT(String, follow_up_person, ZH_WORDS_GETTER("common.field.student.follow-up-person"));
	//开始日期
	API_DTO_FIELD_DEFAULT(String, startdate, ZH_WORDS_GETTER("common.field.student.startdate"));
	//结束日期
	API_DTO_FIELD_DEFAULT(String, enddate, ZH_WORDS_GETTER("common.field.student.enddate"));

	
};
/**
  * 班级列表查询领域模型
  */
class getClassListQuery : public PageQuery
{
	DTO_INIT(getClassListQuery, PageQuery);
	// 序号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("getClassList.id");
	}
	// 班级名称
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("getClassList.name");
	}
	// 科目
	DTO_FIELD(String, subject);
	DTO_FIELD_INFO(subject) {
		info->description = ZH_WORDS_GETTER("getClassList.subject");
	}
	// 教室
	DTO_FIELD(String, classroom);
	DTO_FIELD_INFO(classroom) {
		info->description = ZH_WORDS_GETTER("getClassList.classroom");
	}
	// 学生数
	DTO_FIELD(UInt32, studentCount);
	DTO_FIELD_INFO(studentCount) {
		info->description = ZH_WORDS_GETTER("getClassList.studentCount");
	}
	// 人数上限
	DTO_FIELD(UInt32, maxStudentCount);
	DTO_FIELD_INFO(maxStudentCount) {
		info->description = ZH_WORDS_GETTER("getClassList.maxStudentCount");
	}
};

/**
 * 课程统计查询领域模型
 */
class getCourseStatisticsQuery : public PageQuery
{
	DTO_INIT(getCourseStatisticsQuery, PageQuery);
	// 课程
	DTO_FIELD(String, course);
	DTO_FIELD_INFO(course) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.course");
	}
	// 总课时
	DTO_FIELD(UInt32, totalHours);
	DTO_FIELD_INFO(totalHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.totalHours");
	}
	// 剩余课时
	DTO_FIELD(UInt32, remainingHours);
	DTO_FIELD_INFO(remainingHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.remainingHours");
	}
	// 已上课时
	DTO_FIELD(UInt32, attendedHours);
	DTO_FIELD_INFO(attendedHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.attendedHours");
	}
	// 到期日期
	DTO_FIELD(String, expireDate);
	DTO_FIELD_INFO(expireDate) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.expireDate");
	}
	//清课优先级
	DTO_FIELD(UInt32, cancelPriority);
	DTO_FIELD_INFO(cancelPriority) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.cancelPriority");
	}
};


/** 加入班级查询领域模型
**/
class JoinclassQuery : public PageQuery
{
	DTO_INIT(JoinclassQuery, PageQuery);
	// 班级名称
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("JoinClass.name");
	}
	// 分校
	DTO_FIELD(String, school);
	DTO_FIELD_INFO(school) {
		info->description = ZH_WORDS_GETTER("JoinClass.school");
	}
};



#include OATPP_CODEGEN_END(DTO)
#endif