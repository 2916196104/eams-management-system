#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:24:25

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
#ifndef _JSON_VO_
#define _JSON_VO_
#include "NoDataJsonVO.h"
#include "Message.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * ǰ������ݶԽ����ݶ���
 */
template<class T>
class JsonVO : public NoDataJsonVO
{
	// ��ʼ������
	DTO_INIT(JsonVO, NoDataJsonVO);

	// ���ݶ���
	DTO_FIELD(T, data, "data");
	DTO_FIELD_INFO(data) {
#ifndef LINUX
		info->description = u8"���ݶ���";
#else
		info->description = "data object";
#endif
	}

public:
	// ����״̬
	void setStatus(ResultStatus resultStatus) {
		this->message = resultStatus.getMessage();
		this->code = resultStatus.getCode();
	}
	// ��ʼ��
	void init(T data, ResultStatus resultStatus) {
		this->data = data;
		this->setStatus(resultStatus);
	}
	// �����ɹ���Ϣ
	void success(T data) {
		this->setStatus(RS_SUCCESS);
		this->data = data;
	}
	// ����ʧ����Ϣ 
	void fail(T data) {
		this->setStatus(RS_FAIL);
		this->data = data;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_JSON_VO_
