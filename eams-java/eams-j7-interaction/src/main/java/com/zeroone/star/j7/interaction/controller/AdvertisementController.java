package com.zeroone.star.j7.interaction.controller;

import com.zeroone.star.j7.interaction.service.AdvertisementService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.AdvertisementDTO;
import com.zeroone.star.project.entity.Advertisement;
import com.zeroone.star.project.j7.interaction.AdvertisementApis;
import com.zeroone.star.project.query.j7.interaction.AdvertisementQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/*
 * 公告管理接口实现
 * @author:薛定猫
 * @date:2026/3/16
 * */
@Slf4j
@RestController
@RequestMapping("/j7-interaction/j7-notice")
@Api(tags = "公告管理")
public class AdvertisementController implements AdvertisementApis {

    @Resource
    AdvertisementService advertisementService;

    @GetMapping("/query/list/select")
    @ApiOperation("获取公告列表（条件 + 分页）")
    @Override
    public JsonVO<PageDTO<Advertisement>> queryPage(AdvertisementQuery advertisementQuery) {
        PageDTO<Advertisement> res = advertisementService.queryPage(advertisementQuery);
        if(res == null){
            return JsonVO.fail("查询失败");
        }
        return JsonVO.success(res);
    }

    @GetMapping("/query/get/select")
    @ApiOperation("获取公告详情")
    @Override
    public JsonVO<Advertisement> getAdvertisementDetail(Long id) {
        Advertisement data = advertisementService.getAdvertisementDetail(id);
        if(data == null){
            return JsonVO.fail("查询失败");
        }
        Advertisement advertisement = new Advertisement();
        advertisement.setTitle(data.getTitle());
        advertisement.setContent(data.getContent());
        advertisement.setType(data.getType());
        return JsonVO.success(advertisement);
    }

    @PostMapping("/add/save/insert")
    @ApiOperation("保存公告")
    @Override
    public JsonVO<Long> saveAdvertisement(@RequestBody AdvertisementDTO advertisementDTO) {
        Long res = advertisementService.saveAdvertisement(advertisementDTO);
        if(res == null){
            return JsonVO.fail("保存失败");
        }
        return JsonVO.success(res);
    }
    /**
     * 删除公告
     *
     * @param ids 公告编号
     * @return 删除结果
     */
    @ApiOperation("删除公告")
    @DeleteMapping("/removeNotice")
    public JsonVO<String> removeNotice(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的公告");
        }
        boolean result = advertisementService.removeNotice(ids);
        if (!result){
            return JsonVO.fail("删除失败");
        }
        return JsonVO.success("删除成功");
    }

    /**
     * 启用/停用公告
     * @param id     公告编号
     * @param status 启用/停用S
     * @return 启用/停用结果
     */
    @ApiOperation("启用/停用公告")
    @PutMapping("/modifyNotice")
    public JsonVO<String> modifyNotice(
            @ApiParam(value = "公告ID", required = true)
            @RequestParam Long id,
            @ApiParam(value = "状态：0=启用，1=停用", required = true)
            @RequestParam Integer status) {

        if (id == null || id <= 0 ) {
            return JsonVO.fail("参数不能为空");
        }

        if (status != 0 && status != 1) {
            return JsonVO.fail("状态只能是 0 或 1");
        }

        log.info("启用/停用公告 id={}, status={}", id, status);
        boolean result = advertisementService.modifyNotice(id, status);
        return result ? JsonVO.success("操作成功") : JsonVO.fail("操作失败");
    }
}
