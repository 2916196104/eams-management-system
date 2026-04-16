package com.zeroone.star.project.j6.interact;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AnnouncementDTO;
import com.zeroone.star.project.query.j6.interact.AnnouncementListQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 公告相关接口
 */
public interface AnnouncementApis {

    /**
     * 获取公告列表（条件+分页）
     * @param query 查询条件
     * @return 分页公告数据
     */
    JsonVO<PageDTO<AnnouncementDTO>> queryPage(AnnouncementListQuery query);


    /**
     * 获取公告详情
     * @param id 公告ID
     * @return 公告详情
     */
    JsonVO<AnnouncementDTO> getDetail(Long id);

    /**
     * 保存公告（新增或修改）
     * @param dto 公告信息
     * @return 操作结果
     */
    JsonVO<String> saveAnnouncement(AnnouncementDTO dto);

    /**
     * 删除公告
     * @param ids 公告id列表
     * @return 操作结果
     */
    JsonVO<String> removeAnnouncement(List<Long> ids);

    /**
     * 启用、停用公告
     * @param ids 公告id列表
     * @param state 状态(0-停用,1-启用)
     * @return 操作结果
     */
    JsonVO<String> updateAnnouncementState(List<Long> ids, Integer state);
}
