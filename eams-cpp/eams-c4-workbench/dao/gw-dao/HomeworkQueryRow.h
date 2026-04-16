#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#ifndef _HOMEWORK_QUERY_ROW_H_
#define _HOMEWORK_QUERY_ROW_H_

#include <cstdint>
#include <list>
#include <string>

/** 作业列表查询行（已发布） */
struct HomeworkPublishedRow {
	int64_t id{};
	int64_t classId{};
	std::string title;
	std::string addTime;
	std::string className;
};

/** 作业详情主表行 */
struct HomeworkDetailRow {
	int64_t id{};
	int64_t classId{};
	std::string title;
	std::string content;
	std::string addTime;
	std::string className;
	std::string classKey;
};

/** 作业提交记录行 */
struct HomeworkRecordRow {
	std::string id;
	std::string homeworkId;
	std::string studentId;
	std::string addTime;
	std::string content;
	int score{};
	std::string comment;
	std::string commentTime;
	std::string commentTeacher;
	std::string images;
};

#endif // !_HOMEWORK_QUERY_ROW_H_
