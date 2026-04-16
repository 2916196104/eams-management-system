#pragma once
#ifndef _BOARDSERVICE_H_
#define _BOARDSERVICE_H_
#include "domain/query/BoardManager/BoardManagerQuery.h"
#include "domain/dto/BoardManager/BoardManagerDTO.h"
#include "domain/vo/BoardManager/BoardManagerVO.h"

/**
 * 公告业务逻辑类
 */
class BoardService
{
public:
	// 查询所有公告
	BoardPageDTO::Wrapper listAll(const BoardQuery::Wrapper& query);
	// 添加用户
	oatpp::UInt64 saveBoard(const BoardAddDTO::Wrapper& dto);
	// 修改数据
	bool updateData1(const oatpp::List<oatpp::String>& ids,const BoardUpdateDTO::Wrapper& dto);
	bool updateData2(const oatpp::List<oatpp::String>& ids,const BoardUpdateDTO::Wrapper& dto);
	// 通过ID删除数据
	bool removeData(const oatpp::List<oatpp::String>& ids);
	// 获取公告详情
	GetBoardDetailJsonVO::Wrapper getBoardDetail(const oatpp::String& boardId, const oatpp::String& boardTitle, const oatpp::String& boardType);
};

#endif // !_BOARDSERVICE_H_