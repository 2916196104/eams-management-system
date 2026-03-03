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
#ifndef _FILEMAPPER_H_
#define _FILEMAPPER_H_
#include "Mapper.h"
#include "domain/do/file/FileDO.h"

class FileViewMapper : public Mapper<PtrFileViewDO>
{
public:
	PtrFileViewDO mapper(ResultSet* resultSet) const override
	{
		PtrFileViewDO file = std::make_shared<FileViewDO>();
		file->setId(resultSet->getString("id"));
		file->setName(resultSet->getString("name"));
		file->setFileType(resultSet->getString("file_type"));
		file->setSaveType(resultSet->getString("save_type"));
		file->setSavePath(resultSet->getString("save_path"));
		file->setRemark(resultSet->getString("remark"));
		file->setStatus(resultSet->getInt("status"));
		file->setFileTypeName(resultSet->getString("file_type_name"));
		file->setSaveTypeName(resultSet->getString("save_type_name"));
		return file;
	}
};

#endif // !_FILEMAPPER_H_