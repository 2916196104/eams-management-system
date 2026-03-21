#pragma once
#ifndef _COURSE_EVALUATE_DO_H_
#define _COURSE_EVALUATE_DO_H_

#include "DoInclude.h"

Class CourseEvaluateDO : public BaseDO{
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
//	所属课程
MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
//  学生id
MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
//  订单id
MYSQL_SYNTHESIZE(uint64_t, orderId, OrderId);
//  章节标题
MYSQL_SYNTHESIZE(string, content, Content);
//  打分
MYSQL_SYNTHESIZE(int, score, Score);
//  发布状态
MYSQL_SYNTHESIZE(int, state, State);
//	创建人
MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
//  编辑人
MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
//	添加时间
MYSQL_SYNTHESIZE(string, addTime, AddTime);
//	编辑时间
MYSQL_SYNTHESIZE(string, editTime, EditTime);
//	删除标记
MYSQL_SYNTHESIZE(int, deleted, Deleted);
// 关联查询字段（来自 course.name，非表字段，不注册 FIELD）
MYSQL_SYNTHESIZE(string, courseName, CourseName);


public:
	CourseEvaluateDO() : BaseDO("course comment") {
		MYSQL_ADD_FIELD_PK("id", "bi", id);
		MYSQL_ADD_FIELD("course_id", "bi", courseId);
		MYSQL_ADD_FIELD("student_id", "bi", studentId);
		MYSQL_ADD_FIELD("order_id", "bi", orderId);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("state", "i", state);
		MYSQL_ADD_FIELD("creator", "bi", creator);
		MYSQL_ADD_FIELD("editor", "bi", editor);
		MYSQL_ADD_FIELD("add_time", "dt", addTime);
		MYSQL_ADD_FIELD("edit_time", "dt", editTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
	}
};
typefdef std::shared_ptr<CourseEvaluateDO> PtrCourseEvaluateDO;


#endif // !_COURSE_EVALUATE_DO_H_
