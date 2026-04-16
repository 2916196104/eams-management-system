#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/16 15:47:39

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
#ifndef _ADDSTUDENTVIEWMAPPER_H_
#define _ADDSTUDENTVIEWMAPPER_H_
#include "Mapper.h"
#include "domain/do/AddStudent/AddStudentViewDO.h"
#include "domain/do/Mycustomers/StudentDo.h"

class AddStudentViewMapper : public Mapper<PtrAddStudentViewDo>
{
public:
	PtrAddStudentViewDo mapper(ResultSet* resultSet) const override
	{
		PtrAddStudentViewDo file = std::make_shared<AddStudentViewDo>();
		// Ó³Éä»ù´¡×Ö¶Î
		file->setName(resultSet->getString("name"));
		file->setStage(resultSet->getInt("stage"));
		file->setGender(resultSet->getInt("gender"));
		file->setBirthday(resultSet->getString("birthday"));
		file->setIdcard(resultSet->getString("idcard"));
		file->setRemark(resultSet->getString("remark"));
		file->setUserId(resultSet->getInt("user_id"));
		file->setSchoolId(resultSet->getInt("school_id"));
		file->setFamilyRel(resultSet->getInt("family_rel"));
		file->setAddTime(resultSet->getString("add_time"));
		file->setCreator(resultSet->getInt("creator"));
		file->setGrade(resultSet->getInt("grade"));
		file->setJoinDate(resultSet->getString("join_date"));

		return file;
	}
};


#endif // !_ADDSTUDENTVIEWMAPPER_H_
