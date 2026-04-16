#pragma once
#ifndef _NOTICE_DAO_H_
#define _NOTICE_DAO_H_

#include "BaseDAO.h"
#include "domain/do/Board/NoticeDO.h"
#include "domain/query/BoardManager/BoardManagerQuery.h"

class NoticeDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const BoardQuery::Wrapper& query, SqlParams& params);
public:
    std::list<PtrNoticeDO> selectAll(const BoardQuery::Wrapper& query);
    PtrNoticeDO selectById(oatpp::UInt64 id);
    std::list<PtrNoticeDO> selectByTitle(const std::string& title);
    int insert(const NoticeDO& notice);
    bool update(const NoticeDO& notice);
    uint64_t count(const BoardQuery::Wrapper& query);
    bool update1(const NoticeDO& notice);
    bool update2(const NoticeDO& notice);
};

#endif // _NOTICE_DAO_H_