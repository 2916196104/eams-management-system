package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.interact.entity.Advertisement;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AnnouncementDTO;
import com.zeroone.star.project.query.j6.interact.AnnouncementListQuery;

import java.util.List;

/**
 * 公告管理服务接口
 *
 * @author maban
 * @since 2026-03-28
 */
public interface AnnouncementService extends IService<Advertisement> {

    /**
     * 分页查询公告列表
     *
     * @param query 查询条件
     * @return 分页数据
     */
    PageDTO<AnnouncementDTO> queryPage(AnnouncementListQuery query);

    /**
     * 根据ID获取公告详情
     *
     * @param id 公告ID
     * @return 公告详情
     */
    AnnouncementDTO getDetail(Long id);

    /**
     * 保存公告（新增或修改）
     *
     * @param dto 公告信息
     * @return 公告ID
     */
    Long saveAnnouncement(AnnouncementDTO dto);

    /**
     * 批量删除公告
     *
     * @param ids 公告ID列表
     * @return 删除的ID列表
     */
    List<Long> removeAnnouncement(List<Long> ids);

    /**
     * 批量更新公告状态
     *
     * @param ids   公告ID列表
     * @param state 状态(0-停用,1-启用)
     * @return 更新的ID列表
     */
    List<Long> updateAnnouncementState(List<Long> ids, Integer state);

    /**
     * 获取类型名称
     *
     * @param type 类型编码
     * @return 类型名称
     */
    String getTypeName(Integer type);
}
