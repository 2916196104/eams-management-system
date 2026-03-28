#include "stdafx.h"
#include "UpdateHeadImgService.h"
#include "dao/UserRelated/UserProfileDAO.h"
#include "dao/UserRelated/AttachmentDAO.h"
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
#include "SimpleDateTimeFormat.h"
#include "id/SnowFlake.h"
#include <limits>



ChangePictureDTO::Wrapper UpdateHeadImgService::updateHeadImg(long long userId,
	const char* data,
	size_t size,
	const std::string& fileName)
{

	static SnowFlake snowFlake(1, 1);
	// 用雪花算法生成id
	long long newId = snowFlake.nextId();
	//获取文件名字后缀
	string suffix;
	size_t pos = fileName.rfind('.');
	if(pos != string::npos) {
		suffix = fileName.substr(pos);
	}

	//上传到FastDFS
	ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
	if (size > static_cast<size_t>(std::numeric_limits<int>::max())) 
	{
		// 文件过大，无法上传
		auto dto = ChangePictureDTO::createShared();
		dto->head_img = nullptr;
		return dto;
	}
	string filepath = dfs.uploadFile(data, static_cast<int>(size), suffix);
	string fileUrl = urlPrefix + filepath;




	//构建附件对象
	AttachmentDO attachment;
	attachment.setId(newId);
	attachment.setFileName(fileName);
	attachment.setFileSize(size);
	attachment.setFileType(suffix);
	attachment.setName(fileName);
	attachment.setUrl(fileUrl);
	attachment.setSavePath(filepath);
	attachment.setAddTime(SimpleDateTimeFormat::format("%Y-%m-%d %H:%M:%S"));


	//// 打印调试信息
	//std::cout << "=== AttachmentDO Debug ===" << std::endl;
	//std::cout << "id: " << attachment.getId() << std::endl;
	//std::cout << "file_name: " << attachment.getFileName() << " (len=" << attachment.getFileName().length() << ")" << std::endl;
	//std::cout << "file_size: " << attachment.getFileSize() << std::endl;
	//std::cout << "file_type: " << attachment.getFileType() << " (len=" << attachment.getFileType().length() << ")" << std::endl;
	//std::cout << "name: " << attachment.getName() << " (len=" << attachment.getName().length() << ")" << std::endl;
	//std::cout << "url: " << attachment.getUrl() << " (len=" << attachment.getUrl().length() << ")" << std::endl;
	//std::cout << "save_path: " << attachment.getSavePath() << " (len=" << attachment.getSavePath().length() << ")" << std::endl;
	//std::cout << "add_time: " << attachment.getAddTime() << " (len=" << attachment.getAddTime().length() << ")" << std::endl;
	//std::cout << "==========================" << std::endl;


	//保存附件信息到数据库
	AttachmentDAO attachmentDAO;
	long long result = attachmentDAO.insertAttachment(attachment);
	if (result == 0) {
		auto dto = ChangePictureDTO::createShared();
		dto->head_img = nullptr;
		return dto;
	}

	//更新用户头像URL到数据库
	UserRelatedDAO userReleatDAO;
	bool updateResult = userReleatDAO.updateHeadImg(userId, fileUrl);
	if(updateResult == 0) {
		auto dto = ChangePictureDTO::createShared();
		dto->head_img = nullptr;
		return dto;
	} 

	auto dto = ChangePictureDTO::createShared();
	dto->head_img = fileUrl;
	return dto;

}