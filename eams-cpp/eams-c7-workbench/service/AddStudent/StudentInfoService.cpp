/* Copyright Zero One Star. All rights reserved. */
#include "stdafx.h"
#include "StudentInfoService.h"
#include "domain/dto/AddStudent/AddStudentDTO.h"
#include "dao/AddStudent/AddStudentViewDAO.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
#include "domain/do/AddStudent/UserDO.h"
#include "NacosClient.h"

std::string StudentInfoService::saveStudentInfo(const AddStudentDTO::Wrapper& dto) {
    // 获取SQL会话，用于事务管理
    auto sqlSession = getSqlSession();
    std::string result = "";

    try {
        // 开始事务
        sqlSession->beginTransaction();

        // 增加对 phonenumber 的安全转换
        std::string phone = dto->phonenumber.getValue("");
        if (phone.empty()) {
            throw std::runtime_error("手机号不能为空");
        }

        uint64_t userID = studentDao->getUserIdByPhone(phone);
        SnowFlake sf(1, 1);

        // 如果没有查到用户，则插入新用户
        if (userID == 0) {
            auto user = std::make_shared<UserDO>();
            if (dto->username) {
                user->setName(dto->username.getValue(""));
            }

            user->setMobile(phone);

            // 生成ID
            userID = sf.nextId();
            user->setId(userID);

            std::string payloadIdStr = dto->getPayload()->getId();
            uint64_t creatorId = 0;

            if (!payloadIdStr.empty()) {
                try {
                    creatorId = std::stoull(payloadIdStr);
                }
                catch (const std::invalid_argument& e) {
                    // 记录日志，但不抛出异常
                    std::cerr << "WARN: Invalid creator ID format: " << payloadIdStr << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "WARN: Creator ID out of range: " << payloadIdStr << std::endl;
                }
            }
            else {
                std::cerr << "WARN: Payload ID is empty." << std::endl;
            }

            user->setCreator(creatorId);
            user->setAddTime(SimpleDateTimeFormat::format());

            // 尝试插入用户，如果失败（如手机号已存在），则重新查询
            try {
                int temp = userDao->insert(*user.get());
                if (temp < 0) {
                    // 插入失败，可能用户已存在，重新查询
                    userID = studentDao->getUserIdByPhone(phone);
                    if (userID == 0) {
                        throw std::runtime_error("用户插入失败且未找到已存在用户");
                    }
                }
            }
            catch (const std::exception& e) {
                // 捕获插入异常，尝试重新查询
                std::cerr << "WARN: 插入用户时发生异常: " << e.what() << std::endl;
                userID = studentDao->getUserIdByPhone(phone);
                if (userID == 0) {
                    throw;
                }
            }
        }

        // 组装学生数据
        auto student = std::make_shared<StudentDO>();

        if (dto->name) student->setName(dto->name.getValue(""));
        if (dto->gender) student->setGender(dto->gender.getValue({ 0 }));
        if (dto->birthday) student->setBirthday(dto->birthday.getValue(""));
        if (dto->idcard) student->setIdcard(dto->idcard.getValue(""));
        if (dto->remark) student->setRemark(dto->remark.getValue(""));
        if (dto->stage) student->setStage(dto->stage.getValue({ 0 }));
        if (dto->admitTime) student->setJoinDate(dto->admitTime.getValue(""));
        if (dto->kinship) student->setFamilyRel(dto->kinship.getValue({ 0 }));
        if (dto->schoolId) student->setSchoolId(dto->schoolId.getValue({ 0 }));
        if (dto->grade) student->setGrade(dto->grade.getValue({ 0 }));

        student->setUserId(userID);
        student->setId(sf.nextId());

        // 安全设置创建者ID
        std::string payloadIdStr = dto->getPayload()->getId();
        uint64_t creatorId = 0;
        if (!payloadIdStr.empty()) {
            try {
                creatorId = std::stoull(payloadIdStr);
                student->setCreator(creatorId);
            }
            catch (...) {
                student->setCreator(0);
            }
        }

        student->setAddTime(SimpleDateTimeFormat::format());

        // 执行学生数据插入
        uint64_t finalId = studentDao->insert(*student.get());
        if (finalId == 0) {
            throw std::runtime_error("学生信息插入失败");
        }

        // 提交事务
        sqlSession->commitTransaction();
        result = std::to_string(finalId);

    }
    catch (const std::exception& e) {
        // 回滚事务
        try {
            sqlSession->rollbackTransaction();
        }
        catch (...) {
            // 忽略回滚异常
        }

        std::cerr << "ERROR: 保存学生信息失败: " << e.what() << std::endl;
        result = "";
    }
    catch (...) {
        // 回滚事务
        try {
            sqlSession->rollbackTransaction();
        }
        catch (...) {
            // 忽略回滚异常
        }

        std::cerr << "ERROR: 保存学生信息时发生未知异常" << std::endl;
        result = "";
    }

    return result;
}