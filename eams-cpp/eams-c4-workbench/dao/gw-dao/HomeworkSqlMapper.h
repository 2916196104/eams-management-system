#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#ifndef _HOMEWORK_SQL_MAPPER_H_
#define _HOMEWORK_SQL_MAPPER_H_

#include "Mapper.h"
#include "dao/gw-dao/HomeworkQueryRow.h"

/**
 * 查询结果集 → 作业列表行（等价于 arch-demo 中 MenuMapper 角色）
 */
class HomeworkPublishedSqlMapper : public Mapper<HomeworkPublishedRow> {
public:
	HomeworkPublishedRow mapper(ResultSet* resultSet) const override {
		HomeworkPublishedRow r;
		r.id = resultSet->getInt64("id");
		r.classId = resultSet->getInt64("class_id");
		r.title = resultSet->getString("title").c_str();
		r.addTime = resultSet->getString("add_time").c_str();
		r.className = resultSet->getString("class_name").c_str();
		return r;
	}
};

/** 查询结果集 → 作业详情行 */
class HomeworkDetailSqlMapper : public Mapper<HomeworkDetailRow> {
public:
	HomeworkDetailRow mapper(ResultSet* resultSet) const override {
		HomeworkDetailRow r;
		r.id = resultSet->getInt64("id");
		r.classId = resultSet->getInt64("class_id");
		r.title = resultSet->getString("title").c_str();
		r.content = resultSet->getString("content").c_str();
		r.addTime = resultSet->getString("add_time").c_str();
		r.className = resultSet->getString("class_name").c_str();
		r.classKey = resultSet->getString("class_key").c_str();
		return r;
	}
};

/** 查询结果集 → 提交记录行 */
class HomeworkRecordSqlMapper : public Mapper<HomeworkRecordRow> {
public:
	HomeworkRecordRow mapper(ResultSet* resultSet) const override {
		HomeworkRecordRow r;
		r.id = resultSet->getString("id").c_str();
		r.homeworkId = resultSet->getString("homework_id").c_str();
		r.studentId = resultSet->getString("student_id").c_str();
		r.addTime = resultSet->getString("add_time").c_str();
		r.content = resultSet->getString("content").c_str();
		r.score = static_cast<int>(resultSet->getInt("score"));
		r.comment = resultSet->isNull("comment") ? "" : resultSet->getString("comment").c_str();
		r.commentTime = resultSet->isNull("comment_time") ? "" : resultSet->getString("comment_time").c_str();
		r.commentTeacher = resultSet->isNull("comment_teacher") ? "" : resultSet->getString("comment_teacher").c_str();
		r.images = resultSet->isNull("images") ? "" : resultSet->getString("images").c_str();
		return r;
	}
};

#endif // !_HOMEWORK_SQL_MAPPER_H_
