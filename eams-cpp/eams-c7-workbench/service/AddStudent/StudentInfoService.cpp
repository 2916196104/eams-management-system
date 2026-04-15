/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 16:58:02

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "StudentInfoService.h"
#include "domain/dto/AddStudent/AddStudentDTO.h"
#include "dao/AddStudent/AddStudentViewDAO.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
#include "domain/do/AddStudent/UserDO.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

std::string StudentInfoService::saveStudentInfo(const AddStudentDTO::Wrapper& dto)
{
    std::string result = "";

    try {
        // 增加对 phonenumber 的安全转换
        std::string phone = dto->phonenumber.getValue("");
        if (phone.empty()) {
            std::cerr << "ERROR: 手机号为空" << std::endl;
            return "";
        }

        uint64_t userID = studentDao->getUserIdByPhone(phone);
        SnowFlake sf(1, 1);

        // 如果没有查到用户，则插入新用户
        if (userID == 0) {
            auto user = std::make_shared<UserDO>();
            if (dto->username) {
                user->setName(dto->username.getValue(""));
            }
            else {
                // 如果用户名不存在，使用手机号作为用户名
                user->setName("用户_" + phone.substr(phone.length() - 4));
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

            // 尝试插入用户
            int insertResult = userDao->insert(*user.get());
            if (insertResult < 0) {
                // 插入失败，可能是手机号已存在，重新查询
                std::cerr << "WARN: 用户插入失败，尝试重新查询..." << std::endl;
                userID = studentDao->getUserIdByPhone(phone);
                if (userID == 0) {
                    std::cerr << "ERROR: 用户插入失败且未找到已存在用户" << std::endl;
                    return "";
                }
                std::cout << "INFO: 用户已存在，userID: " << userID << std::endl;
            }
            else {
                std::cout << "INFO: 用户插入成功，userID: " << userID << std::endl;
            }
        }
        else {
            std::cout << "INFO: 用户已存在，userID: " << userID << std::endl;
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

        // 设置必填字段默认值
        if (student->getName().empty()) {
            std::cerr << "ERROR: 学生姓名为空" << std::endl;
            return "";
        }

        if (student->getSchoolId() == 0) {
            // 如果学校ID为0，设置为默认值1（根据实际情况调整）
            student->setSchoolId(1);
            std::cerr << "WARN: 学校ID为空，使用默认值1" << std::endl;
        }

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
                // 如果转换失败，使用用户ID或默认值
                student->setCreator(userID);
                std::cerr << "WARN: Creator ID转换失败，使用userID: " << userID << std::endl;
            }
        }
        else {
            // 如果没有creator，使用userID
            student->setCreator(userID);
        }

        student->setAddTime(SimpleDateTimeFormat::format());

        // 检查必填字段
        if (student->getCreator() == 0) {
            student->setCreator(1); // 使用默认管理员ID
        }

        if (student->getAddTime().empty()) {
            student->setAddTime(SimpleDateTimeFormat::format());
        }

        // 执行学生数据插入
        uint64_t finalId = studentDao->insertStudent(*student.get());
        if (finalId == 0) {
            std::cerr << "ERROR: 学生信息插入失败" << std::endl;
            return "";
        }

        result = std::to_string(finalId);
        std::cout << "INFO: 学生信息插入成功，studentID: " << result << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: 保存学生信息失败: " << e.what() << std::endl;
        result = "";
    }
    catch (...) {
        std::cerr << "ERROR: 保存学生信息时发生未知异常" << std::endl;
        result = "";
    }

    return result;
}