package com.zeroone.star.project.j6.interact;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 公告相关接口
 */
public interface AdvertisementApis {




    JsonVO<PageDTO<AdvertisementDTO>> queryPage(String title, String content , List<String> type);




    JsonVO<AdvertisementDTO> getDetail(String title,String content ,List<String> type,String imageUrl);
}
