#include "PositionService.h"
#include "dao/position/PositionDAO.h"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "sw/redis++/redis.h"
#include "Macros.h"
#include "NacosClient.h"
#include "RedisClient.h"

#include <cstdint>
#include <string>

oatpp::Vector<PositionItemDTO::Wrapper> PositionService::fetchAllPosition() {

  static const std::string kCacheKey = "eams:org:position:all";
  static const long long kCacheTtlSeconds = 300;
  static const long long kEmptyCacheTtlSeconds = 60;

  auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

  ZO_CREATE_REDIS_CLIENT(redis);
  // RedisClient redisClient("192.168.1.100", 6379, "redis123");

  auto cached = redis.execute<sw::redis::OptionalString>(
	  [&](sw::redis::Redis *r) { return r->get(kCacheKey); });

  if (cached) {
	try {
	  return mapper->readFromString<oatpp::Vector<PositionItemDTO::Wrapper>>(
		  oatpp::String(cached.value().c_str()));
	} catch (...) {
	  redis.execute<long long>(
		  [&](sw::redis::Redis *r) { return r->del(kCacheKey); }); // 删除坏key
	}
  }

  PositionDAO dao;
  auto rDTO = oatpp::Vector<PositionItemDTO::Wrapper>::createShared();
  auto doList = dao.fetchAll();

  for (const auto &item : doList) {
	auto dto = PositionItemDTO::createShared();
	dto->id = item.getId();
	dto->name = item.getname().c_str();
	rDTO->push_back(dto);
  }

  const long long ttlSeconds =
	  (rDTO->empty() ? kEmptyCacheTtlSeconds : kCacheTtlSeconds);

  auto json = mapper->writeToString(rDTO);
  if (json) {
	redis.execute<int>([&](sw::redis::Redis *r) {
	  r->setex(kCacheKey, ttlSeconds, json.getValue(""));
	  return 1;
	});
  }

  return rDTO;
}

PositionService::PageQueryResult
PositionService::pageQueryPosition(const oatpp::Int32 &pageNum,
								   const oatpp::Int32 &pageSize,
								   const oatpp::String &keyWord) {

  PageQueryResult result;
  result.data = oatpp::Vector<PositionItemDTO::Wrapper>::createShared();
  result.total = 0;
  result.totalPages = 0;

  auto page = pageNum.getValue(1);
  auto limit = pageSize.getValue(10);

  auto keyword = keyWord.getValue("");

  PositionDAO dao;
  const uint64_t total = dao.countByNameLike(keyword);
  // TODO: total也许可以用redis缓存
  result.total = static_cast<int32_t>(total);
  result.totalPages =
	  static_cast<int32_t>((total + limit - 1) / static_cast<uint64_t>(limit));
  if (total == 0) {
	// 数据库返回错误或者无数据无需查询
	return result;
  }
  auto doList = dao.selectPageByNameLike(page, limit, keyword);
  for (const auto &item : doList) {
	auto dto = PositionItemDTO::createShared();
	dto->id = item.getId();
	dto->name = item.getname().c_str();
	result.data->push_back(dto);
  }

  return result;
}

int64_t
PositionService::savePosition(const PositionSaveRequestDTO::Wrapper &dto) {

  PositionDAO dao;
  auto name = dto->name;

  if (!dto->id) {
	const uint64_t id = dao.insertPosition(name);
	return id > 0 ? static_cast<int64_t>(id) : -1;
  }

  const int rows = dao.updatePositionNameById(dto->id, name);
  return rows > 0 ? 0 : -1;
}

bool PositionService::deletePositions(const std::vector<int64_t>& ids) {
	if (ids.empty()) return false;
	PositionDAO dao;
	return dao.deleteByIds(ids);
}