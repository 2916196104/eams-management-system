/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/11/28 10:47:49

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
#include "ServerInfo.h"
#include "YamlHelper.h"
#include "ApiHelper.h"
#include "PdfComponent.h"
#include "domain/bo/PdfReportBO.h"

void ServerInfo::init()
{
	this->dbPort = 3306;
	this->dbMax = 25;
	// 加载中文词典
	zhDictNode = YAML::LoadFile("zh-dict.yaml");
	// 注册一个简单pdf报表绘制模板
	PdfComponent::registerTplRender("simple-pdf-report", [](YAML::Node* node, PdfComponent* pdf, void* realData)
		{
			// 配置数据
			int maxrow = (*node)["maxrow"].as<int>();
			HPDF_REAL top = (*node)["top"].as<HPDF_REAL>();
			HPDF_REAL left = (*node)["left"].as<HPDF_REAL>();
			HPDF_REAL rowheight = (*node)["rowheight"].as<HPDF_REAL>();
			HPDF_REAL colwidth = (*node)["colwidth"].as<HPDF_REAL>();
			HPDF_REAL titlefontsize = (*node)["titlefontsize"].as<HPDF_REAL>();
			HPDF_REAL contentfontsize = (*node)["contentfontsize"].as<HPDF_REAL>();
			std::vector<FieldConfig> fieldConfigs;
			for (const auto& fieldNode : (*node)["fields"]) {
				for (const auto& entry : fieldNode) {
					YAML::Node value = entry.second;
					FieldConfig field;
					field.title = value["title"].as<std::string>();
					field.prop = value["prop"].as<std::string>();
					field.colwidth = value["colwidth"] ? value["colwidth"].as<HPDF_REAL>() : colwidth;
					fieldConfigs.push_back(field);
				}
			}
			// 动态计算数据
			int currow = 0;
			HPDF_REAL x = 0;
			HPDF_REAL y = 0;
			HPDF_Page page;
			auto datas = static_cast<IDataAccessor*>(realData);
			while (datas->hasNext())
			{
				if (currow == 0)
				{
					// 创建PDF页面
					page = pdf->getNewPage();
					pdf->setCurrPageFontSize(titlefontsize);
					// 绘制表头
					x = left;
					y = pdf->getCurrPageHeight() - top - rowheight;
					for (auto field : fieldConfigs)
					{
						pdf->drawText(field.title, x, y, page);
						x += field.colwidth;
					}
					// 设置字体大小
					pdf->setCurrPageFontSize(contentfontsize);
				}
				// 绘制一行
				x = left;
				y -= rowheight;
				for (auto field : fieldConfigs)
				{
					pdf->drawText(datas->getField(field.prop), x, y, page);
					x += field.colwidth;
				}
				// 更新绘制行数
				currow++;
				// 移动到下一行数据
				datas->moveNext();
				// 重置绘制行数
				if (currow >= maxrow) currow = 0;
			}
		});
}
