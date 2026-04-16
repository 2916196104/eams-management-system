#include "stdafx.h"
#include "RegistrationService.h"
#include "domain/do/registration-records/RegistrationDO.h"
#include "dao/registration-records/RegistrationDAO.h"
// 使用Redis需要的相关头文件
#include "Macros.h"
#include "NacosClient.h"
#include "RedisClient.h"
#include "ServerInfo.h"

RegistrationRecordPageDTO::Wrapper RegistrationService::listAll(const RegistrationRecordQuery::Wrapper& query)
{
    // 1. 获取并构建参数
    uint64_t studentId = query->student_id.getValue(0);
    uint64_t pageIndex = query->pageIndex.getValue(1);
    uint64_t pageSize = query->pageSize.getValue(10);
    bool exclude_expired = query->exclude_expired.getValue(false);

    // 构建 Redis Cache Key: registration:list:student:{id}:{exclude_expired}:page:{pageIndex}:size:{pageSize}
    std::string cacheKey = "registration:list:student:" + std::to_string(studentId) +
                           ":exclude_expired:" + std::to_string(exclude_expired) + ":page:" + std::to_string(pageIndex) +
                           ":size:" + std::to_string(pageSize);

    // ObjectMapper 用于序列化/反序列化 DTO
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    //创建 RedisClient 对象
    RedisClient redisClient("127.0.0.1", 6379, "123456");
    //ZO_CREATE_REDIS_CLIENT(redisClient);    // WIN:从配置文件获取, LINUX:从 Nacos 获取

    // 2. 尝试从 Redis 缓存获取
    auto cachedData =
        redisClient.execute<std::optional<std::string>>([&](Redis* redis) { return redis->get(cacheKey).value(); });

    // 如果缓存存在且有值
    if (cachedData && !cachedData.value().empty()) {
        try {
            // 命中缓存，直接反序列化为 DTO 返回
            return objectMapper->readFromString<RegistrationRecordPageDTO::Wrapper>(cachedData.value());
        } catch (const std::exception& e) {
            std::cerr << "[ReviewService] Redis 数据反序列化失败，去查 MySQL: " << e.what() << std::endl;
        }
    }

    // 3. 缓存未命中，执行 MySQL 查询
    auto page = RegistrationRecordPageDTO::createShared();
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;

    RegistrationDAO dao;
    int64_t total = dao.count(query);
    page->total = total;
    page->calcPages();
    uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    page->rows = oatpp::List<RegistrationRecordDTO::Wrapper>::createShared();
    if (total > 0 && offset < total) {
        auto result = dao.selectByQuery(query);
        for (auto& one : result) {
            auto dto = RegistrationRecordDTO::createShared();
            ZO_STAR_DOMAIN_DO_TO_DTO_1(
                dto, one, id, Id, student_id, StudentId, student_name, StudentName, course_id, CourseId, course_name,
                CourseName, subject_id, SubjectId, subject_name, SubjectName, add_time, AddTime, expire_date,
                ExpireDate, amount, Amount, paid_amount, PaidAmount, count_lesson_total, CountLessonTotal,
                count_lesson_complete, CountLessonComplete, lesson_type, LessonType, verify_state, VerifyState);

            string expire_date_str = dto->expire_date.getValue("");
            if (!expire_date_str.empty()) {
                expire_date_str += " 23:59:59";

                // 填充tm结构体
                std::tm tm = {};
                std::istringstream ss(expire_date_str);
                ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

                // 转换为时间戳
                std::time_t expire_time = std::mktime(&tm);

                // 获取当前时间戳
                std::time_t current_time = std::time(nullptr);

                // 判断是否已过期
                dto->expired = (expire_time < current_time);
            } else {
                dto->expired = false;
            }
            bool ex_expired = query->exclude_expired.getValue(false);
            if (ex_expired) { // 要排除已过期的课程, 跳过已过期的课程
                if (dto->expired) {
                    continue;
                }
            }
            page->rows->emplace_back(std::move(dto));
        }
    }
    page->total = page->rows->size();
    page->calcPages();
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
