#include "stdafx.h"
#include "HomeworkRecordDAO.h"
#include "HomeworkRecordMapper.h"

// 辅助函数：转义字符串
static std::string escape(const std::string& s) {
    std::string result;
    for (char c : s) {
        if (c == '\'') result += "''";
        else result += c;
    }
    return result;
}

bool HomeworkRecordDAO::insert(HomeworkRecordDO& record) {
    if (!sqlSession) {
        OATPP_LOGD("HomeworkRecordDAO", "sqlSession is NULL!");
        return false;
    }

    // 直接拼接 SQL，避免参数化类型问题
    std::string sql = "INSERT INTO homework_record (id, homework_id, student_id, add_time, content, score, comment, comment_time, comment_teacher, images) VALUES (" +
        std::to_string(record.getId()) + ", " +
        std::to_string(record.getHomeworkId()) + ", " +
        std::to_string(record.getStudentId()) + ", '" +
        escape(record.getAddTime()) + "', '" +
        escape(record.getContent()) + "', " +
        std::to_string(record.getScore()) + ", '" +
        escape(record.getComment()) + "', '" +
        escape(record.getCommentTime()) + "', " +
        std::to_string(record.getCommentTeacher()) + ", '" +
        escape(record.getImages()) + "')";

    OATPP_LOGD("HomeworkRecordDAO", "Executing SQL: %s", sql.c_str());

    try {
        int affected = sqlSession->executeUpdate(sql);
        return affected == 1;
    }
    catch (const std::exception& e) {
        OATPP_LOGD("HomeworkRecordDAO", "exception: %s", e.what());
        return false;
    }
}

PtrHomeworkRecordDO HomeworkRecordDAO::selectById(uint64_t id) {
    // 直接拼接 SQL
    std::string sql = "SELECT id, homework_id, student_id, add_time, content, score, comment, comment_time, comment_teacher, images "
        "FROM homework_record WHERE id = " + std::to_string(id);
    return sqlSession->executeQueryOne<PtrHomeworkRecordDO>(sql, PtrHomeworkRecordMapper());
}

std::list<HomeworkRecordDO> HomeworkRecordDAO::selectByHomeworkId(uint64_t homeworkId) {
    std::string sql = "SELECT id, homework_id, student_id, add_time, content, score, comment, comment_time, comment_teacher, images "
        "FROM homework_record WHERE homework_id = " + std::to_string(homeworkId) + " ORDER BY add_time DESC";
    return sqlSession->executeQuery<HomeworkRecordDO>(sql, HomeworkRecordMapper());
}

PtrHomeworkRecordDO HomeworkRecordDAO::selectByHomeworkIdAndStudentId(uint64_t homeworkId, int64_t studentId) {
    std::string sql = "SELECT id, homework_id, student_id, add_time, content, score, comment, comment_time, comment_teacher, images "
        "FROM homework_record WHERE homework_id = " + std::to_string(homeworkId) +
        " AND student_id = " + std::to_string(studentId);
    return sqlSession->executeQueryOne<PtrHomeworkRecordDO>(sql, PtrHomeworkRecordMapper());
}

bool HomeworkRecordDAO::update(const HomeworkRecordDO& record) {
    if (!sqlSession) {
        OATPP_LOGD("HomeworkRecordDAO", "sqlSession is NULL!");
        return false;
    }

    // 简单转义字符串中的单引号
    auto escape = [](const std::string& s) {
        std::string result;
        for (char c : s) {
            if (c == '\'') result += "''";
            else result += c;
        }
        return result;
        };

    std::string sql = "UPDATE homework_record SET score=" +
        std::to_string(record.getScore()) +
        ", comment='" + escape(record.getComment()) + "'" +
        ", comment_time='" + record.getCommentTime() + "'" +
        ", comment_teacher=" + std::to_string(record.getCommentTeacher()) +
        " WHERE id=" + std::to_string(record.getId());

    OATPP_LOGD("HomeworkRecordDAO", "Executing SQL: %s", sql.c_str());

    try {
        int affected = sqlSession->executeUpdate(sql);
        return affected == 1;
    }
    catch (const std::exception& e) {
        OATPP_LOGD("HomeworkRecordDAO", "exception: %s", e.what());
        return false;
    }
}