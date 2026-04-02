#include "stdafx.h"
#include "TimetableDAO.h"
#include "TimetableMapper.h"

/**
 * 构建课次基础查询条件
 * 当前按课次日期过滤数据
 */
std::string TimetableDAO::lessonBaseConditionBuilder(const std::string& studentId,
	const std::string& queryDate,
	SqlParams& params)
{
	std::stringstream sqlCondition;
	// 过滤逻辑删除数据
	sqlCondition << " WHERE l.deleted = 0 ";
	// 按日期过滤课次
	sqlCondition << " AND l.date = ? ";
	// 绑定日期参数
	SQLPARAMS_PUSH(params, "s", std::string, queryDate);
	return sqlCondition.str();
}

/**
 * 构建课表分组查询条件
 * 课表分组包含已入班正式课，以及已提交预约待审核/审核通过的预约课
 */
std::string TimetableDAO::lessonSectionConditionBuilder(const std::string& studentId,
	const std::string& queryDate,
	SqlParams& params)
{
	std::stringstream sqlCondition;
	// 先拼接基础条件
	sqlCondition << lessonBaseConditionBuilder(studentId, queryDate, params);

	// 过滤课表分组数据
	sqlCondition << " AND ( ";
	// 条件一：学生已经在该班级
	sqlCondition << " EXISTS ( ";
	sqlCondition << "     SELECT 1 FROM class_student cs ";
	sqlCondition << "     WHERE cs.class_id = l.class_id ";
	sqlCondition << "       AND cs.student_id = ? ";
	sqlCondition << "       AND cs.deleted = 0 ";
	sqlCondition << " ) ";
	// 条件二：学生已经提交该课次预约且状态为待审核或审核通过
	sqlCondition << " OR EXISTS ( ";
	sqlCondition << "     SELECT 1 FROM appointment ap ";
	sqlCondition << "     WHERE ap.lesson_id = l.id ";
	sqlCondition << "       AND ap.student_id = ? ";
	sqlCondition << "       AND ap.verify_state IN (1,2) ";
	sqlCondition << " ) ";
	sqlCondition << " ) ";

	// 绑定班级学员关系查询参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);
	// 绑定预约记录查询参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);

	return sqlCondition.str();
}

/**
 * 构建预约分组查询条件
 * 预约分组只包含还能预约的课
 */
std::string TimetableDAO::reserveSectionConditionBuilder(const std::string& studentId,
	const std::string& queryDate,
	SqlParams& params)
{
	std::stringstream sqlCondition;
	// 先拼接基础条件
	sqlCondition << lessonBaseConditionBuilder(studentId, queryDate, params);

	// 仅查询开放预约的课次
	sqlCondition << " AND IFNULL(l.bookable, 0) = 1 ";
	// 仅查询进行中的课次状态
	sqlCondition << " AND IFNULL(l.state, 1) = 1 ";
	// 已开始或正在上课的课次不可预约，只能预约后续课次
	sqlCondition << " AND CONCAT(l.date, ' ', l.start_time) > NOW() ";

	// 学员必须有该课程剩余课时
	sqlCondition << " AND EXISTS ( ";
	sqlCondition << "     SELECT 1 FROM student_course sc ";
	sqlCondition << "     WHERE sc.student_id = ? ";
	sqlCondition << "       AND sc.course_id = l.course_id ";
	sqlCondition << "       AND sc.deleted = 0 ";
	sqlCondition << "       AND (IFNULL(sc.count_lesson_total,0) - IFNULL(sc.count_lesson_complete,0) - IFNULL(sc.count_lesson_refund,0)) > 0 ";
	sqlCondition << " ) ";

	// 学员不能已经在该班级中
	sqlCondition << " AND NOT EXISTS ( ";
	sqlCondition << "     SELECT 1 FROM class_student cs ";
	sqlCondition << "     WHERE cs.class_id = l.class_id ";
	sqlCondition << "       AND cs.student_id = ? ";
	sqlCondition << "       AND cs.deleted = 0 ";
	sqlCondition << " ) ";

	// 学员不能已经对该课次提交过预约
	sqlCondition << " AND NOT EXISTS ( ";
	sqlCondition << "     SELECT 1 FROM appointment ap ";
	sqlCondition << "     WHERE ap.lesson_id = l.id ";
	sqlCondition << "       AND ap.student_id = ? ";
	sqlCondition << " ) ";

	// 绑定课时校验参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);
	// 绑定入班关系排除参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);
	// 绑定预约记录排除参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);

	return sqlCondition.str();
}

/**
 * 按天查询课表分组原始数据
 */
std::list<TimetableCourseViewDO> TimetableDAO::selectLessonSectionByDay(const std::string& studentId, const std::string& queryDate)
{
	SqlParams params;
	std::string sql =
		"SELECT "
		" l.id, l.title, IFNULL(l.sn,0), l.class_id, l.room_id, l.date, l.start_time, l.end_time, "
		" l.remark, IFNULL(l.state,1), l.teacher_id, IFNULL(l.bookable,0), l.course_id, "
		" IFNULL(st.name,''), IFNULL(cr.name,''), IFNULL(c.name,''), "
		" IFNULL(l.state,1), "
		" CASE IFNULL(l.state,1) WHEN 2 THEN '" + ZH_WORDS_GETTER("timetable.words.lesson-state-finished") + "' ELSE '" + ZH_WORDS_GETTER("timetable.words.lesson-state-running") + "' END, "
		" IFNULL(ls.sign_state,0), "
		" CASE IFNULL(ls.sign_state,0) "
		"   WHEN 1 THEN '" + ZH_WORDS_GETTER("timetable.words.sign-state-signed") + "' "
		"   WHEN 2 THEN '" + ZH_WORDS_GETTER("timetable.words.sign-state-repair") + "' "
		"   WHEN 3 THEN '" + ZH_WORDS_GETTER("timetable.words.sign-state-leave") + "' "
		"   WHEN 4 THEN '" + ZH_WORDS_GETTER("timetable.words.sign-state-absence") + "' "
		"   ELSE '" + ZH_WORDS_GETTER("timetable.words.sign-state-unsigned") + "' END, "
		" CASE WHEN IFNULL(l.state,1)=1 THEN 1 ELSE 0 END, "
		" CASE WHEN IFNULL(l.state,1)=1 THEN 1 ELSE 0 END, "
		" 0, "
		" 'lesson', "
		" CASE WHEN IFNULL(ls.sign_state,0)=0 THEN 'sign' ELSE 'none' END, "
		" CASE WHEN IFNULL(ls.sign_state,0)=0 THEN '" + ZH_WORDS_GETTER("timetable.words.action-sign") + "' ELSE '' END "
		"FROM lesson l "
		"LEFT JOIN class c ON c.id = l.class_id AND c.deleted = 0 "
		"LEFT JOIN classroom cr ON cr.id = l.room_id AND cr.deleted = 0 "
		"LEFT JOIN staff st ON st.id = l.teacher_id AND st.deleted = 0 "
		"LEFT JOIN lesson_student ls ON ls.lesson_id = l.id AND ls.student_id = ? ";

	// 绑定签到记录联表查询参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);
	// 拼接课表分组条件
	sql += lessonSectionConditionBuilder(studentId, queryDate, params);
	// 按开始时间升序、ID升序排序
	sql += " ORDER BY l.start_time ASC, l.id ASC ";

	// 执行查询并映射结果
	return sqlSession->executeQuery<TimetableCourseViewDO>(sql, TimetableCourseViewMapper(), params);
}

/**
 * 按天查询预约分组原始数据
 */
std::list<TimetableCourseViewDO> TimetableDAO::selectReserveSectionByDay(const std::string& studentId, const std::string& queryDate)
{
	SqlParams params;
	std::string sql =
		"SELECT "
		" l.id, l.title, IFNULL(l.sn,0), l.class_id, l.room_id, l.date, l.start_time, l.end_time, "
		" l.remark, IFNULL(l.state,1), l.teacher_id, IFNULL(l.bookable,0), l.course_id, "
		" IFNULL(st.name,''), IFNULL(cr.name,''), IFNULL(c.name,''), "
		" IFNULL(l.state,1), "
		" CASE IFNULL(l.state,1) WHEN 2 THEN '" + ZH_WORDS_GETTER("timetable.words.lesson-state-finished") + "' ELSE '" + ZH_WORDS_GETTER("timetable.words.lesson-state-running") + "' END, "
		" 0, '', "
		" 0, 0, 1, "
		" 'reservable', "
		" 'reserve', "
		" '" + ZH_WORDS_GETTER("timetable.words.action-reserve") + "' "
		"FROM lesson l "
		"LEFT JOIN class c ON c.id = l.class_id AND c.deleted = 0 "
		"LEFT JOIN classroom cr ON cr.id = l.room_id AND cr.deleted = 0 "
		"LEFT JOIN staff st ON st.id = l.teacher_id AND st.deleted = 0 ";

	// 拼接预约分组条件
	sql += reserveSectionConditionBuilder(studentId, queryDate, params);
	// 按开始时间升序、ID升序排序
	sql += " ORDER BY l.start_time ASC, l.id ASC ";

	// 执行查询并映射结果
	return sqlSession->executeQuery<TimetableCourseViewDO>(sql, TimetableCourseViewMapper(), params);
}

/**
 * 按月查询月历课表计数
 * 仅统计课表分组中会展示出来的数量
 */
std::list<TimetableCalendarCountDO> TimetableDAO::selectCalendarCountByMonth(const std::string& studentId, int year, int month)
{
	SqlParams params;
	std::string sql =
		"SELECT l.date, COUNT(1) "
		"FROM lesson l "
		"WHERE l.deleted = 0 "
		"  AND YEAR(l.date) = ? "
		"  AND MONTH(l.date) = ? "
		"  AND ( "
		"    EXISTS ( "
		"      SELECT 1 FROM class_student cs "
		"      WHERE cs.class_id = l.class_id "
		"        AND cs.student_id = ? "
		"        AND cs.deleted = 0 "
		"    ) "
		"    OR EXISTS ( "
		"      SELECT 1 FROM appointment ap "
		"      WHERE ap.lesson_id = l.id "
		"        AND ap.student_id = ? "
		"        AND ap.verify_state IN (1,2) "
		"    ) "
		"  ) "
		"GROUP BY l.date "
		"ORDER BY l.date ASC";

	// 绑定年份参数
	SQLPARAMS_PUSH(params, "i", int, year);
	// 绑定月份参数
	SQLPARAMS_PUSH(params, "i", int, month);
	// 绑定班级学员关系查询参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);
	// 绑定预约记录查询参数
	SQLPARAMS_PUSH(params, "s", std::string, studentId);

	// 执行查询并映射结果
	return sqlSession->executeQuery<TimetableCalendarCountDO>(sql, TimetableCalendarCountMapper(), params);
}

/**
 * 根据课次ID查询课次基础信息
 */
PtrLessonDO TimetableDAO::selectLessonById(const std::string& id)
{
	std::string sql =
		"SELECT id,title,IFNULL(sn,0),class_id,room_id,date,start_time,end_time,remark,IFNULL(state,1),teacher_id,IFNULL(bookable,0),course_id "
		"FROM lesson WHERE id=?";

	// 执行单条查询
	return sqlSession->executeQueryOne<PtrLessonDO>(sql, PtrLessonMapper(), "%s", id);
}

/**
 * 根据课次ID和学员ID查询签到记录
 */
PtrLessonStudentDO TimetableDAO::selectLessonStudentByLessonId(const std::string& lessonId, const std::string& studentId)
{
	std::string sql =
		"SELECT id,lesson_id,class_id,student_id,sign_time,sign_type,sign_state,teacher_id "
		"FROM lesson_student WHERE lesson_id=? AND student_id=?";

	// 执行单条查询
	return sqlSession->executeQueryOne<PtrLessonStudentDO>(sql, PtrLessonStudentMapper(), "%s%s", lessonId, studentId);
}

/**
 * 统计某学员某课次的预约记录数量
 */
uint64_t TimetableDAO::countAppointmentByLessonId(const std::string& lessonId, const std::string& studentId)
{
	std::string sql =
		"SELECT COUNT(*) FROM appointment WHERE lesson_id=? AND student_id=?";

	// 执行数量统计
	return sqlSession->executeQueryNumerical(sql, "%s%s", lessonId, studentId);
}

/**
 * 统计某学员某课次的驳回记录数量
 */
uint64_t TimetableDAO::countRejectedAppointmentByLessonId(const std::string& lessonId, const std::string& studentId)
{
	std::string sql =
		"SELECT COUNT(*) FROM appointment WHERE lesson_id=? AND student_id=? AND verify_state=-1";

	// 执行数量统计
	return sqlSession->executeQueryNumerical(sql, "%s%s", lessonId, studentId);
}

/**
 * 新增预约记录
 */
int TimetableDAO::insertAppointment(const BaseDO& bd)
{
	// 调用BaseDAO通用插入方法
	return insert(bd);
}

/**
 * 更新签到记录
 */
int TimetableDAO::updateLessonStudent(const BaseDO& bd)
{
	// 调用BaseDAO通用更新方法
	return update(bd);
}
