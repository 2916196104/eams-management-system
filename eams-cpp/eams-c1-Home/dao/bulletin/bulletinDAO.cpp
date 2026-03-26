#include "stdafx.h"
#include"bulletinMapper.h"
#include "bulletinDAO.h"
#include "domain/dto/bulletin/bulletinDTO.h"


/**
 * 查询最新一条公告
 * 查询逻辑：按照sort_num倒序，id倒序，取第一条
 */
ptrbulletinDO bulletinDAO::selectLatest()
{
    string sql = "SELECT id,title,cover,content,type,state,sort_num,add_time,edit_time,creator,editor,deleted "
        "FROM advertisement "
        "WHERE deleted=0 AND state=1 "
        "ORDER BY sort_num DESC, id DESC "
        "LIMIT 1";

    // 使用PtrBulletinMapper来映射结果到ptrbulletinDO
    return sqlSession->executeQueryOne<ptrbulletinDO>(sql, PtrBulletinMapper());
}

/**
 * 查询总记录数
 * 查询条件：deleted=0 AND state=1
 */
uint64_t bulletinDAO::count()
{
    string sql = "SELECT COUNT(*) FROM advertisement WHERE deleted=0 AND state=1";

    return sqlSession->executeQueryNumerical(sql);
}

/**
 * 分页查询公告
 * 查询条件：deleted=0 AND state=1
 * 排序：sort_num DESC, id DESC
 */
std::list<bulletinDO> bulletinDAO::selectWithPage(const PageQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT id,title,cover,content,type,state,sort_num,add_time,edit_time,creator,editor,deleted "
        "FROM advertisement "
        "WHERE deleted=0 AND state=1 "
        "ORDER BY sort_num DESC, id DESC ";

    // 计算分页偏移量
    int offset = (query->pageIndex - 1) * query->pageSize;

    // 添加分页限制
    sql += "LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);

    // 使用BulletinMapper来映射结果到bulletinDO
    return sqlSession->executeQuery<bulletinDO>(sql, BulletinMapper(), params);
}



/**
 * 聚合查询所有未读数
 * 查询逻辑：
 * 1. 作业未读数(homework_count)：在指定班级中，未完成的作业
 * 2. 点评记录未读数(evaluate_count)：学生被点评后，点评时间大于学生记录的最近查看时间
 * 3. 成绩未读数(grade_count)：新增成绩时间大于学生记录的最近查看时间
 */
std::shared_ptr<redDO> redDAO::getUnreadCounts(int64_t studentId)
{
    // 构造SQL查询
    string sql = R"(
        SELECT 
            (SELECT COUNT(0) 
             FROM homework 
             WHERE class_id IN (
                 SELECT class_id 
                 FROM class_student 
                 WHERE student_id = ? AND deleted = 0
             ) 
             AND id NOT IN (
                 SELECT homework_id 
                 FROM homework_record 
                 WHERE student_id = ?
             ) 
             AND deleted = 0) AS homework_count,
            
            (SELECT COUNT(0) 
             FROM lesson_student 
             WHERE student_id = ? 
             AND evaluate_time IS NOT NULL 
             AND evaluate_time > (
                 SELECT redpoint_evaluate 
                 FROM student 
                 WHERE id = ?
             )) AS evaluate_count,
            
            (SELECT COUNT(0) 
             FROM grade_record 
             WHERE student_id = ? 
             AND add_time > (
                 SELECT redpoint_grade 
                 FROM student 
                 WHERE id = ?
             )) AS grade_count
    )";

    // 准备参数
    SqlParams params;

    // 作业未读数参数
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // 第一个student_id
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // homework_record中的student_id

    // 点评记录未读数参数
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // lesson_student中的student_id
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // student表中的id

    // 成绩未读数参数
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // grade_record中的student_id
    SQLPARAMS_PUSH(params, "l", int64_t, studentId);  // student表中的id

    // 使用PtrRedMapper来映射结果到ptrRedDO
    return sqlSession->executeQueryOne<ptrRedDO>(sql, PtrRedMapper(), params);
}