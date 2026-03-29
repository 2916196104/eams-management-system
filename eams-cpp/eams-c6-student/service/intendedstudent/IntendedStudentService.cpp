#include "stdafx.h"
#include "IntendedStudentService.h"
#include "../../dao/intendedstudent/IntendedStudentDAO.h"
#include "../../domain/do/student/UserDO.h"
#include "../../domain/do/student/StudentDO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

// 静态变量（线程安全）
static std::mutex g_snowflakeMutex;
static uint64_t g_lastTimestamp = 0;
static uint64_t g_sequence = 0;

// 生成纯数字唯一ID（适合bigint）
static uint64_t genSnowflakeId()
{
    std::lock_guard<std::mutex> lock(g_snowflakeMutex);

    // 获取当前毫秒时间戳
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    // 处理同一毫秒内并发（12位序列号，最大4096个/毫秒）
    if (ms == g_lastTimestamp) {
        g_sequence = (g_sequence + 1) & 0xFFF;  // 序列号0-4095循环
        if (g_sequence == 0) {
            // 序列号溢出，等待下一毫秒
            while (ms <= g_lastTimestamp) {
                now = std::chrono::system_clock::now();
                ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
            }
        }
    }
    else {
        g_sequence = 0;
    }

    g_lastTimestamp = ms;

    // 组合：时间戳(42位) + 序列号(12位) = 54位十进制数
    // 示例：1774453123456789（16-19位，完全在bigint范围内）
    return (ms << 12) | g_sequence;
}

// 生成字符串形式的数字ID（直接用于setId）
static std::string genNumericId() {
    return std::to_string(genSnowflakeId());
}


std::list<IntendedExportDTO::Wrapper> IntendedService::listByIds(const std::vector<std::string>& ids)
{
    IntendedExportDAO dao;
    std::list<PtrStudentDetail> details = dao.selectByIds(ids);

    // 转换为导出DTO
    std::list<IntendedExportDTO::Wrapper> result;
    for (PtrStudentDetail& detail : details)
    {
        auto dto = IntendedExportDTO::createShared();

        // id 单独处理：string 转 UInt64
        dto->id = std::stoull(detail->student.getId());

        // student 部分
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->student,
            name, Name,
            gender, Gender,
            familyRel, FamilyRel,
            birthday, Birthday
        );

        // user 部分
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->user,
            mobile, Mobile,
            parentName, Name
        );

        // org 部分
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->org,
            schoolName, Name
        );

        // class_grade 部分
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->classGrade,
            gradeName, Name
        );

        // staff 部分
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, detail->staff,
            counselorName, Name
        );

        result.push_back(dto);
    }
    return result;
}

bool IntendedService::importBatch(const oatpp::List<IntendedAddDTO::Wrapper>& datas)
{
    if (!datas || datas->size() == 0) {
        return false;
    }

    UuidFacade uf(1);
    std::string now = SimpleDateTimeFormat::format();

    IntendedImportDAO dao;
    SqlSession* session = dao.getSqlSession();

    session->beginTransaction();

    try
    {
        for (auto& dto : *datas)
        {
            // 1. 查/插 User（家长）
            uint64_t userIdNum = dao.selectUserIdByMobile(dto->mobile.getValue(""), session);
            std::string userIdStr;

            if (userIdNum == 0) {
                // 手机号不存在，新建 User
                ExcelUserDO user;
                user.setId(genNumericId());
                user.setMobile(dto->mobile.getValue(""));
                user.setPassword(dto->password.getValue(""));
                user.setName(dto->parent.getValue(""));

                int result = dao.insertUser(user, session);
                if (result == 0) {
                    // 恢复了被禁用的旧账号，重新查询获取 ID
                    userIdNum = dao.selectUserIdByMobile(dto->mobile.getValue(""), session);
                    if (userIdNum == 0) {
                        throw std::runtime_error("恢复家长账号后查询失败: " + dto->mobile.getValue(""));
                    }
                    userIdStr = std::to_string(userIdNum);
                }
                else if (result < 0) {
                    throw std::runtime_error("插入家长失败: " + dto->mobile.getValue(""));
                }
                else {
                    // 成功插入新用户
                    userIdStr = user.getId();
                }
            }
            else {
                // 已存在，直接使用
                userIdStr = std::to_string(userIdNum);
            }

            // 2. 插 Student（学员）
            ExcelStudentDO stu;
            stu.setId(genNumericId());
            stu.setUserId(userIdStr);              // 关联上面的 User
            stu.setName(dto->name.getValue(""));
            stu.setGender(dto->sex);               // 如果 sex 是 Int32，可能需要 getValue()
            stu.setBirthday(dto->birthday.getValue(""));
            stu.setIdcard(dto->idCard.getValue(""));

            if (dao.insertStudent(stu, session) <= 0) {
                throw std::runtime_error("插入学员失败: " + dto->name);
            }
        }

        session->commitTransaction();
        return true;

    }
    catch (const std::exception& e) {
        session->rollbackTransaction();
        return false;
    }
}