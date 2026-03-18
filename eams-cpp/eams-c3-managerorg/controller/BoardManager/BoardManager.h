#pragma once


#ifndef __BOARDMANAGER_H__
#define __BOARDMANAGER_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "domain/vo/BoardManager/BoardManagerVO.h"
#include "domain/dto/BoardManager/BoardManagerDTO.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/PayloadDTO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("board.tag")
//公告管理控制器



class BoardManager: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(BoardManager);
public:		//定义接口
	// 定义保存公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.save.summary"), SaveBoard, StringJsonVO::Wrapper, API_TAG);
	// 定义保存公告接口端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/board/add-board", SaveBoard, BODY_DTO(BoardAddDTO::Wrapper, dto), executeAddBoard(dto, authObject->getPayload()));
	
	// 3.1 定义删除公告（支持批量删除）接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.delete.summary"), removeBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义删除公告（支持批量删除）接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/board/remove-board", removeBoard, BODY_DTO(List<String>, ids), execRemoveBoard(ids));
	
	// 3.1 定义启用公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.start.summary"), startBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义启用公告接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/board/start-board", startBoard, BODY_DTO(List<String>, ids), execStartBoard(ids));

	// 3.1 定义停用公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("board.end.summary"), endBoard, ListJsonVO<String>::Wrapper, API_TAG);
	// 3.2 定义停用公告接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/board/end-board", endBoard, BODY_DTO(List<String>, ids), execEndBoard(ids));

private:	//定义接口执行函数
	StringJsonVO::Wrapper executeAddBoard(const BoardAddDTO::Wrapper& dto,const PayloadDTO& payload);
	ListJsonVO<String>::Wrapper execRemoveBoard(const List<String>& ids);
	ListJsonVO<String>::Wrapper execStartBoard(const List<String>& ids);
	ListJsonVO<String>::Wrapper execEndBoard(const List<String>& ids);



};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif