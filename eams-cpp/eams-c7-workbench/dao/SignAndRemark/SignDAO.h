#pragma once
#ifndef _SIGNDAO_H_
#define _SIGNDAO_H_

#include "BaseDAO.h"
#include "domain/do/SignAndRemark/SignDO.h"
#include "domain/dto/SignAndRemark/SignDTO.h"
#include "domain/query/SignAndRemark/SignQuery.h"

class SignDAO : public BaseDAO
{
public:
    // 获取数据条数
    uint64_t count(const SignQuery::Wrapper& query);
    // 获取点名记录列表
    std::list<PtrSignViewDO> selectAll(const SignQuery::Wrapper& query);
};

#endif // !_SIGNDAO_H_
