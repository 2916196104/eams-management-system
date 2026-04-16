#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 16:57:53

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
#ifndef _STUDENTINFOSERVICE_H_
#define _STUDENTINFOSERVICE_H_
#include "dao/AddStudent/AddStudentViewDAO.h"
#include "domain/dto/AddStudent/AddStudentDTO.h"
#include "domain/do/Mycustomers/StudentDo.h"
#include "dao/AddStudent/user/UserDAO.h"

/**
 * 文件业务操作类
 */
class StudentInfoService
{
private:
	//定义成员变量指针
	std::shared_ptr<AddStudentViewDAO> studentDao = std::make_shared<AddStudentViewDAO>();
	std::shared_ptr<UserDAO> userDao = std::make_shared<UserDAO>();
public:
	// 保存文件
	std::string saveStudentInfo(const AddStudentDTO::Wrapper& dto);
};

#endif // !_STUDENTINFOSERVICE_H_