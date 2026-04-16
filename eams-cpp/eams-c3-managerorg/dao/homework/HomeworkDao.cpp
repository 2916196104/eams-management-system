#include "stdafx.h"
#include "HomeworkDao.h"
#include "HomeworkMapper.h"
#include <iostream>
#include "domain/query/backhomework/backhomeworkQuery.h"
using namespace std;

//通过id查询数据
PtrHomeworkDO HomeworkDao::getHomeworkById(int id) {
    // 编写SQL语句
    std::string sql = "SELECT * FROM homework WHERE id = ? AND deleted = 0";
    
    // 准备参数
    SqlParams params;
    params.emplace_back("i", std::make_shared<int>(id));
    
    // 执行查询
    PtrHomeworkDO result = nullptr;
    try {
        NULL_PTR_CHECK(sqlSession, "sqlSession is null");
        // 获取prepareStatement对象
        auto pstmt = sqlSession->getConnection()->prepareStatement(sql);
        // 设置参数
        pstmt->setInt(1, id);
        // 执行查询
        auto res = pstmt->executeQuery();
        // 处理查询结果
        if (res->next()) {
            result = std::make_shared<HomeworkDO>();
            result->setId(res->getInt("id"));
            result->setClassId(res->getInt("class_id"));
            result->setTitle(res->getString("title"));
            result->setContent(res->getString("content"));
            result->setCreator(res->getInt("creator"));
            result->setEditor(res->getInt("editor"));
            result->setDeleted(res->getInt("deleted"));
            result->setOrgId(res->getInt("org_id"));
        }
        // 释放资源
        if (res) res->close();
        if (pstmt) pstmt->close();
    } catch (const std::exception& e) {
        cerr << "ExecuteQuery Exception. " << e.what() << endl;
    }
    
    return result;
}

//分页查询数据
std::list<PtrHomeworkDO> HomeworkDao::queryHomeworkList(const GetHomeworkListQuery& query) {
    // 构建SQL语句
    std::string sql = "SELECT * FROM homework WHERE deleted = 0";
    
    // 准备参数
    SqlParams params;
    int paramIndex = 1;
    
    // 添加查询条件
    if (query.title && *query.title != "") {
        sql += " AND title LIKE ?";
        std::string likeTitle = "%" + *query.title + "%";
        params.emplace_back("s", std::make_shared<std::string>(likeTitle));
        paramIndex++;
    }
    
    // 添加排序
    sql += " ORDER BY add_time DESC";
    
    // 添加分页
    sql += " LIMIT ? OFFSET ?";
    int pageSize = query.pageSize ? *query.pageSize : 10;
    int pageIndex = query.pageIndex ? *query.pageIndex : 1;
    int offset = (pageIndex - 1) * pageSize;
    params.emplace_back("i", std::make_shared<int>(pageSize));
    params.emplace_back("i", std::make_shared<int>(offset));
    
    // 执行查询
    std::list<PtrHomeworkDO> homeworkList;
    try {
        NULL_PTR_CHECK(sqlSession, "sqlSession is null");
        // 获取prepareStatement对象
        auto pstmt = sqlSession->getConnection()->prepareStatement(sql);
        // 设置参数
        int pos = 1;
        for (auto& param : params) {
            if (param.key == "s") {
                pstmt->setString(pos, *static_cast<std::string*>(param.value.get()));
            } else if (param.key == "i") {
                pstmt->setInt(pos, *static_cast<int*>(param.value.get()));
            }
            pos++;
        }
        // 执行查询
        auto res = pstmt->executeQuery();
        // 处理查询结果
        while (res->next()) {
            auto homework = std::make_shared<HomeworkDO>();
            homework->setId(res->getInt("id"));
            homework->setClassId(res->getInt("class_id"));
            homework->setTitle(res->getString("title"));
            homework->setContent(res->getString("content"));
            homework->setCreator(res->getInt("creator"));
            homework->setEditor(res->getInt("editor"));
            homework->setDeleted(res->getInt("deleted"));
            homework->setOrgId(res->getInt("org_id"));
            homeworkList.push_back(homework);
        }
        // 释放资源
        if (res) res->close();
        if (pstmt) pstmt->close();
    } catch (const std::exception& e) {
        cerr << "ExecuteQuery Exception. " << e.what() << endl;
    }
    
    return homeworkList;
}

//通过作业标题查询数据
std::list<PtrHomeworkDO> HomeworkDao::queryHomeworkListByTitle(const std::string& title) {
    // 构建SQL语句
    std::string sql = "SELECT * FROM homework WHERE title = ? AND deleted = 0";
    
    // 执行查询
    std::list<PtrHomeworkDO> homeworkList;
    try {
        NULL_PTR_CHECK(sqlSession, "sqlSession is null");
        // 获取prepareStatement对象
        auto pstmt = sqlSession->getConnection()->prepareStatement(sql);
        // 设置参数
        pstmt->setString(1, title);
        // 执行查询
        auto res = pstmt->executeQuery();
        // 处理查询结果
        while (res->next()) {
            auto homework = std::make_shared<HomeworkDO>();
            homework->setId(res->getInt("id"));
            homework->setClassId(res->getInt("class_id"));
            homework->setTitle(res->getString("title"));
            homework->setContent(res->getString("content"));
            homework->setCreator(res->getInt("creator"));
            homework->setEditor(res->getInt("editor"));
            homework->setDeleted(res->getInt("deleted"));
            homework->setOrgId(res->getInt("org_id"));
            homeworkList.push_back(homework);
        }
        // 释放资源
        if (res) res->close();
        if (pstmt) pstmt->close();
    } catch (const std::exception& e) {
        cerr << "ExecuteQuery Exception. " << e.what() << endl;
    }
    
    return homeworkList;
}

//删除作业数据（支持单个和批量删除）
int HomeworkDao::deleteHomework(const std::list<int>& ids) {
    // 检查ids是否为空
    if (ids.empty()) {
        return 0;
    }
    
    // 构建SQL语句（软删除，将deleted字段设置为1）
    std::string sql = "UPDATE homework SET deleted = 1 WHERE id IN (";
    
    // 准备参数
    std::vector<int> idVector(ids.begin(), ids.end());
    for (size_t i = 0; i < idVector.size(); i++) {
        if (i > 0) {
            sql += ", ";
        }
        sql += "?";
    }
    sql += ")";
    
    // 执行删除操作
    int affectedRows = 0;
    try {
        NULL_PTR_CHECK(sqlSession, "sqlSession is null");
        // 获取prepareStatement对象
        auto pstmt = sqlSession->getConnection()->prepareStatement(sql);
        // 设置参数
        for (size_t i = 0; i < idVector.size(); i++) {
            pstmt->setInt(i + 1, idVector[i]);
        }
        // 执行更新操作
        affectedRows = pstmt->executeUpdate();
        // 释放资源
        if (pstmt) pstmt->close();
    } catch (const std::exception& e) {
        cerr << "ExecuteUpdate Exception. " << e.what() << endl;
    }
    
    return affectedRows;
}

//用于给下面的count，获取作业列表构建sql的查询条件
std::string HomeworkDao::queryConditionBuilder(const GetHomeworkListQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    if (query->title) {

        sqlCondition << " AND `title`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->title.getValue(""));
    }
    if (query->class_id) {

        sqlCondition << " AND class_id=?";
        SQLPARAMS_PUSH(params, "ll", std::int64_t, query->class_id.getValue(0));
    }
    if (query->creator) {

        sqlCondition << " AND creator=?";
        SQLPARAMS_PUSH(params, "ll", std::int64_t, query->creator.getValue(0));
    }
    return sqlCondition.str();
}

uint64_t HomeworkDao::count(const GetHomeworkListQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM homework ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 执行查询
    return sqlSession->executeQueryNumerical(sql, params);
}

//定义了分页查询
std::list<HomeworkDO> HomeworkDao::gethomeworklist(const GetHomeworkListQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT id,class_id,title,creator,add_time FROM homework ";
    // 构建查询条件
    sql += queryConditionBuilder(query, params);
    // 构建排序语句
    sql += " ORDER BY IFNULL(`add_time`, `edit_time`) DESC, `id` DESC ";
    // 构建分页条件
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);

    // 执行查询
    return sqlSession->executeQuery<HomeworkDO>(sql, GetHomeworkListMapper(), params);
}

//获取作业详情，点击会传入id，传回班级，标题，作业内容
PtrHomeworkDO HomeworkDao::gethomeworkdetail(int id)
{
    string sql = "SELECT class_id,title,content FROM homework WHERE id=?";
	// homework表中的id 是 int，使用 %i，但是数据库中id是 bigint
    return sqlSession->executeQueryOne<PtrHomeworkDO>(sql, PtrGetHomeworkDetailMapper(), "%i", id);
}