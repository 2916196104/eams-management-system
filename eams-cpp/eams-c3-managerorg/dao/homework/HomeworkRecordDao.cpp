#include "stdafx.h"
#include "HomeworkRecordDao.h"
#include "HomeworkRecordMapper.h"

// 分页查询作业提交记录
std::list<PtrHomeworkRecordDO> HomeworkRecordDAO::getSendHomeworkList(const BackhomeworkQuery::Wrapper& query)
{
    std::string sql = "SELECT id, homework_id, student_id, add_time, content, "
        "score, comment, comment_time, comment_teacher, images "
        "FROM homeworkrecord WHERE 1=1";
    SqlParams params;

    if (query->studentId) {
        sql += " AND student_id = ?";
        SQLPARAMS_PUSH(params, "bi", int64_t, static_cast<int64_t>(query->studentId.getValue(0)));
    }

    sql += " ORDER BY add_time DESC";

    // 分页
    uint64_t pageIndex = query->pageIndex.getValue(1);
    uint64_t pageSize = query->pageSize.getValue(10);
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "i", int, static_cast<int>((pageIndex - 1) * pageSize));
    SQLPARAMS_PUSH(params, "i", int, static_cast<int>(pageSize));

    return sqlSession->executeQuery<PtrHomeworkRecordDO>(sql, PtrHomeworkRecordMapper(), params);
}

// 统计作业提交记录总数
uint64_t HomeworkRecordDAO::countSendHomework(const BackhomeworkQuery::Wrapper& query)
{
    std::string sql = "SELECT COUNT(*) FROM homeworkrecord WHERE 1=1";
    SqlParams params;

    if (query->studentId) {
        sql += " AND student_id = ?";
        SQLPARAMS_PUSH(params, "bi", int64_t, static_cast<int64_t>(query->studentId.getValue(0)));
    }

    return sqlSession->executeQueryNumerical(sql, params);
}

// 根据 ID 查询单条提交记录
PtrHomeworkRecordDO HomeworkRecordDAO::getSendHomeworkById(oatpp::UInt64 id)
{
    std::string sql = "SELECT id, homework_id, student_id, add_time, content, "
        "score, comment, comment_time, comment_teacher, images "
        "FROM homeworkrecord WHERE id = ?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "bi", int64_t, static_cast<int64_t>(id));

    return sqlSession->executeQueryOne<PtrHomeworkRecordDO>(sql, PtrHomeworkRecordMapper(), params);
}

// 更新点评信息
bool HomeworkRecordDAO::updateComment(const HomeworkRecordDO& record)
{
    std::string sql = "UPDATE homeworkrecord SET comment=?, score=?, comment_teacher=?, comment_time=? WHERE id=?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, record.getComment());
    SQLPARAMS_PUSH(params, "ti", int8_t, record.getScore());
    SQLPARAMS_PUSH(params, "bi", int64_t, record.getCommentTeacher());
    SQLPARAMS_PUSH(params, "dt", std::string, record.getCommentTime());
    SQLPARAMS_PUSH(params, "bi", int64_t, record.getId());

    return sqlSession->executeUpdate(sql, params) > 0;
}