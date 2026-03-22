/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/05/17 11:37:57

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
#include <iostream>
#include "FileController.h"

// FastDFS需要导入的头
#include "ServerInfo.h"
#include "NacosClient.h"
#include "FastDfsClient.h"
#include "SimpleDateTimeFormat.h"
#include "../../service/file/FileService.h"

// 文件下载地址前缀
#define DISK_FILE_SERVER_ADDR "http://127.0.0.1:"+ServerInfo::getInstance().getServerPort()+"/file/download?filename="

// 将保存文件到磁盘测试逻辑
#define SAVE_FILE_TO_DISK(file, newFileName) \
/* 获取文件后缀名 */ \
string filename = part##file->getFilename().getValue(""); \
string suffix = ""; \
size_t pos = filename.rfind("."); \
if (pos != string::npos) \
{ \
	suffix = filename.substr(pos + 1); \
} \
/* 将文件保存到磁盘上面 */ \
std::string newFileName = SimpleDateTimeFormat::formatWithMilli("%Y%m%d%H%M%S", "") + "." + suffix; \
string fullPath = "public/static/file/" + newFileName; \
file.saveToFile(fullPath.c_str())

StringJsonVO::Wrapper FileController::execUploadOne(std::shared_ptr<IncomingRequest> request)
{
	// 1 初始化
	API_MULTIPART_INIT(container, reader);

	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	//API_MULTIPART_CONFIG_MEMO(reader, "file", -1);
	//API_MULTIPART_CONFIG_MEMO(reader, "nickname", -1);
	//API_MULTIPART_CONFIG_MEMO(reader, "age", -1);

	// 3 读取数据
	request->transferBody(&reader);

	/* 打印上传总部分数 */
	OATPP_LOGD("Multipart", "parts_count=%d", container->count());

	// 4 解析数据
	/* TODO: 解析的数据具体逻辑，需要根据你的业务需求来，下面是使用示例而已。 */

	// 4.1 处理文件数据，将文件上传到FastDFS上面
	/* 获取文件数据 */
	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "filename", filename);
	string filepath = "";
	if (file)
	{
		// 如果没有指定文件名，则使用文件上传时指定的文件名
		string pfn = partfile->getFilename().getValue("");
		if (!filename || filename.getValue("") == "") filename = pfn;

		// 获取文件后缀名
		string suffix = "";
		size_t pos = pfn.rfind(".");
		if (pos != string::npos)
			suffix = pfn.substr(pos + 1);
		// 上传文件FastDFS
		ZO_CREATE_DFS_CLIENT_URL(dfs, urlPrefix);
		filepath = dfs.uploadFile(file->data(), file->size(), suffix);
		// 打印文件上传成功后的下载地址
		string downloadUrl = urlPrefix + filepath;
		OATPP_LOGD("Multipart", "download url='%s'", downloadUrl.c_str());
	}

	// 4.2 处理表单数据，存储到数据库上面
	/* 获取表单数据 */
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "fileType", fileType);
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "saveType", saveType);
	API_MULTIPART_PARSE_FORM_FIELD_STR(container, "remark", remark);
	/* 构建保存数据对象 */
	auto fileForm = FileDTO::createShared();
	fileForm->savePath = filepath;
	fileForm->filename = filename;
	fileForm->fileType = fileType;
	fileForm->saveType = saveType;
	fileForm->remark = remark;
	/* 呼叫服务层保存数据 */
	std::string id = FileService().saveFile(fileForm);

	// 5 响应结果
	auto jvo = StringJsonVO::createShared();
	if (id != "")
		jvo->success(id);
	else
		jvo->fail("");
	return jvo;
}

ListJsonVO<String>::Wrapper FileController::execUploadMore(std::shared_ptr<IncomingRequest> request)
{
	// 1 初始化
	API_MULTIPART_INIT(container, reader);

	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	//API_MULTIPART_CONFIG_FILE(reader, "file0", "public/static/file/test0.png");
	//API_MULTIPART_CONFIG_FILE(reader, "file1", "public/static/file/test1.png");

	// 3 读取数据
	request->transferBody(&reader);

	/* 打印上传总部分数 */
	OATPP_LOGD("Multipart", "parts_count=%d", container->count());

	// 4 解析数据
	/* TODO: 解析的数据具体逻辑，需要根据你的业务需求来，下面是使用示例而已。 */
	auto jvo = ListJsonVO<String>::createShared();
	API_MULTIPART_PARSE_FILE_FIELD(container, "file0", file0);
	API_MULTIPART_PARSE_FILE_FIELD(container, "file1", file1);
	API_MULTIPART_PARSE_FILE_FIELD(container, "file2", file2);
	if (file0)
	{
		SAVE_FILE_TO_DISK(file0, newFileName);
		jvo->addData(DISK_FILE_SERVER_ADDR + "file/" + newFileName);
	}
	if (file1)
	{
		SAVE_FILE_TO_DISK(file1, newFileName);
		jvo->addData(DISK_FILE_SERVER_ADDR + "file/" + newFileName);
	}
	if (file2)
	{
		SAVE_FILE_TO_DISK(file2, newFileName);
		jvo->addData(DISK_FILE_SERVER_ADDR + "file/" + newFileName);
	}
	// 5 响应结果
	jvo->setStatus(RS_SUCCESS);
	return jvo;
}

StringJsonVO::Wrapper FileController::execUploadStream(const String& fileBody, const String& suffix)
{
	// 测试逻辑，将文件保存到磁盘
	std::string newFileName = SimpleDateTimeFormat::formatWithMilli("%Y%m%d%H%M%S", "") + "." + suffix;
	string fullPath = "public/static/file/" + newFileName;
	fileBody.saveToFile(fullPath.c_str());

	// 创建响应数据
	auto vo = StringJsonVO::createShared();
	vo->success(DISK_FILE_SERVER_ADDR + "file/" + newFileName);
	return vo;
}

EditorImageVO::Wrapper FileController::execUploadEditorImage(std::shared_ptr<IncomingRequest> request)
{
	// 1 初始化
	API_MULTIPART_INIT(container, reader);
	// 2 配置读取器
	API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);
	// 3 读取数据
	request->transferBody(&reader);
	// 4 获取文件数据
	/* TODO: 解析的数据具体逻辑，需要根据你的业务需求来，下面是使用示例而已。 */
	API_MULTIPART_PARSE_FILE_FIELD(container, "file", file);
	if (file)
	{
		// 保存文件到服务器本地磁盘
		SAVE_FILE_TO_DISK(file, newFileName);
		// 测试响应数据
		string downloadUrl = DISK_FILE_SERVER_ADDR + "file/" + newFileName;
		auto jvo = EditorImageVO::createShared();
		jvo->success(EditorImageDTO::createShared(downloadUrl));
		return jvo;
	}
	// 5 响应失败
	auto jvo = EditorImageVO::createShared();
	jvo->fail({});
	return jvo;
}

FileJsonVO::Wrapper FileController::execGetFileInfo(const String& id)
{
	auto jvo = FileJsonVO::createShared();
	//呼叫服务层查询文件信息
	auto info = FileService().getFile(id);
	if (info)
		jvo->success(info);
	else
		jvo->fail({});
	return jvo;
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> FileController::execDownloadFile(const String& filename)
{
	// 构建文件全路径
	std::string fullPath = "public/static/" + URIUtil::urlDecode(filename.getValue(""));

	// 读取文件
	auto fstring = String::loadFromFile(fullPath.c_str());

	// 判断是否读取成功
	if (!fstring)
	{
		std::cerr << "Failed to open file: " << std::strerror(errno) << std::endl;
		return createResponse(Status::CODE_404, "File Not Found");
	}

	// 创建响应头
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头信息
	response->putHeader("Content-Disposition", "attachment; filename=" + filename.getValue(""));

	// 影响成功结果
	return response;
}

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse> FileController::execHtmlFile(std::shared_ptr<IncomingRequest> request)
{
	// 获取文件路径
	auto filename = request->getPathTail();

	// 构建文件全路径
	std::string fullPath = "public/" + filename.getValue("");

	// 读取文件
	auto fstring = String::loadFromFile(fullPath.c_str());

	// 判断是否读取成功
	if (!fstring)
	{
		std::cerr << "Failed to open file<" << filename.getValue("") << ">: " << std::strerror(errno) << std::endl;
		const char* html = R"(
			<html>
             <head><title>404</title></head>
			 <body>
			  <h1>Page Not Found</h1>
			 </body>
			</html>)";
		auto response = createResponse(Status::CODE_404, html);
		response->putHeader(Header::CONTENT_TYPE, "text/html");
		return response;
	}

	// 创建响应对象
	auto response = createResponse(Status::CODE_200, fstring);

	// 根据文件不同类型设置不同响应头，有可能HTML中包含js和css文件，图片暂不处理
	if (filename->find(".js") != string::npos)
		response->putHeader(Header::CONTENT_TYPE, "text/javascript; charset=utf-8");
	else if (filename->find(".css") != string::npos)
		response->putHeader(Header::CONTENT_TYPE, "text/css");
	else
		response->putHeader(Header::CONTENT_TYPE, "text/html");

	// 响应结果
	return response;
}
