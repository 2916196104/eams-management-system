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
#ifndef _FILESERVICE_H_
#define _FILESERVICE_H_
#include "domain/dto/file/FileDTO.h"

/**
 * 文件业务操作类
 */
class FileService
{
public:
	// 保存文件
	std::string saveFile(const FileDTO::Wrapper& data);
	// 获取文件
	FileDTO::Wrapper getFile(const std::string& id);
};

#endif // !_FILESERVICE_H_