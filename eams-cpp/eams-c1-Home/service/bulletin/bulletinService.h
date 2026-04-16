#pragma once
#ifndef _BULLETIN_SERVICE_H_
#define _BULLETIN_SERVICE_H_

#include "domain/vo/bulletin/bulletinVO.h"
#include "domain/query/bulletin/bulletinQuery.h"
#include "domain/dto/bulletin/bulletinDTO.h"

/**
 * 公告服务实现类
 */
class bulletinService
{
public:
	// 接口1: 查询最新一条公告数据
	titleDTO::Wrapper getLatest();

	// 接口2: 分页查询所有公告数据
	listPageDTO::Wrapper listAll(const PageQuery::Wrapper& query);
};

/**
 * 未读数服务实现类
 */
class redService
{
public:
	// 获取未读提醒
	redDTO::Wrapper getRed(int64_t studentId);
};

#endif // !_BULLETIN_SERVICE_H_