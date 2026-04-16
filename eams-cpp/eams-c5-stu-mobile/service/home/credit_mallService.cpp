/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/19 10:10:00

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
#include "credit_mallService.h"
#include "../../dao/home/CreditMallDAO.h" // 积分商城DAO层（需自行创建）
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

// 分页查询积分商城礼品数据（支持多条件筛选）
credit_mallPageDTO::Wrapper CreditMallService::listAll(const CreditMallQuery::Wrapper& query)
{
	// 构建分页返回对象
	auto pages = credit_mallPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询符合条件的数据总条数
	CreditMallDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages; // 无数据时返回空分页对象
	}

	// 分页查询具体数据
	pages->total = count;
	pages->calcPages(); // 计算总页数
	list<CreditMallDO> result = dao.selectWithPage(query);

	// 将DO对象转换为DTO对象（填充分页列表）
	for (CreditMallDO& sub : result)
	{
		auto dto = credit_mallDTO::createShared();
		// 映射DO到DTO（字段严格对应credit_mall表结构）
		ZO_STAR_DOMAIN_DO_TO_DTO(
			dto, sub,
			id, Id,
			school_id, SchoolId,
			material_id, MaterialId,
			category_id, CategoryId,
			category_name, CategoryName,
			name, Name,
			credit, Credit,
			state, State,
			sale_num, SaleNum,
			view_num, ViewNum,
			cover, Cover,
			content, Content,
			creator, Creator,
			editor, Editor,
			add_time, AddTime,
			edit_time, EditTime,
			deleted, Deleted,
			org_id, OrgId
		);
		pages->addData(dto);
	}
	return pages;
}

// 通过ID查询单个积分商城礼品数据
credit_mallDTO::Wrapper CreditMallService::getById(std::string id)
{
	// 查询DO数据
	CreditMallDAO dao;
	auto res = dao.selectById(id);

	// 未查询到数据返回空
	if (!res)
		return nullptr;

	// 转换DO到DTO
	auto dto = credit_mallDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(
		dto, res,
		id, Id,
		school_id, SchoolId,
		material_id, MaterialId,
		category_id, CategoryId,
		category_name, CategoryName,
		name, Name,
		credit, Credit,
		state, State,
		sale_num, SaleNum,
		view_num, ViewNum,
		cover, Cover,
		content, Content,
		creator, Creator,
		editor, Editor,
		add_time, AddTime,
		edit_time, EditTime,
		deleted, Deleted,
		org_id, OrgId
	);
	return dto;
}

// 新增单条积分商城礼品数据
std::string CreditMallService::saveData(const credit_mallAddDTO::Wrapper& dto)
{
	// 组装DO数据（从AddDTO映射）
	CreditMallDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(
		data, dto,
		SchoolId, school_id,
		MaterialId, material_id,
		CategoryId, category_id,
		CategoryName, category_name,
		Name, name,
		Credit, credit,
		State, state,
		Cover, cover,
		Content, content,
		OrgId, org_id
	);

	// 生成唯一ID
	UuidFacade uf;
	data.setId(uf.genUuid());

	// 设置创建人（从Payload中获取）
	data.setCreator(dto->getPayload()->getUsername());
	// 设置创建时间
	data.setAddTime(SimpleDateTimeFormat::format());
	// 默认未删除
	data.setDeleted(0);
	// 初始兑换/预览数为0
	data.setSaleNum(0);
	data.setViewNum(0);

	// 执行新增操作
	CreditMallDAO dao;
	return dao.insert(data) == 1 ? data.getId() : "";
}

// 批量新增积分商城礼品数据
bool CreditMallService::saveDataBatch(const oatpp::List<credit_mallAddDTO::Wrapper>& datas)
{
	UuidFacade uf(1); // 批量生成UUID
	std::string ct = SimpleDateTimeFormat::format(); // 统一创建时间
	std::list<CreditMallDO> dos;

	for (auto dto : *datas.get())
	{
		// 组装DO数据
		CreditMallDO& data = dos.emplace_back();
		ZO_STAR_DOMAIN_DTO_TO_DO(
			data, dto,
			SchoolId, school_id,
			MaterialId, material_id,
			CategoryId, category_id,
			CategoryName, category_name,
			Name, name,
			Credit, credit,
			State, state,
			Cover, cover,
			Content, content,
			OrgId, org_id
		);

		// 生成UUID
		data.setId(uf.genUuid());
		// 设置创建人
		data.setCreator(dto->getPayload()->getUsername());
		// 设置创建时间
		data.setAddTime(ct);
		// 默认未删除
		data.setDeleted(0);
		// 初始兑换/预览数为0
		data.setSaleNum(0);
		data.setViewNum(0);
	}

	// 执行批量新增
	return CreditMallDAO().insertBatch(dos) != 0;
}

// 修改积分商城礼品数据
bool CreditMallService::updateData(const credit_mallDTO::Wrapper& dto)
{
	// 组装DO数据（从DTO映射）
	CreditMallDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(
		data, dto,
		Id, id,
		SchoolId, school_id,
		MaterialId, material_id,
		CategoryId, category_id,
		CategoryName, category_name,
		Name, name,
		Credit, credit,
		State, state,
		Cover, cover,
		Content, content,
		SaleNum, sale_num,
		ViewNum, view_num,
		OrgId, org_id
	);

	// 设置修改人
	data.setEditor(dto->getPayload()->getUsername());
	// 设置修改时间
	data.setEditTime(SimpleDateTimeFormat::format());

	// 执行修改操作
	CreditMallDAO dao;
	return dao.update(data) == 1;
}

// 批量删除积分商城礼品数据（逻辑删除，更新deleted字段为1）
bool CreditMallService::removeData(const oatpp::List<oatpp::String>& ids)
{
	CreditMallDAO dao;
	std::list<std::string> datas;

	// 转换ID列表格式
	for (auto one : *ids.get())
		datas.emplace_back(one.getValue({}));

	// 执行批量逻辑删除（更新deleted=1）
	int rows = dao.updateDeletedByIds(datas, 1);

	// 验证删除行数是否匹配
	if (rows == ids->size())
		return true;
	return false;
}