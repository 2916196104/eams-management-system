package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.interact.entity.Advertisement;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.query.j6.interact.AdvertisementListQuery;

/**
 * 广告/通知管理 Service 接口
 */
public interface IAdvertisementService extends IService<Advertisement> {

    /**
     * 分页查询广告列表
     *
     * @param query 查询条件（标题、类型、状态 + 分页参数）
     * @return 分页数据
     */
    PageDTO<AdvertisementDTO> queryPage(AdvertisementListQuery query);

    /**
     * 获取广告详情
     *
     * @param id 广告主键ID
     * @return 广告详情DTO，不存在时返回 null
     */
    AdvertisementDTO getDetail(Long id);
}
