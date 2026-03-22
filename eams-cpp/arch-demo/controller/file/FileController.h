#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/05/17 11:19:05

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
#ifndef _FILECONTROLLER_H_
#define _FILECONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "domain/vo/file/FileVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("file.tag")
/**
 * 文件操作示例接口
 */
class FileController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(FileController);
public:
	// 定义一个单文件上传接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("file.upload.summary"), uploadFile, FileAddDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/file/upload", uploadFile, REQUEST(std::shared_ptr<IncomingRequest>, request), execUploadOne(request));

	// 定义一个多文件上传接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("file.upload-more.summary"), uploadFileMore, FileMoreDTO::Wrapper, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/file/upload-more", uploadFileMore, REQUEST(std::shared_ptr<IncomingRequest>, request), execUploadMore(request));

	// 定义一个流方式上传接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("file.upload-stream.summary"), uploadFileStream, StringJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_FILE_STREAM(); API_DEF_ADD_QUERY_PARAMS(String, "suffix", ZH_WORDS_GETTER("file.field.suffix"), "png", true);
	);
	// 定义端点
	ENDPOINT(API_M_POST, "/file/upload-stream", uploadFileStream, BODY_STRING(String, fileBody), QUERY(String, suffix), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(execUploadStream(fileBody, suffix));
	}

	// 定义一个文件上传接口用于处理富文本编辑器
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("file.editor-upload-image.summary"), uploadImage, FileOnlyDTO::Wrapper, EditorImageVO::Wrapper, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/file/editor-upload-image", uploadImage, REQUEST(std::shared_ptr<IncomingRequest>, request), execUploadEditorImage(request));

	// 定义一个获取文件信息接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("file.info.summary"), getFileInfo, FileJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("file.field.id"), "d9ecc4e41efd4a4c802ffd5e84147c31", true);
	);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/file/info", getFileInfo, QUERY(String, id), execGetFileInfo(id));

	// 定义一个文件下载接口
	// 定义描述
	API_DEF_ENDPOINT_INFO(
		ZH_WORDS_GETTER("file.download.summary"), downloadFile, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "filename", ZH_WORDS_GETTER("file.field.filename"), "file/test.jpg", true);
	);
	// 定义端点
	API_HANDLER_ENDPOINT_OPTION(API_M_GET, "/file/download", downloadFile, QUERY(String, filename), return execDownloadFile(filename););

	// 定义一个HTML文件接口
	// 定义描述
	API_DEF_ENDPOINT_INFO(ZH_WORDS_GETTER("file.html.summary"), htmlFile, Void, API_TAG);
	// 定义端点
	API_HANDLER_ENDPOINT_OPTION(API_M_GET, "/file/**", htmlFile, REQUEST(std::shared_ptr<IncomingRequest>, request), return execHtmlFile(request););
private: // 定义接口执行函数
	// 执行单文件上传处理
	StringJsonVO::Wrapper execUploadOne(std::shared_ptr<IncomingRequest> request);
	// 执行多文件上传处理
	ListJsonVO<String>::Wrapper execUploadMore(std::shared_ptr<IncomingRequest> request);
	// 执行流方式上传处理
	StringJsonVO::Wrapper execUploadStream(const String& fileBody, const String& suffix);
	// 执行Editor图片上传处理
	EditorImageVO::Wrapper execUploadEditorImage(std::shared_ptr<IncomingRequest> request);
	// 执行获取文件信息处理
	FileJsonVO::Wrapper execGetFileInfo(const String& id);
	// 执行文件下载处理
	std::shared_ptr<OutgoingResponse> execDownloadFile(const String& filename);
	// 执行HTML文件处理
	std::shared_ptr<OutgoingResponse> execHtmlFile(std::shared_ptr<IncomingRequest> request);
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_FILECONTROLLER_H_