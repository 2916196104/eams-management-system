#include "stdafx.h"
#include "LessonDao.h"
#include "LessonMapper.h"

std::string LessonDAO::queryConditionBuilder(const LessonQuery::Wrapper& query, SqlParams& params)
{
    std::string whereSql = " WHERE deleted = 0";
    if (!query) {
        return whereSql;
    }

    if (query->title && !query->title->empty()) {
        whereSql += " AND title LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + query->title.getValue("") + "%");
    }

    if (query->course_id && !query->course_id->empty()) {
        whereSql += " AND course_id = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->course_id.getValue("0")));
    }

    if (query->class_id && !query->class_id->empty()) {
        whereSql += " AND class_id = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->class_id.getValue("0")));
    }

    if (query->teacher_id && !query->teacher_id->empty()) {
        whereSql += " AND teacher_id = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->teacher_id.getValue("0")));
    }

    if (query->date && !query->date->empty()) {
        whereSql += " AND date = ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->date.getValue(""));
    }

    if (query->state && !query->state->empty()) {
        whereSql += " AND state = ?";
        SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->state.getValue("0")));
    }

    if (query->bookable && !query->bookable->empty()) {
        whereSql += " AND bookable = ?";
        SQLPARAMS_PUSH(params, "i", int32_t, std::stoi(query->bookable.getValue("0")));
    }

    if (query->school_id && !query->school_id->empty()) {
        whereSql += " AND school_id = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->school_id.getValue("0")));
    }

    if (query->org_id && !query->org_id->empty()) {
        whereSql += " AND org_id = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, std::stoll(query->org_id.getValue("0")));
    }

    return whereSql;
}

uint64_t LessonDAO::count(const LessonQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT COUNT(*) FROM lesson ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<LessonDO> LessonDAO::selectWithPage(const LessonQuery::Wrapper& query)
{
    SqlParams params;
    v_uint64 pageIndex = query && query->pageIndex ? query->pageIndex.getValue(1) : static_cast<v_uint64>(1);
    v_uint64 pageSize = query && query->pageSize ? query->pageSize.getValue(10) : static_cast<v_uint64>(10);
    if (pageIndex == 0) pageIndex = 1;
    if (pageSize == 0) pageSize = 10;
    v_uint64 offset = (pageIndex - 1) * pageSize;

    std::string sql = "SELECT id, title, sn, course_id, schedule_id, class_id, room_id, date, "
        "start_time, end_time, creator, editor, add_time, edit_time, deleted, "
        "dec_count, remark, teach_type, on_trial, trial_result, state, close_time, "
        "close_operator, teacher_id, bookable, school_id, org_id "
        "FROM lesson ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "ull", uint64_t, offset);
    SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);

    return sqlSession->executeQuery<LessonDO>(sql, LessonMapper(), params);
}

PtrLessonDO LessonDAO::selectById(uint64_t id)
{
    std::string sql = "SELECT id, title, sn, course_id, schedule_id, class_id, room_id, date, "
        "start_time, end_time, creator, editor, add_time, edit_time, deleted, "
        "dec_count, remark, teach_type, on_trial, trial_result, state, close_time, "
        "close_operator, teacher_id, bookable, school_id, org_id "
        "FROM lesson WHERE id = ? AND deleted = 0 LIMIT 1";
    return sqlSession->executeQueryOne<PtrLessonDO>(sql, PtrLessonMapper(), "%ull", id);
}

uint64_t LessonDAO::sumFinishedDecCountByClassId(uint64_t classId)
{
    std::string sql =
        "SELECT IFNULL(SUM(dec_count), 0) FROM lesson "
        "WHERE deleted = 0 AND class_id = ? "
        "AND ((date IS NOT NULL AND CONCAT(date, ' ', end_time) < NOW()) "
        "OR (date IS NULL AND end_time < CURTIME()))";
    return sqlSession->executeQueryNumerical(sql, "%ull", classId);
}

uint64_t LessonDAO::insert(const LessonDO& data)
{
    std::string sql = "INSERT INTO lesson (title, sn, course_id, schedule_id, class_id, room_id, "
        "date, start_time, end_time, creator, editor, add_time, edit_time, deleted, "
        "dec_count, remark, teach_type, on_trial, trial_result, state, close_time, "
        "close_operator, teacher_id, bookable, school_id, org_id) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    return sqlSession->executeUpdate(sql,
        "%s", data.getTitle().c_str(),
        "%i", data.getSn(),
        "%lld", data.getCourseId(),
        "%lld", data.getScheduleId(),
        "%lld", data.getClassId(),
        "%lld", data.getRoomId(),
        "%s", data.getDate().c_str(),
        "%s", data.getStartTime().c_str(),
        "%s", data.getEndTime().c_str(),
        "%lld", data.getCreator(),
        "%lld", data.getEditor(),
        "%s", data.getAddTime().c_str(),
        "%s", data.getEditTime().c_str(),
        "%i", data.getDeleted() ? 1 : 0,
        "%ui", data.getDecCount(),
        "%s", data.getRemark().c_str(),
        "%i", data.getTeachType(),
        "%i", data.getOnTrial() ? 1 : 0,
        "%s", data.getTrialResult().c_str(),
        "%i", data.getState(),
        "%s", data.getCloseTime().c_str(),
        "%lld", data.getCloseOperator(),
        "%lld", data.getTeacherId(),
        "%i", data.getBookable() ? 1 : 0,
        "%lld", data.getSchoolId(),
        "%lld", data.getOrgId()
    );
}

uint64_t LessonDAO::updateById(const LessonDO& data)
{
    std::string sql = "UPDATE lesson SET title=?, sn=?, course_id=?, schedule_id=?, class_id=?, "
        "room_id=?, date=?, start_time=?, end_time=?, editor=?, edit_time=?, "
        "deleted=?, dec_count=?, remark=?, teach_type=?, on_trial=?, "
        "trial_result=?, state=?, close_time=?, close_operator=?, teacher_id=?, "
        "bookable=?, school_id=?, org_id=? WHERE id=?";

    return sqlSession->executeUpdate(sql,
        "%s", data.getTitle().c_str(),
        "%i", data.getSn(),
        "%lld", data.getCourseId(),
        "%lld", data.getScheduleId(),
        "%lld", data.getClassId(),
        "%lld", data.getRoomId(),
        "%s", data.getDate().c_str(),
        "%s", data.getStartTime().c_str(),
        "%s", data.getEndTime().c_str(),
        "%lld", data.getEditor(),
        "%s", data.getEditTime().c_str(),
        "%i", data.getDeleted() ? 1 : 0,
        "%ui", data.getDecCount(),
        "%s", data.getRemark().c_str(),
        "%i", data.getTeachType(),
        "%i", data.getOnTrial() ? 1 : 0,
        "%s", data.getTrialResult().c_str(),
        "%i", data.getState(),
        "%s", data.getCloseTime().c_str(),
        "%lld", data.getCloseOperator(),
        "%lld", data.getTeacherId(),
        "%i", data.getBookable() ? 1 : 0,
        "%lld", data.getSchoolId(),
        "%lld", data.getOrgId(),
        "%ull", data.getId()
    );
}

uint64_t LessonDAO::deleteById(uint64_t id)
{
    std::string sql = "UPDATE lesson SET deleted=1 WHERE id=?";
    return sqlSession->executeUpdate(sql, "%ull", id);
}