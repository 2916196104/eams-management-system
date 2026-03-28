package com.zeroone.star.interact.controller;

import com.zeroone.star.interact.service.IAdvertisementService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.j6.interact.AdvertisementApis;
import com.zeroone.star.project.query.j6.interact.AdvertisementListQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

/**
 * 广告/通知管理接口实现
 */
@RestController
@RequestMapping("/j6/interact/advertisement")
@Api(tags = "广告/通知管理")
public class AdvertisementController implements AdvertisementApis {

    @Resource
    private IAdvertisementService advertisementService;

    /**
     * 获取广告列表（条件+分页）
     */
    @GetMapping("/list")
    @ApiOperation("获取广告列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AdvertisementDTO>> queryPage(AdvertisementListQuery query) {
        PageDTO<AdvertisementDTO> pageResult = advertisementService.queryPage(query);
        return JsonVO.success(pageResult);
    }

    /**
     * 获取广告详情
     */
    @GetMapping("/detail/{id}")
    @ApiOperation("获取广告详情")
    @ApiImplicitParam(name = "id", value = "广告主键ID", required = true, dataType = "Long", paramType = "path", example = "1")
    @Override
    public JsonVO<AdvertisementDTO> getDetail(@PathVariable("id") Long id) {
        AdvertisementDTO dto = advertisementService.getDetail(id);
        if (dto == null) {
            return JsonVO.fail("广告不存在");
        }
        return JsonVO.success(dto);
    }
}
