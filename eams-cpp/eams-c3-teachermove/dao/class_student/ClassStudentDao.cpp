#include "stdafx.h"
#include "ClassStudentDAO.h"
#include "ClassStudentMapper.h"

// 1. 查询总条数 (用于分页计算)
uint64_t ClassStudentDAO::count(const StuListQuery::Wrapper& query)
{
    string sql = "SELECT count(id) FROM class_student ";
    SqlParams params;

    sql += "WHERE deleted = 0 ";

    // 执行查询并返回数字
    return sqlSession->executeQueryNumerical(sql, params);
}

// 2. 分页查询列表
std::list<PtrClassStudentDO> ClassStudentDAO::selectAll(const StuListQuery::Wrapper& query)
{
    string sql = "SELECT id, class_id, student_id, add_time, creator, reason, deleted, remark, consume_course_id FROM class_student WHERE deleted = 0 ";
    SqlParams params;

    // 分页处理 LIMIT ?,?
    sql += "LIMIT ?,?";
    SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
    SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));

    // 传入 ClassStudentMapper() 解析返回结果集
    return sqlSession->executeQuery<PtrClassStudentDO>(sql, ClassStudentMapper(), params);
}

// 3. 根据学员ID查课程关联
std::list<PtrClassStudentDO> ClassStudentDAO::selectByStudentId(const std::string& studentId)
{
    string sql = "SELECT id, class_id, student_id, add_time, creator, reason, deleted, remark, consume_course_id FROM class_student WHERE deleted = 0 AND student_id = ?";

    return sqlSession->executeQuery<PtrClassStudentDO>(sql, ClassStudentMapper(), "%s", studentId);
}

// 4. 插入一条新数据
uint64_t ClassStudentDAO::insert(const PtrClassStudentDO& doObj)
{
    string sql = "INSERT INTO class_student (id, class_id, student_id, add_time, creator, reason, deleted, remark, consume_course_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    SqlParams params;

    // 绑定每一个字段参数
    SQLPARAMS_PUSH(params, "ll", int64_t, doObj->getClassId());
    SQLPARAMS_PUSH(params, "ll", int64_t, doObj->getStudentId());
    SQLPARAMS_PUSH(params, "s", std::string, doObj->getAddTime());
    SQLPARAMS_PUSH(params, "ll", int64_t, doObj->getCreator());
    SQLPARAMS_PUSH(params, "i", int32_t, doObj->getReason());
    SQLPARAMS_PUSH(params, "i", int32_t, doObj->getDeleted() ? 1 : 0);
    SQLPARAMS_PUSH(params, "s", std::string, doObj->getRemark());
    SQLPARAMS_PUSH(params, "ll", int64_t, doObj->getConsumeCourseId());

    return sqlSession->executeUpdate(sql, params);
}