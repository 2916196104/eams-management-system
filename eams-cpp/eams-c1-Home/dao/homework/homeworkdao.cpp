#include "stdafx.h"
#include "homeworkdao.h"
#include "homeworkmapper.h"
#include <sstream>

uint64_t HomeworkDAO::count(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT COUNT(1) FROM homework WHERE deleted = 0";

    if (query->title && !query->title->empty()) {
        sql << " AND title LIKE '%" << query->title->c_str() << "%'";
    }

    std::string sqlStr = sql.str();
    return sqlSession->executeQueryNumerical(sqlStr);
}

std::vector<HomeworkDTO::Wrapper> HomeworkDAO::selectPage(const HomeworkQuery::Wrapper& query)
{
    std::stringstream sql;
    sql << "SELECT id, class_id, title, creator, add_time FROM homework WHERE deleted = 0";

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
    sql << "SELECT id, class_id, title, content, creator, editor, add_time, edit_time, org_id "
        << "FROM homework WHERE deleted = 0 AND id = " << id;

    HomeworkDetailMapper mapper;
    return sqlSession->executeQueryOne<HomeworkDetailDTO::Wrapper>(sql.str(), mapper);
}

uint64_t HomeworkDAO::insert(const HomeworkDO& obj)
{
    std::stringstream sql;
    sql << "INSERT INTO homework (id, class_id, title, content, creator, org_id, add_time, deleted) VALUES ("
        << obj.getId() << ", "
        << obj.getClassId() << ", "
        << "'" << obj.getTitle() << "', "
        << "'" << obj.getContent() << "', "
        << obj.getCreator() << ", "
        << obj.getOrgId() << ", "
        << "NOW(), 0)";
    return sqlSession->executeUpdate(sql.str());
}

