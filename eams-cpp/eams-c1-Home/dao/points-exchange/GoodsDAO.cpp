/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/24
*/
#include "stdafx.h"
#include "GoodsDAO.h"
#include "GoodsMapper.h"

GoodsDAO::GoodsDAO() : BaseDAO() {

}

PtrGoodsDetailDO GoodsDAO::selectById(const int64_t& id)
{
    SqlParams params;
    string sql = "SELECT id, deleted, school_id, add_time, edit_time, "
      "creator, editor, material_id, category_id, category_name, "
       "name, credit, sale_num, view_num, cover, content, "
        "state, org_id "
        "FROM credit_mall WHERE id = ? AND deleted = 0";
    
    
    SQLPARAMS_PUSH(params, "ull", uint64_t, id);

    auto resultList = sqlSession->executeQuery<PtrGoodsDetailDO>(sql, GoodsMapper(), params);

    if (resultList.empty()) {
       throw invalid_argument("Goods not found with id: " + std::to_string(id));
    }

    return resultList.front();
     
    
}

int GoodsDAO::incrementViewNum(const int64_t& id)
{
    SqlParams params;
    string sql = "UPDATE credit_mall SET view_num = view_num + 1 "
        "WHERE id = ? AND deleted = 0";
    
    SQLPARAMS_PUSH(params, "ull", int64_t, id);

    auto result = sqlSession->executeUpdate(sql, params);
    if (result <= 0)
        throw invalid_argument("Failed to increment view count");

    return result;
}

int GoodsDAO::updateStorage(const int64_t& id, const int64_t& num)
{
    SqlParams params;
    string sql = "UPDATE credit_mall SET storage = storage - ? "
        "WHERE id = ? AND storage >= ? AND deleted = 0";
    
    SQLPARAMS_PUSH(params, "ull", int64_t, num);
    SQLPARAMS_PUSH(params, "ull", int64_t, id);
    SQLPARAMS_PUSH(params, "ull", int64_t, num);

    auto result = sqlSession->executeUpdate(sql, params);
    if (result <= 0)
        throw invalid_argument("Failed to deduct inventory (stock may be insufficient)");

    return result;
}

int GoodsDAO::updateSaleNum(const int64_t& id, const int64_t& num)
{
    SqlParams params;
    string sql = "UPDATE credit_mall SET sale_num = sale_num + ? "
        "WHERE id = ? AND deleted = 0";
    
    SQLPARAMS_PUSH(params, "ull", int64_t, num);
    SQLPARAMS_PUSH(params, "ull", int64_t, id);

    auto result = sqlSession->executeUpdate(sql, params);

    if (result <= 0)
    {
        throw invalid_argument("Failed to increment sales count");
    }

    return result;
}