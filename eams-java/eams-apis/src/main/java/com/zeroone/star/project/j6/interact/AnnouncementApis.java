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
     * @param announcementListQuery
     * @return
     */
    JsonVO<PageDTO<AnnouncementDTO>> queryPage(AnnouncementListQuery announcementListQuery);


    /**
     * 获取公告详情
     * @param id
     * @return
     */
    JsonVO<AnnouncementDTO> getDetail(Long id);

    /**
     *  保存公告
     * @param dto
     * @return
     */
    JsonVO<String> saveAnnouncement(AnnouncementDTO dto);

    /**
     * 删除公告
     * @param ids 公告id列表
     * @return
     */
    JsonVO<String> removeAnnouncement(List<Long> ids);

    /**
     * 启用、停用公告
     * @param ids 公告id列表
     * @return
     */
    JsonVO<String> updateAnnouncementState(List<Long> ids);
}
