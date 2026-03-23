/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/19 16:19:31

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
#include "UserService.h"
#include "id/UuidFacade.h"
#include "dao/user/UserDAO.h"
#include "dao/user/AddressDAO.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

std::string UserService::getDfsServerAddrssUrl()
{
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
}

UserPageDTO::Wrapper UserService::listAll(const UserQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = UserPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	UserDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	std::string urlPrefix = getDfsServerAddrssUrl();
	// 获取分页数据
	auto list = ud.selectAll(query);
	for (auto one : list)
	{
		auto user = UserDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(user, one, id, Id, nickname, Nickname, age, Age, idCard, IdCard, avatar, Avatar);
		if (one->getFile())
		{
			user->avatarUrl = urlPrefix + one->getFile()->getSavePath();
		}
		page->addData(user);
	}
	return page;
}

std::string UserService::saveUser(const UserAddDTO::Wrapper& dto)
{
	// 生成唯一标识
	UuidFacade uf;
	auto id = uf.genUuid();

	// 数据转换
	UserDO udo;
	udo.setId(id);
	ZO_STAR_DOMAIN_DTO_TO_DO(udo, dto, Nickname, nickname, Age, age, IdCard, idCard, Avatar, avatar);

	// 保存数据
	UserDAO ud;
	if (ud.insert(udo)) return id;
	return "";
}

UserDetailDTO::Wrapper UserService::getUserDetail(const oatpp::String& id)
{
	// 获取用户主数据
	UserDAO ud;
	auto data = ud.selectById(id.getValue(""));
	if (!data)
		return nullptr;
	auto dto = UserDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, data, id, Id, nickname, Nickname, age, Age, idCard, IdCard, avatar, Avatar);
	if (data->getFile())
	{
		dto->avatarUrl = getDfsServerAddrssUrl() + data->getFile()->getSavePath();
	}
	// 获取收货地址数据
	AddressDAO ad;
	auto address = ad.selectByUserId(id.getValue(""));
	for (auto one : address)
	{
		auto addr = AddressDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(addr, one,
			id, Id,
			userId, UserId,
			contact, Contact,
			phone, Phone,
			province, Province,
			city, City,
			country, Country,
			address, Address,
			remark, Remark);
		dto->addresses->push_back(addr);
	}

	// 返回数据
	return dto;
}
