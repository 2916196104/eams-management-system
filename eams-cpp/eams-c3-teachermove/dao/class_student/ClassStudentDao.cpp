#include "stdafx.h"
#include "ClassStudentDao.h"
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

uint64_t ClassStudentDAO::countByClassId(uint64_t classId)
{
    string sql = "SELECT count(id) FROM class_student WHERE deleted = 0 AND class_id = ?";
    return sqlSession->executeQueryNumerical(sql, "%ull", classId);
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

std::list<ClassStudentBaseInfo> ClassStudentDAO::selectStudentBaseWithPage(uint64_t classId, uint64_t pageIndex, uint64_t pageSize)
{
    if (pageIndex == 0) pageIndex = 1;
    if (pageSize == 0) pageSize = 10;
    const uint64_t offset = (pageIndex - 1) * pageSize;

    const std::string sql =
        "SELECT cs.student_id, s.name, s.gender "
        "FROM class_student cs "
        "LEFT JOIN student s ON s.id = cs.student_id "
        "WHERE cs.deleted = 0 AND cs.class_id = ? "
        "ORDER BY cs.id DESC LIMIT ?, ?";

    SqlParams params;
    SQLPARAMS_PUSH(params, "ll", int64_t, static_cast<int64_t>(classId));
    SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
    SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

    class ClassStudentBaseInfoMapper : public Mapper<ClassStudentBaseInfo>
    {
    public:
        ClassStudentBaseInfo mapper(ResultSet* resultSet) const override
        {
            ClassStudentBaseInfo info;
            if (!resultSet->isNull("student_id")) info.studentId = resultSet->getUInt64("student_id");
            if (!resultSet->isNull("name")) info.studentName = resultSet->getString("name");
            if (!resultSet->isNull("gender")) info.gender = resultSet->getInt("gender");
            return info;
        }
    };

    return sqlSession->executeQuery<ClassStudentBaseInfo, ClassStudentBaseInfoMapper>(sql, ClassStudentBaseInfoMapper(), params);
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