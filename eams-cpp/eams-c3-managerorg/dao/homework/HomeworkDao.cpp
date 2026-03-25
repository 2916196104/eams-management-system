#include "stdafx.h"
#include "HomeworkDao.h"
#include "HomeworkMapper.h"
#include <iostream>
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
