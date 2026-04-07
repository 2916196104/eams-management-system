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
	// 增加对 phonenumber 的安全转换
	std::string phone = dto->phonenumber.getValue("");
	uint64_t userID = studentDao->getUserIdByPhone(phone);
	SnowFlake sf(1, 1);
	// 如果没有查到到 调用USERDAO插入
	if (userID == 0) {
		auto user = std::make_shared<UserDO>();
		if (dto->username)     user->setName(dto->username.getValue(""));
		if (dto->phonenumber)   user->setMobile(dto->phonenumber.getValue(""));
		// 生成ID

		userID = sf.nextId();
		user->setId(userID);
		user->setCreator(std::stoull(dto->getPayload()->getId()));
		// 设置创建时间
		user->setAddTime(SimpleDateTimeFormat::format());
		int temp = userDao->insert(*user.get());
		if (temp < 0) return "user表插入失败";
	}
	//组装DO数据
	auto student = std::make_shared<StudentDO>();
	// 3. 手动赋值 (跳过那个破宏，直接写，红线立刻消失)
	if (dto->name)     student->setName(dto->name.getValue(""));
	if (dto->gender)   student->setGender(dto->gender.getValue({0})); 
	if (dto->birthday) student->setBirthday(dto->birthday.getValue(""));//现在日期参数不填不行
	if (dto->idcard)   student->setIdcard(dto->idcard.getValue(""));
	if (dto->remark)   student->setRemark(dto->remark.getValue(""));
	if (dto->stage)   student->setStage(dto->stage.getValue({0}));
	if (dto->admitTime)   student->setJoinDate(dto->admitTime.getValue(""));
	if (dto->kinship)   student->setFamilyRel(dto->kinship.getValue({ 0 }));
	if (dto->schoolId)   student->setSchoolId(dto->schoolId.getValue({ 0 }));
	if (dto->grade)   student->setGrade(dto->grade.getValue({ 0 }));
	student->setUserId(userID);
	
	// 生成ID
	student->setId(sf.nextId());
	student->setCreator(std::stoull(dto->getPayload()->getId()));
	
	
	// 设置创建时间
	student->setAddTime(SimpleDateTimeFormat::format());

	// 执行数据添加
	uint64_t finalId = studentDao->insert(*student.get());
	return finalId > 0 ? std::to_string(finalId) : "";
}

