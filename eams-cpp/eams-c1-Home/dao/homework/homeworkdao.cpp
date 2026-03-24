#include "stdafx.h"
#include "homeworkdao.h"
#include "homeworkmapper.h"
#include <sstream>

uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT COUNT(1) FROM homework WHERE 1=1";

    if (query->title && !query->title->empty()) {
        sql << " AND title LIKE '%" << query->title->c_str() << "%'";
    }

    std::string sqlStr = sql.str();
    return sqlSession->executeQueryNumerical(sqlStr);
}

std::vector<HomeworkDTO::Wrapper> HomeworkDAO::selectPage(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT id, title, '' AS course_name, publisher AS teacher_name FROM homework WHERE 1=1";

    if (query->title && !query->title->empty()) {
        sql << " AND title LIKE '%" << query->title->c_str() << "%'";
    }

    sql << " LIMIT " << (query->pageIndex - 1) * query->pageSize << ", " << query->pageSize;

    HomeworkMapper mapper;
    auto list = sqlSession->executeQuery<HomeworkDTO::Wrapper>(sql.str(), mapper);
    
    std::vector<HomeworkDTO::Wrapper> vec(list.begin(), list.end());
    return vec;
}

HomeworkDetailDTO::Wrapper HomeworkDAO::selectDetail(uint64_t id)
{
    std::stringstream sql;
    sql << "SELECT id, title, '' AS course_name, '' AS start_time, '' AS end_time, publisher AS teacher_name "
        << "FROM homework WHERE id = " << id;

    HomeworkDetailMapper mapper;
    return sqlSession->executeQueryOne<HomeworkDetailDTO::Wrapper>(sql.str(), mapper);
}
