#include "stdafx.h"
#include "GradeManagerService.h"
#include "dao/Grade/GradeDao.h"

/**
 * 分页查询成绩列表
 * 流程：
 *   1. 构建分页返回对象
 *   2. 调 DAO 查询总数
 *   3. 调 DAO 分页查询 DO 列表
 *   4. DO -> DTO 转换
 */
GradeManagePageDTO::Wrapper GradeManagerService::listAll(const GradeManageQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = GradeManagePageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	GradeDao dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	std::list<GradeDO> result = dao.selectWithPage(query);

	// DO -> DTO 转换
	for (GradeDO& sub : result)
	{
		auto dto = GradeManageDTO::createShared();
		// 考核项（grade.title）
		dto->item = sub.getTitle();
		// 从联查字段取 grade_record.id 和 grade_record.score
		dto->id = sub.getRecordId();
		dto->score = (float)sub.getScore();
		
		// 从关联的 student 对象中取学生姓名
		if (sub.getStudent())
		{
			dto->name = sub.getStudent()->getName();
		}
		pages->addData(dto);
	}
	return pages;
}

/**
 * 保存成绩（新增一条 grade_record 记录）
 */
uint64_t GradeManagerService::saveScore(const GradeManageDTO::Wrapper& dto, const PayloadDTO& payload)
{
	GradeDao dao;

	// 根据考核项标题查找 grade.id
	int64_t gradeId = dao.selectGradeIdByTitle(dto->item.getValue(""));
	if (gradeId <= 0) return 0;

	// 根据学生姓名查找 student.id
	int64_t studentId = dao.selectStudentIdByName(dto->name.getValue(""));
	if (studentId <= 0) return 0;

	// 构建 grade_record DO
	GradeRecordDO record;
	record.setGradeId(gradeId);
	record.setStudentId(studentId);
	record.setScore(dto->score.getValue(0.0));
	record.setCreator(atoi(payload.getId().c_str()));

	return dao.insertRecord(record);
}

/**
 * 批量删除成绩记录
 */
bool GradeManagerService::removeScore(const oatpp::List<oatpp::String>& ids)
{
	// 将 oatpp::List<String> 转为 std::list<std::string>
	std::list<std::string> idList;
	for (const auto& id : *ids)
	{
		idList.push_back(id);
	}
	GradeDao dao;
	return dao.deleteRecordByIds(idList);
}
