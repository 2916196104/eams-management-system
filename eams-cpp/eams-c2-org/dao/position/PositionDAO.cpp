#include "PositionDAO.h"
#include "dao/position/PositionMapper.h"

std::vector<PositionItemDO> PositionDAO::fetchAll() {

  PositionItemMapper mapper;
  auto list = sqlSession->executeQuery<PositionItemDO>(
      "SELECT id, name FROM position WHERE deleted = 0", mapper);
  std::vector<PositionItemDO> vec;
  vec.reserve(list.size()); // 预分配空间，提升性能
  for (auto& item : list) {
      vec.push_back(std::move(item)); // 移动而非拷贝
  }
  return vec;
}

uint64_t PositionDAO::countByNameLike(const std::string &keyWord) {

  SqlParams params;

  std::string sql = "SELECT COUNT(1) FROM position WHERE deleted = 0";
  if (!keyWord.empty()) {
    sql += " AND name LIKE ?";
    SQLPARAMS_PUSH(params, "s", std::string, ("%" + keyWord + "%"));
  }

  return sqlSession->executeQueryNumerical(sql, params);
}

std::vector<PositionItemDO>
PositionDAO::selectPageByNameLike(int pageNum, int pageSize,
                                  const std::string &keyWord) {

  SqlParams params;

  std::string sql = "SELECT id, name FROM position WHERE deleted = 0";
  if (!keyWord.empty()) {
    sql += " AND name LIKE ?";
    SQLPARAMS_PUSH(params, "s", std::string, ("%" + keyWord + "%"));
  }

  sql += " ORDER BY id DESC LIMIT ?, ?";
  const int32_t offset = (pageNum - 1) * pageSize;
  SQLPARAMS_PUSH(params, "i", int32_t, offset);
  SQLPARAMS_PUSH(params, "i", int32_t, pageSize);

  PositionItemMapper mapper;
  auto list = sqlSession->executeQuery<PositionItemDO>(sql, mapper, params);
  std::vector<PositionItemDO> vec;
  vec.reserve(list.size()); // 预分配空间，提升性能
  for (auto& item : list) {
      vec.push_back(std::move(item)); // 移动而非拷贝
  }
  return vec;
}

uint64_t PositionDAO::insertPosition(const std::string &name) {

  PositionItemDO item;
  item.setname(name);
  return insertAutoPk(item);
}

int PositionDAO::updatePositionNameById(int64_t id, const std::string &name) {

  PositionItemDO item;
  item.setId(static_cast<int>(id));
  item.setname(name);
  return update(item);
}
