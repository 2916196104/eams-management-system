#include "stdafx.h"
#include "HomeworkRecordDAO.h"
#include "CommonMacros.h"
#include "SimpleDateTimeFormat.h"
#include "../../../lib-common/include/id/SnowFlake.h"

static SnowFlake sf(1, 1);

// ===================== 提交作业 =====================
bool HomeworkRecordDAO::submit(const HomeworkRecordDO& data)
{
    uint64_t homeworkId = static_cast<uint64_t>(data.gethomework_id());
    uint64_t studentId = static_cast<uint64_t>(data.getstudent_id());
    std::string content = data.getcontent();
    std::string images = data.getimages();
    std::string addTime = data.getadd_time();
    uint64_t id = sf.nextId();

    std::string sql = "\
        INSERT INTO homework_record \
        (id, homework_id, student_id, add_time, content, images, score, comment, comment_time, comment_teacher) \
        VALUES (?,?,?,?,?,?,0,'',NULL,0)\
    ";

    SqlParams params;
    SQLPARAMS_PUSH(params, "ull", uint64_t, id);
    SQLPARAMS_PUSH(params, "ull", uint64_t, homeworkId);
    SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
    SQLPARAMS_PUSH(params, "s", std::string, addTime);
    SQLPARAMS_PUSH(params, "s", std::string, content);
    SQLPARAMS_PUSH(params, "s", std::string, images);

    // 执行SQL
    bool ret = sqlSession->executeUpdate(sql, params) > 0;
    
    return ret;
}

// ===================== 删除作业=====================
bool HomeworkRecordDAO::deleteByStudentAndHomework(uint64_t studentId, uint64_t homeworkId)
{
    // SQL：更新清空 content、images，重置提交时间
    std::string sql = R"(
        UPDATE homework_record 
        SET content = '', images = '', add_time = ? 
        WHERE student_id = ? AND homework_id = ?
    )";

    SqlParams params;
    // 1. 当前时间
    SQLPARAMS_PUSH(params, "s", std::string, SimpleDateTimeFormat::format());
    // 2. 学生ID
    SQLPARAMS_PUSH(params, "ull", uint64_t, studentId);
    // 3. 作业ID
    SQLPARAMS_PUSH(params, "ull", uint64_t, homeworkId);

    int affectedRows = sqlSession->executeUpdate(sql, params);
    return affectedRows > 0;
}