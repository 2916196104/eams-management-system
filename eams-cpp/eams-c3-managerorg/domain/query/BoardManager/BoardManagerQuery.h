#ifndef __BOARDMANAGER_QUERY_H__
#define __BOARDMANAGER_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)





class BoardQuery : public PageQuery
{
	// �����ʼ��
	DTO_INIT(BoardQuery, PageQuery);
	// �������
	API_DTO_FIELD_DEFAULT(String, boardTitle, ZH_WORDS_GETTER("board.field.boardTitle"));
	// 公告发布者名称
	//API_DTO_FIELD_DEFAULT(String, boardPublisherName, ZH_WORDS_GETTER("board.field.boardPublisherName"));
	// 公告发布者id
	API_DTO_FIELD_DEFAULT(Int64, boardPublisherId, ZH_WORDS_GETTER("board.field.boardPublisherId"));
};

#include OATPP_CODEGEN_END(DTO)

#endif