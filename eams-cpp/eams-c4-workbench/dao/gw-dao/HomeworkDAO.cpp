/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#include "stdafx.h"
#include "dao/gw-dao/HomeworkDAO.h"
#include "dao/gw-dao/HomeworkSqlMapper.h"
#include "domain/do/HomeworkDO.h"

uint64_t HomeworkDAO::countHomeworkPublishedByClassFilter(const std::string& classIdFilter) {
	const std::string sql =
		"SELECT COUNT(h.id) AS cnt FROM homework h "
		"WHERE h.deleted = 0 AND CAST(h.class_id AS CHAR) = ?";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(classIdFilter)));
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<HomeworkPublishedRow> HomeworkDAO::selectPublishedHomeworkPage(const std::string& classIdFilter, int offset, int limit) {
	const std::string sql =
		"SELECT h.id, h.class_id, h.title, h.add_time, IFNULL(c.name,'') AS class_name "
		"FROM homework h "
		"LEFT JOIN class c ON c.id = CAST(h.class_id AS CHAR) "
		"WHERE h.deleted = 0 AND CAST(h.class_id AS CHAR) = ? "
		"ORDER BY h.add_time DESC "
		"LIMIT ? OFFSET ?";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(classIdFilter)));
	params.emplace_back(SqlParam("i", std::make_shared<int32_t>(limit)));
	params.emplace_back(SqlParam("i", std::make_shared<int32_t>(offset)));
	return sqlSession->executeQuery<HomeworkPublishedRow>(sql, HomeworkPublishedSqlMapper(), params);
}

int32_t HomeworkDAO::countSubmitByHomeworkId(const std::string& homeworkIdStr) {
	const std::string sql =
		"SELECT COUNT(r.id) AS cnt FROM homework_record r WHERE r.homework_id = ?";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(homeworkIdStr)));
	return static_cast<int32_t>(sqlSession->executeQueryNumerical(sql, params));
}

HomeworkDetailRow HomeworkDAO::selectHomeworkById(int64_t homeworkPk, bool& ok) {
	ok = false;
	const std::string sql =
		"SELECT h.id, h.class_id, h.title, h.content, h.add_time, IFNULL(c.name,'') AS class_name, "
		"IFNULL(CAST(h.class_id AS CHAR), '') AS class_key "
		"FROM homework h "
		"LEFT JOIN class c ON c.id = CAST(h.class_id AS CHAR) "
		"WHERE h.id = ? AND h.deleted = 0";
	SqlParams params;
	params.emplace_back(SqlParam("ll", std::make_shared<int64_t>(homeworkPk)));
	auto row = sqlSession->executeQueryOne<HomeworkDetailRow>(sql, HomeworkDetailSqlMapper(), params);
	if (row.id != 0) {
		ok = true;
	}
	return row;
}

std::list<HomeworkRecordRow> HomeworkDAO::selectRecordsByHomeworkId(const std::string& homeworkIdStr) {
	const std::string sql =
		"SELECT r.id, r.homework_id, r.student_id, r.add_time, r.content, r.score, r.comment, "
		"r.comment_time, r.comment_teacher, r.images "
		"FROM homework_record r "
		"WHERE r.homework_id = ? "
		"ORDER BY r.add_time DESC";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(homeworkIdStr)));
	return sqlSession->executeQuery<HomeworkRecordRow>(sql, HomeworkRecordSqlMapper(), params);
}

HomeworkRecordRow HomeworkDAO::selectRecordById(const std::string& recordId, bool& ok) {
	ok = false;
	const std::string sql =
		"SELECT r.id, r.homework_id, r.student_id, r.add_time, r.content, r.score, r.comment, "
		"r.comment_time, r.comment_teacher, r.images "
		"FROM homework_record r "
		"WHERE r.id = ? LIMIT 1";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(recordId)));
	auto row = sqlSession->executeQueryOne<HomeworkRecordRow>(sql, HomeworkRecordSqlMapper(), params);
	if (!row.id.empty()) {
		ok = true;
	}
	return row;
}

int HomeworkDAO::updateRecordComment(const std::string& recordId, int score, const std::string& comment,
	const std::string& commentTime, const std::string& teacherId) {
	const std::string sql =
		"UPDATE homework_record SET score = ?, comment = ?, comment_time = ?, comment_teacher = ? WHERE id = ?";
	SqlParams params;
	params.emplace_back(SqlParam("i", std::make_shared<int32_t>(score)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(comment)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(commentTime)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(teacherId)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(recordId)));
	return sqlSession->executeUpdate(sql, params);
}

uint64_t HomeworkDAO::insertHomework(int64_t classId, const std::string& title, const std::string& content,
	int64_t creatorUserId, int64_t orgId, const std::string& addTime, const std::string& editTime) {
	HomeworkDO bd;
	bd.setClassId(classId);
	bd.setTitle(title);
	bd.setContent(content);
	bd.setCreator(creatorUserId);
	bd.setEditor(creatorUserId);
	bd.setAddTime(addTime);
	bd.setEditTime(editTime);
	bd.setDeleted(0);
	bd.setOrgId(orgId);
	return insertAutoPk(bd);
}

bool HomeworkDAO::isAdminManagingClass(const std::string& classTableId, const std::string& adminId) {
	const std::string sql =
		"SELECT COUNT(c.id) AS cnt FROM class c "
		"WHERE c.id = ? AND c.deleted = 0 AND (c.teacher_id = ? OR c.creator = ?)";
	SqlParams params;
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(classTableId)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(adminId)));
	params.emplace_back(SqlParam("s", std::make_shared<std::string>(adminId)));
	const uint64_t n = sqlSession->executeQueryNumerical(sql, params);
	return n > 0;
}
