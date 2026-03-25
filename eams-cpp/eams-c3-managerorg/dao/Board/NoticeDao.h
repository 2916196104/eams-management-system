#pragma once
#ifndef _NOTICE_DAO_
#define _NOTICE_DAO_

#include "BaseDAO.h"
#include "../../domain/do/Board/NoticeDO.h"
#include "../../domain/query/BoardManager/BoardManagerQuery.h"

/**
 * 通知设置数据访问对象
 */
class NoticeDAO : public BaseDAO
{
public:
    // 查询所有通知配置
    std::list<PtrNoticeSettingDO> selectAll();

    // 根据ID查询通知配置
    PtrNoticeSettingDO selectById(int id);

    // 根据通知编码（code）查询通知配置
    PtrNoticeSettingDO selectByCode(const std::string& code);
};

#endif // !_NOTICE_DAO_