#pragma once

#ifndef _SCORE_DAO_
#define _SCORE_DAO_
#include "BaseDAO.h"
#include "domain/do/score/ScoreDO.h"
#include "domain/query/score/scorequery.h"

/**
 * 角色表数据库操作实现
 */
class ScoreDAO : public BaseDAO {
public:
    // 统计记录总数
    uint64_t count(const ScoreQuery::Wrapper& query);
    // 通过查询条件查询数据
    std::list<PtrScoreViewDO> selectByQuery(const ScoreQuery::Wrapper& query);
};
#endif // !_SCORE_DAO_
