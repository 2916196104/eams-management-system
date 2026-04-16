#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#ifndef _HOMEWORK_DAO_H_
#define _HOMEWORK_DAO_H_

#include "BaseDAO.h"
#include "dao/gw-dao/HomeworkQueryRow.h"

/**
 * 作业数据访问对象（写法对齐 arch-demo MenuDAO：继承 BaseDAO，SQL 显式列名）
 */
class HomeworkDAO : public BaseDAO {
public:
	uint64_t countHomeworkPublishedByClassFilter(const std::string& classIdFilter);
	std::list<HomeworkPublishedRow> selectPublishedHomeworkPage(const std::string& classIdFilter, int offset, int limit);
	int32_t countSubmitByHomeworkId(const std::string& homeworkIdStr);
	HomeworkDetailRow selectHomeworkById(int64_t homeworkPk, bool& ok);
	std::list<HomeworkRecordRow> selectRecordsByHomeworkId(const std::string& homeworkIdStr);
	HomeworkRecordRow selectRecordById(const std::string& recordId, bool& ok);
	int updateRecordComment(const std::string& recordId, int score, const std::string& comment,
		const std::string& commentTime, const std::string& teacherId);
	uint64_t insertHomework(int64_t classId, const std::string& title, const std::string& content,
		int64_t creatorUserId, int64_t orgId, const std::string& addTime, const std::string& editTime);
	bool isAdminManagingClass(const std::string& classTableId, const std::string& adminId);
};

#endif // !_HOMEWORK_DAO_H_
