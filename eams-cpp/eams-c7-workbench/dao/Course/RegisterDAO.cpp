#include "stdafx.h"
#include "RegisterDAO.h"
#include "RegisterMapper.h"

// 辅助函数：转义字符串中的单引号（MySQL 转义）
static std::string escapeSqlString(const std::string& str) {
    std::string result;
    result.reserve(str.size() * 2);
    for (char c : str) {
        if (c == '\'') result.push_back('\'');
        result.push_back(c);
    }
    return result;
}

// 专门用于查询单个 ID 的 Mapper
class IdMapper : public Mapper<int64_t> {
public:
    int64_t mapper(ResultSet* resultSet) const override {
        return resultSet->getInt64(1);  // 只取第一列
    }
};

// ========== RegisterDAO 实现 ==========
uint64_t RegisterDAO::insert(RegisterDO& data) {
    if (!sqlSession) {
        printf("[ERROR] RegisterDAO::insert - sqlSession is null\n");
        return 0;
    }

    try {
        // 转义字符串字段
        std::string startDate = escapeSqlString(data.getStartDate());
        std::string expireDate = escapeSqlString(data.getExpireDate());
        std::string remark = escapeSqlString(data.getRemark());
        std::string addTime = escapeSqlString(data.getAddTime());

        // 使用 std::string 动态构建 SQL
        std::string sql = "INSERT INTO student_course ("
            "id, student_id, course_id, subject_id, start_date, expire_date, "
            "count_lesson_total, amount, discount_amount, paid_amount, remark, "
            "creator, add_time, deleted, verify_state) VALUES ("
            + std::to_string(data.getId()) + ", "
            + std::to_string(data.getStudentId()) + ", "
            + std::to_string(data.getCourseId()) + ", "
            + std::to_string(data.getSubjectId()) + ", '"
            + startDate + "', '"
            + expireDate + "', "
            + std::to_string(data.getCountLessonTotal()) + ", "
            + std::to_string(data.getAmount()) + ", "
            + std::to_string(data.getDiscountAmount()) + ", "
            + std::to_string(data.getPaidAmount()) + ", '"
            + remark + "', "
            + std::to_string(data.getCreator()) + ", '"
            + addTime + "', "
            + std::to_string(data.getDeleted()) + ", "
            + std::to_string(data.getVerifyState()) + ")";

        int64_t affectedRows = sqlSession->executeUpdate(sql);
        return (affectedRows > 0) ? static_cast<uint64_t>(affectedRows) : 0;
    }
    catch (const std::exception& e) {
        printf("[ERROR] RegisterDAO::insert - %s\n", e.what());
        return 0;
    }
    catch (...) {
        printf("[ERROR] RegisterDAO::insert - unknown exception\n");
        return 0;
    }
}

int64_t RegisterDAO::selectStudentIdByName(const char* name) {
    if (!sqlSession) {
        printf("[ERROR] selectStudentIdByName - sqlSession is null\n");
        return 0;
    }
    if (!name || !*name) {
        printf("[WARN] selectStudentIdByName - empty name\n");
        return 0;
    }

    try {
        // 转义姓名中的单引号
        std::string safeName = escapeSqlString(name);

        // 拼接 SQL 字符串
        std::string sql = "SELECT id FROM student WHERE name = '" + safeName + "'";

        printf("[DEBUG] selectStudentIdByName - executing: %s\n", sql.c_str());

        IdMapper mapper;
        auto list = sqlSession->executeQuery<int64_t, IdMapper>(sql, mapper);
        if (list.empty()) {
            printf("[WARN] selectStudentIdByName - no student found with name='%s'\n", name);
            return 0;
        }
        int64_t id = list.front();
        printf("[DEBUG] selectStudentIdByName - found id=%lld\n", id);
        return id;
    }
    catch (const std::exception& e) {
        printf("[ERROR] selectStudentIdByName - exception: %s\n", e.what());
        return 0;
    }
    catch (...) {
        printf("[ERROR] selectStudentIdByName - unknown exception\n");
        return 0;
    }
}

int64_t RegisterDAO::selectCourseIdByName(const char* name) {
    if (!sqlSession) {
        printf("[ERROR] selectCourseIdByName - sqlSession is null\n");
        return 0;
    }
    if (!name || !*name) {
        printf("[WARN] selectCourseIdByName - empty name\n");
        return 0;
    }

    try {
        std::string safeName = escapeSqlString(name);
        std::string sql = "SELECT id FROM course WHERE name = '" + safeName + "'";

        printf("[DEBUG] selectCourseIdByName - executing: %s\n", sql.c_str());

        IdMapper mapper;
        auto list = sqlSession->executeQuery<int64_t, IdMapper>(sql, mapper);
        if (list.empty()) {
            printf("[WARN] selectCourseIdByName - no course found with name='%s'\n", name);
            return 0;
        }
        int64_t id = list.front();
        printf("[DEBUG] selectCourseIdByName - found id=%lld\n", id);
        return id;
    }
    catch (const std::exception& e) {
        printf("[ERROR] selectCourseIdByName - %s\n", e.what());
        return 0;
    }
    catch (...) {
        return 0;
    }
}

int64_t RegisterDAO::selectSubjectIdByName(const char* name) {
    if (!sqlSession) {
        printf("[ERROR] selectSubjectIdByName - sqlSession is null\n");
        return 0;
    }
    if (!name || !*name) {
        printf("[WARN] selectSubjectIdByName - empty name\n");
        return 0;
    }

    try {
        std::string safeName = escapeSqlString(name);
        std::string sql = "SELECT id FROM subject WHERE name = '" + safeName + "'";

        printf("[DEBUG] selectSubjectIdByName - executing: %s\n", sql.c_str());

        IdMapper mapper;
        auto list = sqlSession->executeQuery<int64_t, IdMapper>(sql, mapper);
        if (list.empty()) {
            printf("[WARN] selectSubjectIdByName - no subject found with name='%s'\n", name);
            return 0;
        }
        int64_t id = list.front();
        printf("[DEBUG] selectSubjectIdByName - found id=%lld\n", id);
        return id;
    }
    catch (const std::exception& e) {
        printf("[ERROR] selectSubjectIdByName - %s\n", e.what());
        return 0;
    }
    catch (...) {
        return 0;
    }
}