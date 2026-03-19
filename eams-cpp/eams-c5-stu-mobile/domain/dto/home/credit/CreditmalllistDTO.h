#pragma once

#ifndef _CREDITMALLLIST_DTO_
#define _CREDITMALLLIST_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 核心DTO：适配credit_mall表字段
class CreditMallDTO : public oatpp::DTO
{
    DTO_INIT(CreditMallDTO, DTO);

    // ========== credit_mall表字段 ==========
    // 1. 主键ID
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.id");
    }

    // 2. 所属学校
    DTO_FIELD(Int64, school_id);
    DTO_FIELD_INFO(school_id) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.school_id");
    }

    // 3. 物料分类
    DTO_FIELD(Int64, material_id);
    DTO_FIELD_INFO(material_id) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.material_id");
    }

    // 4. 礼品分类ID
    DTO_FIELD(Int64, category_id);
    DTO_FIELD_INFO(category_id) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.category_id");
    }

    // 5. 分类名称
    DTO_FIELD(String, category_name);
    DTO_FIELD_INFO(category_name) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.category_name");
    }

    // 6. 礼品名称
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.name");
    }

    // 7. 兑换积分
    DTO_FIELD(Int32, credit);
    DTO_FIELD_INFO(credit) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.credit");
    }

    // 8. 是否可以兑换
    DTO_FIELD(Boolean, state);
    DTO_FIELD_INFO(state) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.state");
    }

    // 9. 历史兑换数量
    DTO_FIELD(Int32, sale_num);
    DTO_FIELD_INFO(sale_num) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.sale_num");
    }

    // 10. 预览次数
    DTO_FIELD(Int32, view_num);
    DTO_FIELD_INFO(view_num) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.view_num");
    }

    // 11. 封面
    DTO_FIELD(String, cover);
    DTO_FIELD_INFO(cover) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.cover");
    }

    // 12. 详情内容
    DTO_FIELD(String, content);
    DTO_FIELD_INFO(content) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.content");
    }

    // 13. 创建人
    DTO_FIELD(Int64, creator);
    DTO_FIELD_INFO(creator) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.creator");
    }

    // 14. 编辑人
    DTO_FIELD(Int64, editor);
    DTO_FIELD_INFO(editor) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.editor");
    }

    // 15. 添加时间
    DTO_FIELD(String, add_time);
    DTO_FIELD_INFO(add_time) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.add_time");
    }

    // 16. 编辑时间
    DTO_FIELD(String, edit_time);
    DTO_FIELD_INFO(edit_time) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.edit_time");
    }

    // 17. 删除标记
    DTO_FIELD(Boolean, deleted);
    DTO_FIELD_INFO(deleted) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.deleted");
    }

    // 18. 创建者所属组织ID
    DTO_FIELD(Int64, org_id);
    DTO_FIELD_INFO(org_id) {
        info->description = ZH_WORDS_GETTER("c5.home.credit.mall.field.org_id");
    }

    // 保留原有Payload字段（若业务需要）
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

// 分页DTO：适配CreditMallDTO
class CreditMallPageDTO : public PageDTO<CreditMallDTO::Wrapper>
{
    DTO_INIT(CreditMallPageDTO, PageDTO<CreditMallDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CREDITMALLLIST_DTO_