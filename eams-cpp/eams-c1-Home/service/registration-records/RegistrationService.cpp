#include "RegistrationService.h"
#include "dao/registration-records/RegistrationDAO.h"
#include "domain/do/registration-records/RegistrationDO.h"

RegistrationRecordPageDTO::Wrapper RegistrationService::listAll(const RegistrationRecordQuery::Wrapper& query) 
{
    // 构建返回分页DTO对象
    auto page = RegistrationRecordPageDTO::createShared();
    // 1. 获取分页数据
    page->pageIndex = query->pageIndex;
    page->pageSize = query->pageSize;
    // 2. 获取数据总数
    RegistrationDAO dao;
    int64_t total = dao.count(query);
    page->calcPages();
    uint64_t offset = (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10);
    page->rows = oatpp::List<RegistrationRecordDTO::Wrapper>::createShared();
    if (total == 0 || offset > total) { // 没有记录或者当前页没有记录
        return page;                    // 设置记录为空，直接返回
    }
    auto result = dao.selectByQuery(query);
    // 返回的std::list类型的结果为空
    if (result.empty()) {
        return page; // 设置记录为空，直接返回
    }
    for (auto& one : result) {
        auto dto = RegistrationRecordDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, one, 
            id, Id, 
            student_id, StudentId, 
            student_name, StudentName, 
            course_id, CourseId, 
            course_name, CourseName,
            subject_id, SubjectId,
            subject_name, SubjectName,
            add_time, AddTime,
            expire_date, ExpireDate,
            amount, Amount,
            paid_amount, PaidAmount,
            count_lesson_total, CountLessonTotal, 
            count_lesson_complete, CountLessonComplete, 
            lesson_type, LessonType, 
            verify_state, VerifyState);
        
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
        if (ex_expired) {  // 要排除已过期的课程, 跳过已过期的课程
            if (dto->expired) {
                continue;
            }
        }
        page->rows->emplace_back(std::move(dto));
    }
    return page;

}
