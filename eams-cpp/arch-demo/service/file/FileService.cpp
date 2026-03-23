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
#include "FileService.h"
#include "dao/file/FileDAO.h"
#include "id/UuidFacade.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

std::string FileService::saveFile(const FileDTO::Wrapper& data)
{
	// 生成唯一标识
	UuidFacade uf;
	std::string id = uf.genUuid();
	// 创建do数据对象
	FileDO fdo;
	ZO_STAR_DOMAIN_DTO_TO_DO(fdo, data, Name, filename, FileType, fileType, SaveType, saveType, SavePath, savePath);
	if (data->remark && data->remark.getValue("") != "")
		fdo.setRemark(data->remark.getValue(""));
	fdo.setId(id);
	fdo.setStatus(1);
	// 保存数据
	FileDAO fd;
	if (fd.insert(fdo)) return id;
	return "";
}

FileDTO::Wrapper FileService::getFile(const std::string& id)
{
	// 查询数据
	FileDAO fd;
	auto res = fd.selectById(id);
	if (!res)
		return nullptr;
	auto dto = FileDTO::createShared();
	dto->id = res->getId();
	dto->filename = res->getName();
	dto->fileType = res->getFileType();
	dto->saveType = res->getSaveType();
	dto->remark = res->getRemark();
	dto->status = res->getStatus();
	dto->fileTypeName = res->getFileTypeName();
	dto->saveTypeName = res->getSaveTypeName();
	
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	// 拼接上地址前缀
	std::string urlPrefix = "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
	dto->savePath = urlPrefix + res->getSavePath();
	return dto;
}
