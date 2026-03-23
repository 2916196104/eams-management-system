#pragma once

#ifndef _SCORE_DAO_
#define _SCORE_DAO_
#include "BaseDAO.h"
#include "domain/do/score/ScoreDO.h"
#include "domain/query/score/ScoreQuery.h"

/**
 * 角色表数据库操作实现
 */
class ScoreDAO : public BaseDAO {
public:
    // 统计记录总数
    uint64_t count(const ScoreQuery::Wrapper& query);
    // 通过查询条件查询数据
    std::list<PtrScoreViewDO> selectByQuery(const ScoreQuery::Wrapper& query);
    // 分页查询数据
    std::list<ScoreViewDO> selectWithPage(const ScoreQuery::Wrapper& query);
    // 通过名称查询数据
    std::list<ScoreViewDO> selectByName(const string& name);
    // 通过 ID 查询数据
    PtrScoreViewDO selectById(std::string id);
    // 分页查询角色列表，支持名称和描述查询
    std::list<ScoreViewDO> selectRole(const ScoreQuery::Wrapper& query);
    // 根据 ID 查询角色详情
    PtrScoreViewDO selectByIdtwo(std::string id);
    // 统计角色关联的用户数量
    uint64_t countUsersByRoleId(const std::string& roleId);
};
#endif // !_SCORE_DAO_
