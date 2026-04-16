#pragma once

#ifndef _HOMEWORKRECORD_MAPPER_
#define _HOMEWORKRECORD_MAPPER_

#include "Mapper.h"
#include "../../domain/do/homework/HomeworkRecordDO.h"

/**
 * 表字段匹配映射，对应homeworkrecord表的每一个字段
 * 共10个字段：id, homework_id, student_id, add_time, content, score, comment, comment_time, comment_teacher, images
 */
class HomeworkRecordMapper : public Mapper<HomeworkRecordDO>
{
public:
	HomeworkRecordDO mapper(ResultSet* resultSet) const override
	{
		HomeworkRecordDO data;
		data.setId(resultSet->getInt(1));               // id
		data.setHomeworkId(resultSet->getInt(2));       // homework_id
		data.setStudentId(resultSet->getInt(3));        // student_id
		data.setAddTime(resultSet->getString(4));       // add_time
		data.setContent(resultSet->getString(5));       // content
		data.setScore(static_cast<int8_t>(resultSet->getInt(6))); // score
		data.setComment(resultSet->getString(7));       // comment
		data.setCommentTime(resultSet->getString(8));   // comment_time
		data.setCommentTeacher(resultSet->getInt(9));   // comment_teacher
		data.setImages(resultSet->getString(10));       // images
		return data;
	}
};

/**
 * 表字段匹配映射-创建智能指针对象
 */
class PtrHomeworkRecordMapper : public Mapper<PtrHomeworkRecordDO>
{
public:
	PtrHomeworkRecordDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<HomeworkRecordDO>();

		data->setId(resultSet->getInt64(1));
		data->setHomeworkId(resultSet->getInt64(2));
		data->setStudentId(resultSet->getInt64(3));
		data->setAddTime(resultSet->getString(4));
		data->setContent(resultSet->getString(5));
		data->setScore(resultSet->getInt(6));
		data->setComment(resultSet->getString(7));
		data->setCommentTime(resultSet->getString(8));
		data->setCommentTeacher(resultSet->getInt64(9));
		data->setImages(resultSet->getString(10));
		return data;
	}
};

#endif // !_HOMEWORKRECORD_MAPPER_