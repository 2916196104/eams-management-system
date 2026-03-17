#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:20:12

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
#ifndef _PAGE_DTO_
#define _PAGE_DTO_
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * ��ҳ����ʵ��
 */
template <class T>
class PageDTO : public oatpp::DTO
{
	// ��ʼ��
	DTO_INIT(PageDTO, DTO);

	/**
	 * ��ǰҳ��
	 */
	DTO_FIELD(UInt64, pageIndex) = 1;
	DTO_FIELD_INFO(pageIndex) {
		info->required = true;
#ifndef LINUX
		info->description = u8"��ǰҳ��";
#else
		info->description = "page index";
#endif
	}
	/**
	 * ÿҳ��ʾ�����������
	 */
	DTO_FIELD(UInt64, pageSize) = 5;
	DTO_FIELD_INFO(pageSize) {
		info->required = true;
#ifndef LINUX
		info->description = u8"ÿҳ��������";
#else
		info->description = "page size";
#endif
	}
	/**
	 * ���ݵ�������
	 */
	DTO_FIELD(Int64, total) = 9;
	DTO_FIELD_INFO(total) {
		info->required = true;
#ifndef LINUX
		info->description = u8"���ݵ�������";
#else
		info->description = "total";
#endif
	}
	/**
	 * ���ݵ���ҳ��
	 */
	DTO_FIELD(Int64, pages) = 2;
	DTO_FIELD_INFO(pages) {
		info->required = true;
#ifndef LINUX
		info->description = u8"���ݵ���ҳ��";
#else
		info->description = "pages";
#endif
	}
	/**
	 * ��ǰҳ�����б�
	 */
	DTO_FIELD(List<T>, rows) = {};
	DTO_FIELD_INFO(rows) {
#ifndef LINUX
		info->description = u8"��ǰҳ�����б�";
#else
		info->description = "page data list";
#endif
	}
public:
	PageDTO() {
		this->total = v_int64(0);
		this->pages = v_int64(0);
	}
	// ��ʼ����������
	void initAll(UInt64 pageIndex, UInt64 pageSize, Int64 total, Int64 pages, List<T> rows) {
		this->pageIndex = pageIndex;
		this->pageSize = pageSize;
		this->total = total;
		this->pages = pages;
		this->rows = rows;
	}
	// ������ҳ��
	void calcPages() {
		this->pages = total.getValue(0) / pageSize.getValue(1);
		this->pages = total.getValue(0) % pageSize.getValue(1) == 0 ? this->pages.getValue(0) : this->pages.getValue(0) + 1;
	}
	// ���һ������
	void addData(T one) {
		this->rows->push_back(one);
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PAGE_DTO_
