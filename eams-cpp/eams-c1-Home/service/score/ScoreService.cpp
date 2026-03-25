#include "stdafx.h"
#include "ScoreService.h"
#include "dao/score/ScoreDAO.h"
#include "domain/do/score/ScoreDO.h"
// 使用Redis需要的相关头文件
#include "Macros.h"
#include "NacosClient.h"
#include "RedisClient.h"
#include "ServerInfo.h"

ScorePageDTO::Wrapper ScoreService::listAll(const ScoreQuery::Wrapper& query)
{
    // 1. 获取并构建参数
    uint64_t studentId = query->student_id.getValue(0);
    uint64_t pageIndex = query->pageIndex.getValue(1);
    uint64_t pageSize = query->pageSize.getValue(10);

    // 构建 Redis Cache Key: score:list:student:{id}:page:{pageIndex}:size:{pageSize}
    std::string cacheKey = "score:list:student:" + std::to_string(studentId) + ":page:" + std::to_string(pageIndex) +
                           ":size:" + std::to_string(pageSize);

    // ObjectMapper 用于序列化/反序列化 DTO
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    // 创建 RedisClient 对象
    //RedisClient redisClient("127.0.0.1", 6379, "123456");
    ZO_CREATE_REDIS_CLIENT(redisClient);    // WIN:使用配置文件，LINUX:从 Nacos 配置文件获取

    // 2. 尝试从 Redis 缓存获取
    auto cachedData =
        redisClient.execute<std::optional<std::string>>([&](Redis* redis) { return redis->get(cacheKey).value(); });

    // 如果缓存存在且有值
    if (cachedData && !cachedData.value().empty()) {
        try {
            // 命中缓存，直接反序列化为 DTO 返回
            return objectMapper->readFromString<ScorePageDTO::Wrapper>(cachedData.value());
        } catch (const std::exception& e) {
            std::cerr << "[ScoreService] Redis 数据反序列化失败，去查 MySQL: " << e.what() << std::endl;
        }
    }

    // 3. 缓存未命中，执行 MySQL 查询
    auto page = ScorePageDTO::createShared();
    page->pageIndex = pageIndex;
    page->pageSize = pageSize;

    ScoreDAO dao;
    int64_t total = dao.count(query);
    page->total = total;
    page->calcPages();

    uint64_t offset = (pageIndex - 1) * pageSize;
    page->rows = oatpp::List<ScoreDTO::Wrapper>::createShared();

    // 只有在有数据的情况下才执行查表
    if (total > 0 && offset < total) {
        auto result = dao.selectByQuery(query);
        for (auto& one : result) {
            auto scoreDTO = ScoreDTO::createShared();
            ZO_STAR_DOMAIN_DO_TO_DTO_1(scoreDTO, one, id, Id, grade_id, GradeId, grade_title, GradeTitle, student_id,
                                       StudentId, student_name, StudentName, score, Score, add_time, AddTime);
            page->rows->push_back(scoreDTO);
        }
    }

    // 4. 将查询结果写入 Redis 缓存
    if (page->rows->size() > 0) {
        // 序列化为 JSON 字符串
        oatpp::String jsonStr = objectMapper->writeToString(page);

        // 使用 execute 写入 Redis 并设置过期时间
        redisClient.execute<bool>([&](Redis* redis) {
            // 写入 Redis 并设置 1 小时 (3600秒) 过期
            redis->set(cacheKey, jsonStr->c_str(), std::chrono::seconds(3600));
            return true;
        });
    }
    return page;
}
