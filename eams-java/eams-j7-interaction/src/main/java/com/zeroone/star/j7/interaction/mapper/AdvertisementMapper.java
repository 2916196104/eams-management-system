package com.zeroone.star.j7.interaction.mapper;

import com.zeroone.star.project.dto.j7.interaction.AdvertisementDTO;
import com.zeroone.star.project.entity.Advertisement;
import com.zeroone.star.project.query.j7.interaction.AdvertisementQuery;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 公告管理Mapper
 * </p>
 *
 * @author 薛定猫
 * @since 2026/3/16
 */
@Mapper
public interface AdvertisementMapper {

    /**
     * 获取公告列表
     * @param advertisementQuery 查询条件
     * @return 公告列表
     */
    List<Advertisement> queryPage(AdvertisementQuery advertisementQuery);

    /**
     * 获取公告详情
     * @param id 公告id
     * @return 公告详情
     */
    Advertisement queryAdvertisementDetail(Long id);

    /**
     * 插入公告
     * @param advertisementDTO 公告信息
     * @return 保存结果
     */
    Long insertAdvertisement(AdvertisementDTO advertisementDTO);

    /**
     * 修改公告
     * @param advertisementDTO 公告信息
     * @return 修改结果
     */
    Long updateAdvertisement(AdvertisementDTO advertisementDTO);

    /**
     * 查询单条公告
     * @param advertisementDTO 公告信息
     * @return 公告信息
     */
    Advertisement findAdvertisement(AdvertisementDTO advertisementDTO);

    /**
     * 根据code查询单条公告
     * @param code
     * @return
     */
    Advertisement findAdvertisementByCode(String code);
}
