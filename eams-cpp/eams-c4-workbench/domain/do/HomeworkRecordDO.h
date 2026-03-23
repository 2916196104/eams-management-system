#pragma once

#ifndef _HOMEWORKRECORDDO_H_
#define _HOMEWORKRECORDDO_H_

#include"DoInclude.h"

/*
	作业提交记录数据实体
*/
class HomeworkRecordDO :public BaseDO {
	//主键
	MYSQL_SYNTHESIZE(string, id, Id);
	//所属作业
	MYSQL_SYNTHESIZE(string, homework_id, Homework_id);
	//学生名
	MYSQL_SYNTHESIZE(string, student_id, Student_id);
	//时间
	MYSQL_SYNTHESIZE(string, add_time, Add_time);
	//内容
	MYSQL_SYNTHESIZE(string, content, Content);
	//点评分数
	MYSQL_SYNTHESIZE(int, score, Score);
	//点评
	MYSQL_SYNTHESIZE(string, comment, Comment);
	//点评时间
	MYSQL_SYNTHESIZE(string, comment_time, Comment_time);
	//点评老师
	MYSQL_SYNTHESIZE(string, comment_teacher, Comment_teacher);
	//图片
	MYSQL_SYNTHESIZE(string, images, Images);
public:
	HomeworkRecordDO : BaseDO("homework_record") {
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("homework_id", "s", homework_id);
		MYSQL_ADD_FIELD("student_id", "s", student_id);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("score", "i", score);
		MYSQL_ADD_FIELD("comment", "s", comment);
		MYSQL_ADD_FIELD("comment_time", "s", comment_time);
		MYSQL_ADD_FIELD("comment_teacher", "s", comment_teacher);
		MYSQL_ADD_FIELD("images", "s", images);
	}
};

//定义一个作业提交记录实体的智能指针
typedef std::shared_ptr<HomeworkRecordDO> PtrHomeworkRecordDO;

#endif //!_HOMEWORKRECORDDO_H_