#include"points-ExchangeDAO.h"


int64_t ExchangeDAO::insert(const PtrExchangeDO& exchange)
{
    // Get school id
    string schoolIdSql = "SELECT school_id FROM student WHERE user_id = ? AND deleted = 0";
    int64_t schoolId = sqlSession->executeQueryNumerical(schoolIdSql, "ull", exchange->getStudentId());

    string sql = "INSERT INTO credit_exchange ("
        "id, add_time, edit_time, creator, editor, deleted, "
        "credit_mall_id, school_id, student_id, user_id, "
        "num, credit, verify_state"
        ") VALUES ("
        "?, NOW(), NOW(), ?, ?, 0, "
        "?, ?, ?, ?, "
        "?, ?, 0"
        ")";

    int64_t result = sqlSession->executeUpdate(sql, "ullssullullullull",
        exchange->getId(),
        exchange->getCreator(),
        exchange->getEditor(),
        exchange->getCreditMallId(),
        schoolId,
        exchange->getStudentId(),
        exchange->getUserId(),
        exchange->getNum(),
        exchange->getCredit()
    );

    if (result <= 0)
    {
        throw invalid_argument("insert error");
    }

    return result;
}

int64_t ExchangeDAO::insertCreditChangeRecord(const PtrExchangeDO& exchange, const int64_t& current_credit)
{
    string sql = "INSERT INTO student_credit_log ("
        " student_id, user_id, source_id, staff_id, school_id, "
        "change_type, add_time, remark, credit, current_credit"
        ") VALUES ("
        "?, ?, ?, ?, ?, "
        "?, ?, ?, ?, ?"
        ")";

    int64_t result = sqlSession->executeUpdate(sql, "llullullullullullullullullu",
        exchange->getStudentId(),
        exchange->getStudentId(),
        exchange->getUserId(),
        0,  // NULL replaced with 0
        exchange->getVerifyStaff(),
        exchange->getSchoolId(),
        2,  // change_type: 2 means deduction
        exchange->getAddTime(),
        0,  // NULL replaced with 0
        exchange->getCredit(),
        current_credit
    );

    if (result <= 0)
    {
        throw invalid_argument("insert table student_credit_log error");
    }
    return result;
}

int64_t ExchangeDAO::getStudentCurrentCredit(const int64_t& studentId)
{
    string sql = "SELECT credit FROM student "
        "WHERE user_id = ? AND deleted = 0";
    auto result = sqlSession->executeQueryNumerical(sql, "ull", studentId);
    return result;
}

int ExchangeDAO::deductStudentCredit(const int64_t& studentId, const int64_t& credit)
{
    string sql = "UPDATE student SET credit = credit - ? "
        "WHERE user_id = ? AND credit >= ?";
    int result = sqlSession->executeUpdate(sql, "ullullull", credit, studentId, credit);
    if (result <= 0) {
        throw invalid_argument("credit lacked");
    }
    return result;
}