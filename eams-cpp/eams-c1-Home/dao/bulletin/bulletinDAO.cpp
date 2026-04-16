#include "stdafx.h"
#include"bulletinMapper.h"
#include "bulletinDAO.h"
#include "domain/dto/bulletin/bulletinDTO.h"
#include<iostream>

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
	return static_cast<uint64_t>(sqlSession->executeQueryNumerical(sql));
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
	int offset =(int)((query->pageIndex - 1) * query->pageSize);

	// 添加分页限制
	sql += "LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);

	// 使用BulletinMapper来映射结果到bulletinDO
	return sqlSession->executeQuery<bulletinDO>(sql, BulletinMapper(), params);
}

/**
*  未读数查询
 * 分别查询作业，成绩，点评未读数
 */
// 作业未读数查询
int32_t redDAO::getHomeworkUnreadCount(int64_t studentId)
{
	//std::cout << "执行作业未读数查询，studentId=" << studentId << std::endl;

	// 与数据库验证完全一致的SQL
	std::ostringstream sql;
	sql << "SELECT COUNT(*) as cnt FROM homework "
		<< "WHERE class_id IN ("
		<< "  SELECT class_id FROM class_student "
		<< "  WHERE student_id = " << studentId << " AND deleted = 0"
		<< ") "
		<< "AND id NOT IN ("
		<< "  SELECT homework_id FROM homework_record "
		<< "  WHERE student_id = " << studentId
		<< ") "
		<< "AND deleted = 0";

	//std::cout << "作业查询SQL: " << sql.str() << std::endl;

	try {
		CountMapper mapper;
		SqlParams emptyParams;
		auto result = sqlSession->executeQuery<int32_t>(sql.str(), mapper, emptyParams);
		if (!result.empty()) {
			int32_t count = result.front();
			//std::cout << "作业未读数查询结果: " << count << std::endl;
			return count;
		}
	}
	catch (const std::exception& e) {
		std::cout << "作业未读数查询异常: " << e.what() << std::endl;
	}

	return 0;
}

// 点评记录未读数查询
int32_t redDAO::getEvaluateUnreadCount(int64_t studentId)
{
	//std::cout << "执行点评未读数查询，studentId=" << studentId << std::endl;

	// 先获取学生的redpoint_evaluate
	std::string redpointEvaluate = "1970-01-01 00:00:00";
	{
		std::ostringstream sql;
		sql << "SELECT COALESCE(redpoint_evaluate, '1970-01-01 00:00:00') as eval_time "
			<< "FROM student WHERE id = " << studentId;

		try {
			class StringMapper : public Mapper<std::string> {
			public:
				std::string mapper(ResultSet* resultSet) const override {
					return resultSet->getString("eval_time");
				}
			};

			StringMapper mapper;
			SqlParams emptyParams;
			auto result = sqlSession->executeQuery<std::string>(sql.str(), mapper, emptyParams);
			if (!result.empty()) {
				redpointEvaluate = result.front();
			}
		}
		catch (const std::exception& e) {
			std::cout << "获取redpoint_evaluate异常: " << e.what() << std::endl;
		}
	}

	//std::cout << "redpoint_evaluate: " << redpointEvaluate << std::endl;

	// 使用学生的redpoint_evaluate进行查询
	std::ostringstream sql;
	sql << "SELECT COUNT(*) as cnt FROM lesson_student "
		<< "WHERE student_id = " << studentId
		<< " AND evaluate_time IS NOT NULL "
		<< "AND evaluate_time > '" << redpointEvaluate << "'";

	//std::cout << "点评查询SQL: " << sql.str() << std::endl;

	try {
		CountMapper mapper;
		SqlParams emptyParams;
		auto result = sqlSession->executeQuery<int32_t>(sql.str(), mapper, emptyParams);
		if (!result.empty()) {
			int32_t count = result.front();
			//std::cout << "点评未读数查询结果: " << count << std::endl;
			return count;
		}
	}
	catch (const std::exception& e) {
		std::cout << "点评未读数查询异常: " << e.what() << std::endl;
	}

	return 0;
}

// 成绩未读数查询
int32_t redDAO::getGradeUnreadCount(int64_t studentId)
{
	//std::cout << "执行成绩未读数查询，studentId=" << studentId << std::endl;

	// 先获取学生的redpoint_grade
	std::string redpointGrade = "1970-01-01 00:00:00";
	{
		std::ostringstream sql;
		sql << "SELECT COALESCE(redpoint_grade, '1970-01-01 00:00:00') as grade_time "
			<< "FROM student WHERE id = " << studentId;

		try {
			class StringMapper : public Mapper<std::string> {
			public:
				std::string mapper(ResultSet* resultSet) const override {
					return resultSet->getString("grade_time");
				}
			};

			StringMapper mapper;
			SqlParams emptyParams;
			auto result = sqlSession->executeQuery<std::string>(sql.str(), mapper, emptyParams);
			if (!result.empty()) {
				redpointGrade = result.front();
			}
		}
		catch (const std::exception& e) {
			std::cout << "获取redpoint_grade异常: " << e.what() << std::endl;
		}
	}

	//std::cout << "redpoint_grade: " << redpointGrade << std::endl;

	// 使用学生的redpoint_grade进行查询
	std::ostringstream sql;
	sql << "SELECT COUNT(*) as cnt FROM grade_record "
		<< "WHERE student_id = " << studentId
		<< " AND add_time > '" << redpointGrade << "'";

	//std::cout << "成绩查询SQL: " << sql.str() << std::endl;

	try {
		CountMapper mapper;
		SqlParams emptyParams;
		auto result = sqlSession->executeQuery<int32_t>(sql.str(), mapper, emptyParams);
		if (!result.empty()) {
			int32_t count = result.front();
			//std::cout << "成绩未读数查询结果: " << count << std::endl;
			return count;
		}
	}
	catch (const std::exception& e) {
		std::cout << "成绩未读数查询异常: " << e.what() << std::endl;
	}

	return 0;
}

// 聚合查询所有未读数
std::shared_ptr<redDO> redDAO::getUnreadCounts(int64_t studentId)
{
	/*std::cout << "=== 开始执行分步查询 ===" << std::endl;
	std::cout << "studentId: " << studentId << std::endl;*/

	auto result = std::make_shared<redDO>();

	// 先测试一个简单查询，确保数据库连接正常
	//{
	//	std::ostringstream testSql;
	//	testSql << "SELECT COUNT(*) as cnt FROM student WHERE id = " << studentId;

	//	//std::cout << "测试SQL: " << testSql.str() << std::endl;

	//	try {
	//		CountMapper mapper;
	//		SqlParams emptyParams;
	//		auto testResult = sqlSession->executeQuery<int32_t>(testSql.str(), mapper, emptyParams);
	//		if (!testResult.empty()) {
	//			std::cout << "数据库连接测试成功，学生存在: " << testResult.front() << std::endl;
	//		}
	//		else {
	//			std::cout << "警告: 未找到学生ID=" << studentId << std::endl;
	//			return result;
	//		}
	//	}
	//	catch (const std::exception& e) {
	//		std::cout << "数据库连接测试异常: " << e.what() << std::endl;
	//		return result;
	//	}
	//}

	// 执行三个查询
	try {
		int32_t homeworkCount = getHomeworkUnreadCount(studentId);
		int32_t evaluateCount = getEvaluateUnreadCount(studentId);
		int32_t gradeCount = getGradeUnreadCount(studentId);

		result->setHomeworkCount(homeworkCount);
		result->setEvaluateCount(evaluateCount);
		result->setGradeCount(gradeCount);

	/*	std::cout << "=== 最终结果 ===" << std::endl;
		std::cout << "作业未读数: " << homeworkCount << std::endl;
		std::cout << "点评未读数: " << evaluateCount << std::endl;
		std::cout << "成绩未读数: " << gradeCount << std::endl;
		std::cout << "=== 查询结束 ===" << std::endl;*/
	}
	catch (const std::exception& e) {
		std::cout << "查询过程中发生异常: " << e.what() << std::endl;
	}

	return result;
}