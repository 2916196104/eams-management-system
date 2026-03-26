/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 15:54:59

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
#include "FileDAO.h"
#include "FileMapper.h"

PtrFileViewDO FileDAO::selectById(const string& id)
{
	string sql = R"(SELECT 
		f.id,
		f.`name`,
		f.file_type,
		f.save_type,
		f.save_path,
		f.remark,
		f.`status`,
		fti.`name` AS file_type_name,
		sti.`name` AS save_type_name
		FROM
		sample_file f
		LEFT JOIN(
			SELECT
			di.`code`,
			di.`name`
			FROM
			sample_dict_item di
			JOIN
			sample_dict d ON d.id = di.dict_id
			WHERE
			d.`code` = 'file_type'
		) fti ON f.file_type = fti.`code`
		LEFT JOIN(
			SELECT
			di.`code`,
			di.`name`
			FROM
			sample_dict_item di
			JOIN
			sample_dict d ON d.id = di.dict_id
			WHERE
			d.`code` = 'save_way'
		) sti ON f.save_type = sti.`code`
		WHERE
		f.id = ?)";
	return sqlSession->executeQueryOne<PtrFileViewDO>(sql, FileViewMapper(), "%s", id);
}
