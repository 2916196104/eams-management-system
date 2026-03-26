#ifndef __BOARDMANAGER_QUERY_H__
#define __BOARDMANAGER_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*��������ѯ��*/


/**
 * ����һ����ѯ��������ݴ���ģ��
 */
class BoardQuery : public PageQuery
{
	// �����ʼ��
	DTO_INIT(BoardQuery, PageQuery);
	// �������
	API_DTO_FIELD_DEFAULT(String, boardTitle, ZH_WORDS_GETTER("board.field.boardTitle"));
	// ���淢��������
	API_DTO_FIELD_DEFAULT(String, boardPublisherName, ZH_WORDS_GETTER("board.field.boardPublisherName"));
	// ���淢����id
	API_DTO_FIELD_DEFAULT(String, boardPublisherId, ZH_WORDS_GETTER("board.field.boardPublisherId"));
	// ��������
	API_DTO_FIELD_DEFAULT(Int8, boardType, ZH_WORDS_GETTER("board.field.boardType"));
};

#include OATPP_CODEGEN_END(DTO)

#endif