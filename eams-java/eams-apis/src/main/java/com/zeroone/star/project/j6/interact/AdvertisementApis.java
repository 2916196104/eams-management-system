package com.zeroone.star.project.j6.interact;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 公告相关接口
 */
public interface AdvertisementApis {

    /**
     * 分页条件查询公告列表
     * @param condition 查询条件（包含分页参数、筛选条件等）
     * @return 分页结果（包装在统一响应体 JsonVO 中）
     */
    JsonVO<PageDTO<AdvertisementDTO>> queryPage(AdvertisementQuery condition);



    /**
     * 根据ID获取公告详情
     * @param id 公告ID
     * @return 公告详情（包装在统一响应体 JsonVO 中）
     */
    JsonVO<AdvertisementDTO> getDetail(Long id);
}
