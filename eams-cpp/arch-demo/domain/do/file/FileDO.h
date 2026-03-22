#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 19:47:24

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
#ifndef _FILEDO_H_
#define _FILEDO_H_
#include "../DoInclude.h"

/**
 * 测试文件存储数据模型
 */
class FileDO :public BaseDO
{
	// 文件唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);
	// 文件名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 文件存储类型编码
	MYSQL_SYNTHESIZE(string, fileType, FileType);
	// 文件存储方式编码
	MYSQL_SYNTHESIZE(string, saveType, SaveType);
	// 文件存储路径
	MYSQL_SYNTHESIZE(string, savePath, SavePath);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 数据状态
	MYSQL_SYNTHESIZE(int, status, Status);
public:
	FileDO() : BaseDO("sample_file")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD_NULLABLE("file_type", "s", fileType, false);
		MYSQL_ADD_FIELD_NULLABLE("save_type", "s", saveType, false);
		MYSQL_ADD_FIELD_NULLABLE("save_path", "s", savePath, false);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD_NULLABLE("status", "i", status, false);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<FileDO> PtrFileDO;

/**
 * 文件视图对象，关联一些外表的字段
 */
class FileViewDO : public FileDO {
	// 文件类型名称
	MYSQL_SYNTHESIZE(string, fileTypeName, FileTypeName);
	// 文件保存类型名称
	MYSQL_SYNTHESIZE(string, saveTypeName, SaveTypeName);
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<FileViewDO> PtrFileViewDO;

#endif // !_FILEDO_H_