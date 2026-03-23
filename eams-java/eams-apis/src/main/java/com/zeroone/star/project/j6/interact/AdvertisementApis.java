package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.query.j6.interact.AdvertisementListQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 广告/通知管理相关接口定义
 */
public interface AdvertisementApis {

    /**
     * 获取广告列表（条件+分页）
     *
     * @param query 查询条件（标题、类型、状态 + 分页参数）
     * @return 分页数据
     */
    JsonVO<PageDTO<AdvertisementDTO>> queryPage(AdvertisementListQuery query);

    /**
     * 获取广告详情
     *
     * @param id 广告主键ID
     * @return 广告详情
     */
    JsonVO<AdvertisementDTO> getDetail(Long id);
}
