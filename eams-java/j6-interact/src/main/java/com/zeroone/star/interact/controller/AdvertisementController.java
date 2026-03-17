package com.zeroone.star.interact.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementQuery;
import com.zeroone.star.project.j6.interact.AdvertisementApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


/**
 * 公告管理接口实现类
 */
@RestController
@RequestMapping(("j6/interact/Advertisement"))
@Api(tags = "公告接口")
public class AdvertisementController implements AdvertisementApis {

    @GetMapping("/list")
    @ApiOperation("获取公告列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AdvertisementDTO>> queryPage(AdvertisementQuery condition) {
        return null;
    }

    @GetMapping("/detail/{id}")
    @ApiOperation("获取公告详情")
    @Override
    public JsonVO<AdvertisementDTO> getDetail(Long id) {
        return null;
    }
}
