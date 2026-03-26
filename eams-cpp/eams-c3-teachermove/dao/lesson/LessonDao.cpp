#include "stdafx.h"
#include "LessonDAO.h"
#include "LessonMapper.h"

std::string LessonDAO::queryConditionBuilder(const LessonQuery::Wrapper& query, SqlParams& params)
{
    std::stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";

    // 课程名称（模糊查询）
    if (query->title) {
        sqlCondition << " AND `title` LIKE CONCAT('%',?,'%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->title.getValue(""));
    }

    // 适用学校（精确匹配）
    if (query->schoolId) {
        sqlCondition << " AND `school_id`=?";
        SQLPARAMS_PUSH(params, "ll", long long, query->schoolId.getValue(0));
    }

    // 科目（精确匹配）
    if (query->courseId) {
        sqlCondition << " AND `course_id`=?";
        SQLPARAMS_PUSH(params, "ll", long long, query->courseId.getValue(0));
    }

    // 状态（精确匹配）
    if (query->state) {
        sqlCondition << " AND `state`=?";
        SQLPARAMS_PUSH(params, "i", int, query->state.getValue(0));
    }

    // 适用年级（精确匹配）
    if (query->classId) {
        sqlCondition << " AND `class_id`=?";
        SQLPARAMS_PUSH(params, "ll", long long, query->classId.getValue(0));
    }

    // 注意：如果业务还需要其他筛选（如机构ID隔离），可以继续添加
    // 例如租户隔离：sqlCondition << " AND `org_id`=?"; 并添加对应参数

    return sqlCondition.str();
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
    std::string sql = "SELECT id, title, sn, course_id, schedule_id, class_id, room_id, date, "
        "start_time, end_time, creator, editor, add_time, edit_time, deleted, "
        "dec_count, remark, teach_type, on_trial, trial_result, state, close_time, "
        "close_operator, teacher_id, bookable, school_id, org_id "
        "FROM lesson ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY IFNULL(`edit_time`, `add_time`) DESC, `id` DESC ";
    sql += " LIMIT " + std::to_string((query->pageIndex - 1) * query->pageSize) + "," +
        std::to_string(query->pageSize);

    return sqlSession->executeQuery<LessonDO>(sql, LessonMapper(), params);
}

PtrLessonDO LessonDAO::selectById(long long id)
{
    std::string sql = "SELECT id, title, sn, course_id, schedule_id, class_id, room_id, date, "
        "start_time, end_time, creator, editor, add_time, edit_time, deleted, "
        "dec_count, remark, teach_type, on_trial, trial_result, state, close_time, "
        "close_operator, teacher_id, bookable, school_id, org_id "
        "FROM lesson WHERE id=?";
    return sqlSession->executeQueryOne<PtrLessonDO>(sql, PtrLessonMapper(), "%lld", id);
}

int LessonDAO::insert(const LessonDO& data)
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
        "%i", data.getDeleted(),
        "%c", data.getDecCount(),
        "%s", data.getRemark().c_str(),
        "%i", data.getTeachType(),
        "%i", data.getOnTrial(),
        "%s", data.getTrialResult().c_str(),
        "%i", data.getState(),
        "%s", data.getCloseTime().c_str(),
        "%lld", data.getCloseOperator(),
        "%lld", data.getTeacherId(),
        "%i", data.getBookable(),
        "%lld", data.getSchoolId(),
        "%lld", data.getOrgId()
    );
}

int LessonDAO::updateById(const LessonDO& data)
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
        "%i", data.getDeleted(),
        "%c", data.getDecCount(),
        "%s", data.getRemark().c_str(),
        "%i", data.getTeachType(),
        "%i", data.getOnTrial(),
        "%s", data.getTrialResult().c_str(),
        "%i", data.getState(),
        "%s", data.getCloseTime().c_str(),
        "%lld", data.getCloseOperator(),
        "%lld", data.getTeacherId(),
        "%i", data.getBookable(),
        "%lld", data.getSchoolId(),
        "%lld", data.getOrgId(),
        "%lld", data.getId()
    );
}

int LessonDAO::deleteById(long long id)
{
    std::string sql = "UPDATE lesson SET deleted=1 WHERE id=?";
    return sqlSession->executeUpdate(sql, "%lld", id);
}