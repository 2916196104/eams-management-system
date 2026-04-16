#include "stdafx.h"
#include "homeworkdao.h"
#include "homeworkmapper.h"
#include <sstream>

// 1. 获取列表总数
uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT COUNT(1) FROM homework WHERE deleted = 0";

    if (query->title && !query->title->empty()) {
        sql << " AND title LIKE '%" << query->title->c_str() << "%'";
    }

    return sqlSession->executeQueryNumerical(sql.str());
}

// 2. 获取分页列表
std::vector<HomeworkDTO::Wrapper> HomeworkDAO::selectPage(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT id, class_id, title, creator, add_time FROM homework WHERE deleted = 0";

    if (query->title && !query->title->empty()) {
        sql << " AND title LIKE '%" << query->title->c_str() << "%'";
    }

    uint64_t pageIndex = query->pageIndex;
    uint64_t pageSize = query->pageSize;
    uint64_t offset = (pageIndex - 1) * pageSize;

    sql << " LIMIT " << offset << ", " << pageSize;

    HomeworkMapper mapper;
    auto list = sqlSession->executeQuery<HomeworkDTO::Wrapper>(sql.str(), mapper);

    return std::vector<HomeworkDTO::Wrapper>(list.begin(), list.end());
}

// 3. 获取作业详情
HomeworkDetailDTO::Wrapper HomeworkDAO::selectDetail(const uint64_t& id)
{
    std::stringstream sql;
    sql << "SELECT id, class_id, title, content, creator, editor, add_time, edit_time, org_id "
        << "FROM homework WHERE deleted = 0 AND id = " << id;

    HomeworkDetailMapper mapper;
    return sqlSession->executeQueryOne<HomeworkDetailDTO::Wrapper>(sql.str(), mapper);
}

PtrHomeworkDO HomeworkDAO::selectById(const uint64_t& id) {
    // 直接把 id 拼到 SQL 里
    std::string sql = "SELECT * FROM homework WHERE id = " + std::to_string(id);
    // 调用无参数的 executeQueryOne
    return sqlSession->executeQueryOne<PtrHomeworkDO>(sql, PtrHomeworkMapper());
}