package com.zeroone.star.interact.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AnnouncementDTO;
import com.zeroone.star.project.j6.interact.AnnouncementApis;
import com.zeroone.star.project.query.j6.interact.AnnouncementListQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;


/**
 * 公告管理接口实现类
 */
@RestController
@RequestMapping(("j6/interact/Advertisement"))
@Api(tags = "公告管理")
public class AnnouncementController implements AnnouncementApis {

    @GetMapping("/list")
    @ApiOperation("获取公告列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AnnouncementDTO>> queryPage(AnnouncementListQuery announcementListQuery) {
        return null;
    }


    @GetMapping("/detail/{id}")
    @ApiOperation("获取公告详情")
    @Override
    public JsonVO<AnnouncementDTO> getDetail(@PathVariable("id") Long id) {
        return null;
    }

    /**
     * 保存公告
     *
     * @param dto
     * @return
     */
    @PostMapping
    @ApiOperation("保存公告")
    @Override
    public JsonVO<String> saveAnnouncement(AnnouncementDTO dto) {
        return null;
    }

    /**
     * 删除公告
     *
     * @param ids 公告id列表
     * @return
     */
    @DeleteMapping
    @ApiOperation("删除公告")
    @Override
    public JsonVO<String> removeAnnouncement(List<Long> ids) {
        return null;
    }

    /**
     * 启用、停用公告
     *
     * @param ids 公告id列表
     * @return
     */
    @PutMapping
    @ApiOperation("启用，停用公告")
    @Override
    public JsonVO<String> updateAnnouncementState(List<Long> ids) {
        return null;
    }
}
