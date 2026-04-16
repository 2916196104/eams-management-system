#pragma once
#ifndef _GRADE_DAO_H_
#define _GRADE_DAO_H_

#include "BaseDAO.h"
#include "domain/do/Grade/GradeDO.h"
#include "domain/do/Grade/GradeRecordDO.h"
#include "domain/query/GradeTable/GradeManageQuery.h"

/**
 * 成绩管理数据库操作实现
 * 联查 grade + grade_record + student 三张表
 */
class GradeDao : public BaseDAO
{
private:
	/**
	 * 查询条件构建器
	 * 根据 GradeManageQuery 对象动态构建 WHERE 条件
	 * @param query  查询数据对象
	 * @param params 存放查询数据的参数对象
	 * @return 条件SQL语句（WHERE部分）
	 */
	inline std::string queryConditionBuilder(const GradeManageQuery::Wrapper& query, SqlParams& params);

public:
	// 统计数据条数（联查）
	uint64_t count(const GradeManageQuery::Wrapper& query);
	// 分页查询数据（联查 grade + grade_record + student）
	std::list<GradeDO> selectWithPage(const GradeManageQuery::Wrapper& query);
	// 根据考核项标题查询 grade.id
	int64_t selectGradeIdByTitle(const std::string& title);
	// 根据学生姓名查询 student.id
	int64_t selectStudentIdByName(const std::string& name);
	// 新增成绩记录（插入 grade_record 表）
	uint64_t insertRecord(const GradeRecordDO& record);
	// 批量删除成绩记录（删除 grade_record 表记录）
	bool deleteRecordByIds(const std::list<std::string>& ids);
};

#endif // !_GRADE_DAO_H_
