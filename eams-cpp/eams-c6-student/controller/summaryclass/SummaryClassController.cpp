#include "stdafx.h"
#include "SummaryClassController.h"
#include "ServerInfo.h"
#include <sstream>

SummaryClassPageJsonVO::Wrapper SummaryClassController::excuteSummaryClassQuery(const SummaryClassQuery::Wrapper& query)
{
    return {};
    //auto jvo = SummaryClassPageJsonVO::createShared();
    //auto pageData = SummaryClassPageDTO::createShared();
    //pageData->rows = {};

    //if (!query || query->pageIndex <= 0 || query->pageSize <= 0) {
    //    jvo->code = 9999;
    //    jvo->message = "Invalid pagination parameters.";
    //    return jvo;
    //}

    //ConnPool pool(
    //    ServerInfo::getInstance().getDbHost() + ":" + std::to_string(ServerInfo::getInstance().getDbPort()) + "/" + ServerInfo::getInstance().getDbName(),
    //    ServerInfo::getInstance().getDbUsername(),
    //    ServerInfo::getInstance().getDbPassword(),
    //    10
    //);
    //Connection* conn = pool.GetConnection();
    //if (!conn) {
    //    jvo->code = 9999;
    //    jvo->message = "Database connection failed.";
    //    return jvo;
    //}

    //try {
    //    std::string countSql = "SELECT COUNT(*) FROM student_course sc "
    //        "LEFT JOIN student s ON sc.student_id = s.id "
    //        "LEFT JOIN course c ON sc.course_id = c.id "
    //        "WHERE sc.deleted = 0 ";

    //    if (query->studentName && !query->studentName->empty()) countSql += " AND s.name LIKE ? ";
    //    if (query->courseName && !query->courseName->empty()) countSql += " AND c.name LIKE ? ";

    //    PreparedStatement* pstmtCount = conn->prepareStatement(countSql);
    //    int pIdx = 1;
    //    if (query->studentName && !query->studentName->empty()) pstmtCount->setString(pIdx++, "%" + std::string(query->studentName->c_str()) + "%");
    //    if (query->courseName && !query->courseName->empty()) pstmtCount->setString(pIdx++, "%" + std::string(query->courseName->c_str()) + "%");

    //    ResultSet* resCount = pstmtCount->executeQuery();
    //    if (resCount->next()) {
    //        pageData->total = resCount->getInt64(1);
    //    }
    //    delete resCount;
    //    delete pstmtCount;

    //    int total = (int)pageData->total.getValue(0);
    //    int size = query->pageSize.getValue(10);
    //    pageData->pages = (total + size - 1) / size;
    //    pageData->pageIndex = query->pageIndex;
    //    pageData->pageSize = query->pageSize;

    //    std::string dataSql = R"(
    //        SELECT 
    //            s.name AS stu_name, c.name AS cou_name, sc.id AS sc_id, 
    //            sc.count_lesson_total, sc.count_lesson_complete, 
    //            (SELECT COUNT(*) FROM lesson_student WHERE consume_student_course_id = sc.id AND sign_state = 1) AS up_cnt, 
    //            (SELECT COUNT(*) FROM lesson_student WHERE consume_student_course_id = sc.id AND sign_state = 3) AS leave_cnt, 
    //            (SELECT COUNT(*) FROM lesson_student WHERE consume_student_course_id = sc.id AND sign_state = 4) AS absent_cnt, 
    //            (SELECT COUNT(*) FROM lesson_student WHERE consume_student_course_id = sc.id AND sign_state = 2) AS makeup_cnt 
    //        FROM student_course sc 
    //        LEFT JOIN student s ON sc.student_id = s.id 
    //        LEFT JOIN course c ON sc.course_id = c.id 
    //        WHERE sc.deleted = 0 
    //    )";

    //    if (query->studentName && !query->studentName->empty()) dataSql += " AND s.name LIKE ? ";
    //    if (query->courseName && !query->courseName->empty()) dataSql += " AND c.name LIKE ? ";
    //    dataSql += " LIMIT ?, ? ";

    //    PreparedStatement* pstmtData = conn->prepareStatement(dataSql);
    //    pIdx = 1;
    //    if (query->studentName && !query->studentName->empty()) pstmtData->setString(pIdx++, "%" + std::string(query->studentName->c_str()) + "%");
    //    if (query->courseName && !query->courseName->empty()) pstmtData->setString(pIdx++, "%" + std::string(query->courseName->c_str()) + "%");

    //    int offset = (query->pageIndex - 1) * query->pageSize;
    //    pstmtData->setInt(pIdx++, offset);
    //    pstmtData->setInt(pIdx++, query->pageSize);

    //    ResultSet* resData = pstmtData->executeQuery();
    //    while (resData->next()) {
    //        auto row = SummaryClassDTO::createShared();
    //        row->studentName = resData->getString("stu_name").c_str();
    //        row->courseName = resData->getString("cou_name").c_str();
    //        row->totalLessons = resData->getInt("count_lesson_total");
    //        row->usedLessons = resData->getInt("count_lesson_complete");
    //        row->remainingLessons = row->totalLessons - row->usedLessons;

    //        std::ostringstream oss;
    //        oss << "\xE4\xB8\x8A " << resData->getInt("up_cnt")       // "ÉÏ "
    //            << " \xE5\x81\x87 " << resData->getInt("leave_cnt")    // " ¼Ù "
    //            << " \xE6\x97\xb7 " << resData->getInt("absent_cnt")   // " ¿õ "
    //            << " \xE8\xA1\xA5 " << resData->getInt("makeup_cnt");  // " ²¹ "
    //        row->attendanceRecord = oss.str().c_str();

    //        pageData->rows->push_back(row);
    //    }
    //    delete resData;
    //    delete pstmtData;

    //    jvo->success(pageData);

    //}
    //catch (std::exception& e) {
    //    jvo->code = 9999;
    //    jvo->message = e.what();
    //}

    //pool.ReleaseConnection(conn);
    //return jvo;
}