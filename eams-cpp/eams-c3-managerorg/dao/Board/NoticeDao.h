#pragma once
#ifndef _NOTICE_DAO_
#define _NOTICE_DAO_

#include "BaseDAO.h"
#include "../../domain/do/Board/NoticeDO.h"
#include "../../domain/query/BoardManager/BoardManagerQuery.h"

/**
 * ֪ͨ�������ݷ��ʶ���
 */
class NoticeDAO : public BaseDAO
{
public:
    // ��ѯ����֪ͨ����
    std::list<PtrNoticeSettingDO> selectAll();

    // ����ID��ѯ֪ͨ����
    PtrNoticeSettingDO selectById(int id);

    // ����֪ͨ���루code����ѯ֪ͨ����
    PtrNoticeSettingDO selectByCode(const std::string& code);
};

#endif // !_NOTICE_DAO_