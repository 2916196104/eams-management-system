/*
 @Author: abinng
 @Date: 2026/03/23 16:16:17
 @File: ReviewService.cpp
*/
#include "ReviewService.h"

#include "dao/review-records/ReviewDAO.h"
#include "domain/do/review-records/ReviewDO.h"
#include "stdafx.h"
// 使用Redis需要的相关头文件
#include "Macros.h"
#include "NacosClient.h"
#include "RedisClient.h"
#include "ServerInfo.h"

ReviewRecordPageDTO::Wrapper ReviewService::listAll(const ReviewRecordQuery::Wrapper& query)
{
    // 1. 获取并构建参数
    uint64_t studentId = query->student_id.getValue(0);
    uint64_t pageIndex = query->pageIndex.getValue(1);
    uint64_t pageSize = query->pageSize.getValue(10);

    // 构建 Redis Cache Key: review:list:student:{id}:page:{pageIndex}:size:{pageSize}
    std::string cacheKey = "review:list:student:" + std::to_string(studentId) + ":page:" + std::to_string(pageIndex) +
                           ":size:" + std::to_string(pageSize);

    // ObjectMapper 用于序列化/反序列化 DTO
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    // 创建 RedisClient 对象
    RedisClient redisClient("127.0.0.1", 6379, "123456");
    // ZO_CREATE_REDIS_CLIENT(redisClient);

    // 2. 尝试从 Redis 缓存获取
    auto cachedData =
        redisClient.execute<std::optional<std::string>>([&](Redis* redis) { return redis->get(cacheKey).value(); });

    // 如果缓存存在且有值
    if (cachedData && cachedData) {
        try {
        
        }
    }

    // 构建返回分页DTO对象
    auto page = ReviewRecordPageDTO::createShared();
    // 1. 获取分页数据
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;

    // 2. 获取数据总数
    ReviewDAO dao;

    int64_t total = dao.count(query);
    page->total = total;
    page->calcPages();

    uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    page->rows = oatpp::List<ReviewRecordDTO::Wrapper>::createShared();
    if (total == 0 || offset > total) { // 没有记录或者当前页没有记录
        return page;                    // 设置记录为空，直接返回
    }
    auto result = dao.selectByQuery(query);
    // 返回的std::list类型的结果为空
    if (result.empty()) {
        return page; // 设置记录为空，直接返回
    }
    for (auto& one : result) {
        auto dto = ReviewRecordDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, one, id, Id, lesson_id, LessonId, lesson_title, LessonTitle, evaluate_teacher,
                                   EvaluateTeacher, evaluation, Evaluation, score, Score, evaluate_time, EvaluateTime);
        page->rows->emplace_back(std::move(dto));
    }
    return page;
}
