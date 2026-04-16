package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.AdvertisementDTO;
import com.zeroone.star.project.entity.Advertisement;
import com.zeroone.star.project.query.j7.interaction.AdvertisementQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;

/*
* 公告管理：公告查询列表、公告详情、保存公告
* @author: 薛定猫
* @date: 2026/3/17
* */
@Valid
public interface AdvertisementApis {

    /*
    * 公告列表查询（条件 + 分页）
    * @param: 查询条件
    * @return: 公告列表
    * */
    JsonVO<PageDTO<Advertisement>> queryPage(AdvertisementQuery advertisementQuery);


    /*
    * 公告详情页查询
    * @param: 公告id
    * @return: 详情页
    * */
    JsonVO<Advertisement> getAdvertisementDetail(Long id);


    /*
    * 保存公告
    * @param: 公告信息
    * @return: 保存结果
    * */
    JsonVO<Long> saveAdvertisement(@RequestBody @Valid AdvertisementDTO advertisementDTO);
}