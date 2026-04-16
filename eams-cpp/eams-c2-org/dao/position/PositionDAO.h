#pragma once
#ifndef _POSITIONDAO_H_
#define _POSITIONDAO_H_

#include "BaseDAO.h"
#include "domain/do/position/PositionDO.h"

#include <cstdint>
#include <string>
#include <vector>

class PositionDAO : public BaseDAO {

public:
    std::vector<PositionItemDO> fetchAll();
    uint64_t countByNameLike(const std::string& keyWord);
    std::vector<PositionItemDO> selectPageByNameLike(int pageNum, int pageSize,
        const std::string& keyWord);

    uint64_t insertPosition(const std::string& name);
    int updatePositionNameById(int64_t id, const std::string& name);

    // 新增：批量删除职位（同时删除 data_permission 中关联的记录）
    bool deleteByIds(const std::vector<int64_t>& ids);
};

#endif