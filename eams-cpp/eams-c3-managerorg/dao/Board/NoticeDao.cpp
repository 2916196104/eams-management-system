#include "stdafx.h"
#include "NoticeDao.h"
#include "NoticeMapper.h"
#include "domain/query/BoardManager/BoardManagerQuery.h"

std::list<PtrNoticeDO> NoticeDAO::selectAll(const BoardQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT id, title, content, view_num, creator, editor, add_time, edit_time, deleted FROM notice ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY add_time DESC";
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
    return sqlSession->executeQuery<PtrNoticeDO>(sql, PtrNoticeMapper());
}

PtrNoticeDO NoticeDAO::selectById(oatpp::UInt64 id)
{
    std::string sql = "SELECT id, title, content, view_num, creator, "
        "editor, add_time, edit_time, deleted "
        "FROM notice WHERE id = ? AND deleted = 0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, id);
    return sqlSession->executeQueryOne<PtrNoticeDO>(sql, PtrNoticeMapper(), params);
}

std::list<PtrNoticeDO> NoticeDAO::selectByTitle(const std::string& title)
{
    if (title.empty()) return {};
    std::string sql = "SELECT id, title, content, view_num, creator, "
        "editor, add_time, edit_time, deleted "
        "FROM notice WHERE title LIKE ? AND deleted = 0 "
        "ORDER BY add_time DESC";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, "%" + title + "%");
    return sqlSession->executeQuery<PtrNoticeDO>(sql, PtrNoticeMapper(), params);
}

int NoticeDAO::insert(const NoticeDO& notice)
{
    std::string sql = "INSERT INTO notice (id, title, content, creator, add_time) VALUES (?,?, ?, ?, ?)";
    SqlParams params;
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getId());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getTitle());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getContent());
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getCreator());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getAddTime());
    return sqlSession->executeUpdate(sql, params);
}

bool NoticeDAO::update(const NoticeDO& notice)
{
    std::string sql = "UPDATE notice SET title=?, content=?, view_num=view_num+1, editor=?, edit_time=? "
        "WHERE id=? AND deleted=0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, notice.getTitle());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getContent());
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getEditor());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getEditTime());
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getId());
    return sqlSession->executeUpdate(sql, params) > 0;
}

bool NoticeDAO::update1(const NoticeDO& notice)
{
    std::string sql = "UPDATE notice SET view_num=view_num+1, editor=?, edit_time=?, deleted=1 "
        "WHERE id=? ";
    SqlParams params;
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getEditor());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getEditTime());
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getId());
    return sqlSession->executeUpdate(sql, params) > 0;
}

bool NoticeDAO::update2(const NoticeDO& notice)
{
    std::string sql = "UPDATE notice SET view_num=view_num+1, editor=?, edit_time=?, deleted=0 "
        "WHERE id=? ";
    SqlParams params;
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getEditor());
    SQLPARAMS_PUSH(params, "s", std::string, notice.getEditTime());
    SQLPARAMS_PUSH(params, "bi", oatpp::UInt64, notice.getId());
    return sqlSession->executeUpdate(sql, params) > 0;
}

uint64_t NoticeDAO::count(const BoardQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM notice ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 执行查询
    return sqlSession->executeQueryNumerical(sql, params);
}

std::string NoticeDAO::queryConditionBuilder(const BoardQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    if (query->boardPublisherId) {

        sqlCondition << " AND `creator`=?";
        SQLPARAMS_PUSH(params, "i", int, query->boardPublisherId.getValue(0));
    }
    if (query->boardTitle) {

        sqlCondition << " AND title=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->boardTitle.getValue(""));
    }
    return sqlCondition.str();
}