#pragma once
#ifndef COMMENTRECORDSERVICE_H
#define COMMENTRECORDSERVICE_H

#include "domain/vo/huitailang-vo/commentrecordvo.h"
#include "domain/query/huitailang-query/commentrecordquery.h"
#include "domain/dto/huitailang-dto/commentrecorddto.h"


class CommentrecordService
{
public:
	// 分页查询所有数据
	CommentrecordPageDTO::Wrapper listAll(const CommentrecordQuery::Wrapper& query);
	
};

#endif