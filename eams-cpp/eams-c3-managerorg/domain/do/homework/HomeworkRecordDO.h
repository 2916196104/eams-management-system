#pragma once

#ifndef _HOMEWORKRECORD_DO_
#define _HOMEWORKRECORD_DO_
#include "../DoInclude.h"

/**
 * 数据库实体类
 */
class HomeworkRecordDO : public BaseDO
{
	// id
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	// 作业编号id
	MYSQL_SYNTHESIZE(int64_t, homework_id, HomeworkId);
	// 学生编号id
	MYSQL_SYNTHESIZE(int64_t, student_id, StudentId);
	// 添加时间
	MYSQL_SYNTHESIZE(string, add_time,AddTime);
	// 内容
	MYSQL_SYNTHESIZE(string, content, Content);
	// 分数
	MYSQL_SYNTHESIZE(int8_t, score, Score);
	// 评论
	MYSQL_SYNTHESIZE(string, comment, Comment);
	// 评论时间
	MYSQL_SYNTHESIZE(string, comment_time, CommentTime);
	// 评论老师
	MYSQL_SYNTHESIZE(int64_t, comment_teacher, CommentTeacher);
	// 图片?
	MYSQL_SYNTHESIZE(string, images, Images);
public:
	HomeworkRecordDO() : BaseDO("homeworkrecord")
	{
		MYSQL_ADD_FIELD_PK("id", "bi", id);
		MYSQL_ADD_FIELD("homework_id", "bi", homework_id);
		MYSQL_ADD_FIELD("student_id", "bi", student_id);
		MYSQL_ADD_FIELD("add_time", "dt", add_time);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("score", "ti", score);
		MYSQL_ADD_FIELD("comment", "s", comment);
		MYSQL_ADD_FIELD("comment_time", "dt", comment_time);
		MYSQL_ADD_FIELD("comment_teacher", "bi", comment_teacher);
		MYSQL_ADD_FIELD("images", "s", images);
	}
};

// 给HomeworkRecordDO智能指针设定一个别名方便使用
typedef std::shared_ptr<HomeworkRecordDO> PtrHomeworkRecordDO;
#endif // !_HOMEWORKRECORD_DO_
