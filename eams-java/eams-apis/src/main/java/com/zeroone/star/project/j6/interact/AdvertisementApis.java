package com.zeroone.star.project.j6.interact;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.query.j6.interact.AdvertisementListQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 公告相关接口
 */
public interface AdvertisementApis {

    /**
     * 获取公告列表（条件+分页）
     * @param advertisementListQuery
     * @return
     */
    JsonVO<PageDTO<AdvertisementDTO>> queryPage(AdvertisementListQuery advertisementListQuery);


    /**
     * 获取公告详情
     * @param id
     * @return
     */
    JsonVO<AdvertisementDTO> getDetail(Long id);
}
