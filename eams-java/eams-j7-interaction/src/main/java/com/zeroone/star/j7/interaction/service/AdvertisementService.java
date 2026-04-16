package com.zeroone.star.j7.interaction.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.AdvertisementDTO;
import com.zeroone.star.project.entity.Advertisement;
import com.zeroone.star.project.query.j7.interaction.AdvertisementQuery;

import java.util.List;

/**
 * <p>
 * 公告管理服务类
 * </p>
 *
 * @author 薛定猫
 * @since 2026/3/16
 */
public interface AdvertisementService {

    /**
     * 获取公告列表（条件+分页）
     * @param advertisementQuery 查询条件
     * @return 公告列表
     */
    PageDTO<Advertisement> queryPage(AdvertisementQuery advertisementQuery);

    /**
     * 获取公告详情
     * @param id 公告id
     * @return 详情页
     */
    Advertisement getAdvertisementDetail(Long id);

    /**
     * 保存公告
     * @param advertisementDTO 公告信息
     * @return 保存结果
     */
    Long saveAdvertisement(AdvertisementDTO advertisementDTO);
    // 删除
    boolean removeNotice(List<Long> ids);

    // 启用/停用公告
    boolean modifyNotice(Long id, Integer status);

}
