#pragma once


#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/vo/BoardManager/BoardManagerVO.h"
#include "domain/dto/BoardManager/BoardManagerDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/PayloadDTO.h"
#include "domain/query/BoardManager/BoardManagerQuery.h"
#include "ApiHelper.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("board.tag")
//公告管理控制器



class BoardManager : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(BoardManager);
public:		//定义接口
	// 定义保存公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.save.summary"), SaveBoard, StringJsonVO::Wrapper, API_TAG);
	// 定义保存公告接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "c3-org/board/add-board", SaveBoard, BODY_DTO(BoardAddDTO::Wrapper, dto), executeAddBoard(dto, authObject->getPayload()));

	// 3.1 定义删除公告（支持批量删除）接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.delete.summary"), removeBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义删除公告（支持批量删除）接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "c3-org/board/remove-board", removeBoard, BODY_DTO(List<String>, ids), execRemoveBoard(ids));

	// 3.1 定义启用公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.start.summary"), startBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义启用公告接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "c3-org/board/start-board", startBoard, BODY_DTO(List<String>, ids), execStartBoard(ids, authObject->getPayload()));

	// 3.1 定义停用公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.end.summary"), endBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义停用公告接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "c3-org/board/end-board", endBoard, BODY_DTO(List<String>, ids), execEndBoard(ids, authObject->getPayload()));

	// ========== 新增：获取公告列表接口（和原有接口格式完全一致，一行写完） ==========
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("board.list.summary"), GetBoardList, BoardQuery, BoardPageJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "c3-org/board/get-board-list", GetBoardList, BoardQuery, execGetBoardList(query));

	// ========== 新增：获取公告详情接口（和原有接口格式完全一致，一行写完） ==========
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.detail.summary"), GetBoardDetail, GetBoardDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "boardId", ZH_WORDS_GETTER("board.field.boardId"), "boardId", true);
	API_DEF_ADD_QUERY_PARAMS(String, "boardTitle", ZH_WORDS_GETTER("board.field.boardTitle"), "boardTitle", false);
	API_DEF_ADD_QUERY_PARAMS(String, "boardType", ZH_WORDS_GETTER("board.field.boardType"), "boardType", false);
		);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "c3-org/board/get-board-detail", GetBoardDetail, QUERIES(QueryParams, queryParams),
		auto boardId = queryParams.get("boardId");
	auto boardTitle = queryParams.get("boardTitle");
	auto boardType = queryParams.get("boardType");
	API_HANDLER_RESP_VO(execGetBoardDetail(boardId, boardTitle, boardType));
		);

private:	//定义接口执行函数
	StringJsonVO::Wrapper executeAddBoard(const BoardAddDTO::Wrapper& dto, const PayloadDTO& payload);
	ListJsonVO<String>::Wrapper execRemoveBoard(const List<String>& ids);
	ListJsonVO<String>::Wrapper execStartBoard(const List<String>& ids, const PayloadDTO& payload);
	ListJsonVO<String>::Wrapper execEndBoard(const List<String>& ids, const PayloadDTO& payload);

	// 新增：函数声明（完全抄原有格式）
	BoardPageJsonVO::Wrapper execGetBoardList(const BoardQuery::Wrapper& query);
	GetBoardDetailJsonVO::Wrapper execGetBoardDetail(const oatpp::String& boardId, const oatpp::String& boardTitle, const oatpp::String& boardType);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif