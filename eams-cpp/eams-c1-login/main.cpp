/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 23:02:34

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
#include "StringUtil.h"
#include "ServerInfo.h"
#include "HttpServer.h"
#include "controller/Router.h"
#include "controller/OtherComponent.hpp"
#include "DbInit.h"

#ifdef LINUX
#include "NacosClient.h"
#endif

/**
 * 服务器参数解析
 * 注意：
 * 参数中数据需要满足一定的格式，如：sp=8090、sn=feign-cpp-sample
 * 前缀与真实值之间使用=分隔
 */
void parseServerArgs(int argc, char* argv[]) {
	// 服务器端口
	std::string serverPort = "8090";
	// 数据库连接信息
	std::string dbUsername = "";
	std::string dbPassword = "";
	std::string dbName = "";
	std::string dbHost = "";
	int dbPort = -1;
	int dbMax = -1;
#ifdef LINUX
	// Nacos配置参数
	std::string nacosAddr = "192.168.153.15";
	std::string nacosNs = "eams-cpp-dev";
	std::string serviceName = "";
	std::string regIp = "";
#endif

	// 开始解析
	int currIndex = 1;
	int setDbParamNum = 0;
	while (currIndex < argc)
	{
		// 拆分字符串
		auto args = StringUtil::split(argv[currIndex], "=");
		// 判断参数是否合法
		if (args.size() != 2)
		{
			cout << "arg: " << argv[currIndex] << ", format error." << endl;
			exit(1);
		}

		// 根据参数前缀对不同属性赋值
		std::string prefix = args[0];
		std::string val = args[1];
		if (prefix == "sp") serverPort = val;
		else if (prefix == "du")
		{
			setDbParamNum++;
			dbUsername = val;
		}
		else if (prefix == "dp")
		{
			setDbParamNum++;
			dbPassword = val;
		}
		else if (prefix == "dn")
		{
			setDbParamNum++;
			dbName = val;
		}
		else if (prefix == "dh")
		{
			setDbParamNum++;
			dbHost = val;
		}
		else if (prefix == "dP")
		{
			setDbParamNum++;
			dbPort = atoi(val.c_str());
		}
		else if (prefix == "dm") dbMax = atoi(val.c_str());
#ifdef LINUX
		else if (prefix == "na") nacosAddr = val;
		else if (prefix == "ns") nacosNs = val;
		else if (prefix == "sn") serviceName = val;
		else if (prefix == "ip") regIp = val;
#endif
		// 更新索引
		currIndex++;
	}

	// 从配置中获取数据库配置
	if (setDbParamNum < 5)
	{
#ifdef LINUX
		// 获取Nacos中的数据库配置
		NacosClient nacosClient(nacosAddr, nacosNs);
		YAML::Node node = nacosClient.getConfig("data-source.yaml");
#else
		// 获取配置文件中的数据库配置
		YAML::Node node = YAML::LoadFile("./conf/data-source.yaml");
#endif
		// 解析配置信息
		YamlHelper yaml;
		std::string dbUrl = yaml.getString(&node, "spring.datasource.url");
		if (dbUrl != "")
		{
			// 解析数据库连接字符串
			yaml.parseDbConnUrl(dbUrl, &dbHost, &dbPort, &dbName);
			// 获取数据库用户名和密码
			dbUsername = dbUsername == "" ? yaml.getString(&node, "spring.datasource.username") : dbUsername;
			dbPassword = dbPassword == "" ? yaml.getString(&node, "spring.datasource.password") : dbPassword;
			dbMax = dbMax == -1 ? atoi(yaml.getString(&node, "spring.datasource.druid.max-active").c_str()) : dbMax;
		}
	}

	// 记录服务器配置到内存中方便使用
	ServerInfo::getInstance().setServerPort(serverPort);
	ServerInfo::getInstance().setDbUsername(dbUsername);
	ServerInfo::getInstance().setDbPassword(dbPassword);
	ServerInfo::getInstance().setDbName(dbName);
	ServerInfo::getInstance().setDbHost(dbHost);
	ServerInfo::getInstance().setDbPort(dbPort);
	ServerInfo::getInstance().setDbMax(dbMax);
#ifdef LINUX
	ServerInfo::getInstance().setNacosAddr(nacosAddr);
	ServerInfo::getInstance().setNacosNs(nacosNs);
	ServerInfo::getInstance().setRegIp(regIp);
	ServerInfo::getInstance().setServiceName(serviceName);
#endif
}

int main(int argc, char* argv[]) {
	// 服务器参数初始化
	parseServerArgs(argc, argv);

#ifndef _RELEASE_DOC_
	// 初始数据库连接
	bool initConnPool = DbInit::initDbPool(DBConfig(
		ServerInfo::getInstance().getDbUsername(),
		ServerInfo::getInstance().getDbPassword(),
		ServerInfo::getInstance().getDbName(),
		ServerInfo::getInstance().getDbHost(),
		ServerInfo::getInstance().getDbPort(),
		ServerInfo::getInstance().getDbMax()));
	if (!initConnPool) return -1;
#endif

#ifdef LINUX
	// 创建Nacos客户端对象
	NacosClient nacosClient(
		ServerInfo::getInstance().getNacosAddr(),
		ServerInfo::getInstance().getNacosNs());

	// 注册服务
	if (!ServerInfo::getInstance().getServiceName().empty() && !ServerInfo::getInstance().getRegIp().empty())
	{
		nacosClient.registerInstance(
			ServerInfo::getInstance().getRegIp(),
			atoi(ServerInfo::getInstance().getServerPort().c_str()),
			ServerInfo::getInstance().getServiceName());
	}
#endif

	// 启动HTTP服务器
	HttpServer::startServer(ServerInfo::getInstance().getServerPort(),
		[=](Endpoints* doc, HttpRouter* router) {
			Router(doc, router).initRouter();
		},
		[](std::shared_ptr<AbstractComponentReg>* o) {
			*o = std::make_shared<OtherComponent>();
		});

#ifndef _RELEASE_DOC_
	// 释放数据库连接
	DbInit::releasePool();
#endif

#ifdef LINUX
	// 反注册服务
	if (!ServerInfo::getInstance().getServiceName().empty() && !ServerInfo::getInstance().getRegIp().empty())
	{
		nacosClient.deregisterInstance(
			ServerInfo::getInstance().getRegIp(),
			atoi(ServerInfo::getInstance().getServerPort().c_str()),
			ServerInfo::getInstance().getServiceName());
	}
#endif
	return 0;
}
