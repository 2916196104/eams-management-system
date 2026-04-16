#include"stdafx.h"
#include"ChangePictureController.h"

#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
#include "SimpleDateTimeFormat.h"
#include "service/UserRelated/UpdateHeadImgService.h"



ChangePictureVO::Wrapper ChangePictureController::execQueryChangePicture(const PayloadDTO& payload, std::shared_ptr<IncomingRequest> request) {

	//获取pyload中的用户唯一id
	auto userID = payload.getId();
	// 2. 解析 multipart
	API_MULTIPART_INIT(container, reader);
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	request->transferBody(&reader);
	// 3. 获取文件部分
	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);

	//4.获取文件名
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "filename", filename);
	string pfn = partfile->getFilename().getValue("");
	string finalFileName = (filename && filename.getValue("") != "") ? filename.getValue("") : pfn;

	// 4. 提取文件信息
	const char* data = file->data();
	size_t size = file->size();

	//5.调用service层进行头像修改
	UpdateHeadImgService updateHeadImgService;
	auto changePictureDTO = updateHeadImgService.updateHeadImg(std::stoll(userID), data, size, finalFileName);

	//6. 构建响应对象
	auto changePictureVO = ChangePictureVO::createShared();
	changePictureVO->success(changePictureDTO);

	return changePictureVO;

}