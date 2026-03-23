#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/09/18 15:01:29

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
#ifndef _FILEDTO_H_
#define _FILEDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 添加文件表单数据
 */
class FileAddFormDTO : public oatpp::DTO
{
	DTO_INIT(FileAddFormDTO, DTO);
	// 文件名
	API_DTO_FIELD_DEFAULT(String, filename, ZH_WORDS_GETTER("file.field.filename"));
	// 文件类型编码
	API_DTO_FIELD_REQUIRE(String, fileType, ZH_WORDS_GETTER("file.field.ft"), true);
	// 文件存储类型编码
	API_DTO_FIELD_REQUIRE(String, saveType, ZH_WORDS_GETTER("file.field.st"), true);
	// 备注
	API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("file.field.remark"));
};

/**
 * 添加文件数据模型
 */
class FileAddDTO : public FileAddFormDTO
{
	DTO_INIT(FileAddDTO, FileAddFormDTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
};

/**
 * 完整文件数据存储模型
 */
class FileDTO : public FileAddFormDTO
{
	DTO_INIT(FileDTO, FileAddFormDTO);
	// 唯一标识
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("file.field.id"), true);
	// 保存路径
	API_DTO_FIELD_REQUIRE(String, savePath, ZH_WORDS_GETTER("file.field.path"), true);
	// 数据状态
	API_DTO_FIELD_DEFAULT(Int32, status, ZH_WORDS_GETTER("file.field.status"));
	// 文件类型名称
	API_DTO_FIELD_DEFAULT(String, fileTypeName, ZH_WORDS_GETTER("file.field.ftn"));
	// 文件存储类型名称
	API_DTO_FIELD_DEFAULT(String, saveTypeName, ZH_WORDS_GETTER("file.field.stn"));
};

/**
 * 多文件上传演示模型
 */
class FileMoreDTO : public oatpp::DTO
{
	DTO_INIT(FileMoreDTO, DTO);
	// 文件1
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file0, ZH_WORDS_GETTER("file.field.file"), true);
	// 文件2
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file1, ZH_WORDS_GETTER("file.field.file"), true);
	// 文件3
	API_DTO_FIELD_DEFAULT(oatpp::swagger::Binary, file2, ZH_WORDS_GETTER("file.field.file"));
};

/**
 * 单文件上传数据模型
 */
class FileOnlyDTO : public oatpp::DTO
{
	DTO_INIT(FileOnlyDTO, DTO);
	// 文件数据
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("file.field.file"), true);
};

/**
 * editor图片信息传输数据对象
 */
class EditorImageDTO : public oatpp::DTO
{
	DTO_INIT(EditorImageDTO, DTO);
	// 图片src
	API_DTO_FIELD(String, url, ZH_WORDS_GETTER("file.field.img-url"), true, {});
	// 图片文字描述
	API_DTO_FIELD_DEFAULT(String, alt, ZH_WORDS_GETTER("file.field.img-alt"));
	// 图片链接地址
	API_DTO_FIELD_DEFAULT(String, href, ZH_WORDS_GETTER("file.field.img-href"));
public:
	EditorImageDTO() {}
	EditorImageDTO(String url, String alt = "", String href = "")
	{
		this->url = url;
		this->alt = alt;
		this->href = href;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_FILEDTO_H_