#pragma once
#ifndef _BULLETIN_DAO_H_
#define _BULLETIN_DAO_H_

#include "domain/do/bulletin/bulletinDO.h"
#include "domain/query/PageQuery.h"
#include "BaseDAO.h"
#include <list>
#include <cstdint>

/**
 * 公告数据访问对象
 */
class bulletinDAO : public BaseDAO
{
public:
	// 查询最新一条公告
	ptrbulletinDO selectLatest();

	// 查询总记录数
	uint64_t count();

	// 分页查询公告
	std::list<bulletinDO> selectWithPage(const PageQuery::Wrapper& query);
};

/**
 * 未读数数据访问对象
 */
class redDAO : public BaseDAO
{
public:
	// 聚合查询所有未读数
	std::shared_ptr<redDO> getUnreadCounts(int64_t studentId);

	// 分拆的查询方法
	int32_t getHomeworkUnreadCount(int64_t studentId);
	int32_t getEvaluateUnreadCount(int64_t studentId);
	int32_t getGradeUnreadCount(int64_t studentId);
};

// 用于映射单个整数值的Mapper
class CountMapper : public Mapper<int32_t>
{
public:
	int32_t mapper(ResultSet* resultSet) const override
	{
		return resultSet->getInt(1);
	}
};
#endif // !_BULLETIN_DAO_H_