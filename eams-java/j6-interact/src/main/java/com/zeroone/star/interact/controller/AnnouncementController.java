package com.zeroone.star.interact.controller;

import com.zeroone.star.interact.service.AnnouncementService;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AnnouncementDTO;
import com.zeroone.star.project.j6.interact.AnnouncementApis;
import com.zeroone.star.project.query.j6.interact.AnnouncementListQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;


/**
 * 公告管理接口实现类
 *
 * @author maban
 * @since 2026-03-28
 */
@RestController
@RequestMapping("/j6-interact/announcement")
@Api(tags = "公告管理")
public class AnnouncementController implements AnnouncementApis {

    @Autowired
    private AnnouncementService announcementService;

    @Autowired
    private FastDfsClientComponent fastDfsClient;

    @Value("${fastdfs.nginx-host:http://47.103.79.46:8888}")
    private String fastDfsNginxHost;

    @GetMapping("/list")
    @ApiOperation("获取公告列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<AnnouncementDTO>> queryPage(@Validated AnnouncementListQuery query) {
        PageDTO<AnnouncementDTO> pageResult = announcementService.queryPage(query);
        return JsonVO.success(pageResult);
    }


    @GetMapping("/detail/{id}")
    @ApiOperation("获取公告详情")
    @Override
    public JsonVO<AnnouncementDTO> getDetail(@PathVariable("id") Long id) {
        AnnouncementDTO detail = announcementService.getDetail(id);
        if (detail == null) {
            return JsonVO.fail("公告不存在");
        }
        return JsonVO.success(detail);
    }

    /**
     * 保存公告
     *
     * @param dto 公告信息
     * @return 操作结果
     */
    @PostMapping("/save")
    @ApiOperation("保存公告")
    @Override
    public JsonVO<String> saveAnnouncement(@RequestBody AnnouncementDTO dto) {
        Long id = announcementService.saveAnnouncement(dto);
        if (id != null) {
            return JsonVO.success("保存成功");
        }
        return JsonVO.fail("保存失败");
    }

    /**
     * 上传公告图片
     *
     * @param file 图片文件
     * @return 图片URL
     */
    @PostMapping("/upload")
    @ApiOperation("上传公告图片")
    public JsonVO<String> uploadImage(@ApiParam(value = "图片文件", required = true) @RequestParam("file") MultipartFile file) {
        if (file == null || file.isEmpty()) {
            return JsonVO.fail("请选择要上传的文件");
        }
        try {
            // 获取文件扩展名
            String originalFilename = file.getOriginalFilename();
            String extName = "";
            if (originalFilename != null && originalFilename.contains(".")) {
                extName = originalFilename.substring(originalFilename.lastIndexOf(".") + 1);
            }
            // 上传到FastDFS
            FastDfsFileInfo fileInfo = fastDfsClient.uploadFile(file.getBytes(), extName);
            if (fileInfo != null) {
                // 生成访问URL（使用Token防盗链）
                String url = fastDfsClient.fetchUrl(fileInfo, fastDfsNginxHost, true);
                return JsonVO.success(url);
            }
            return JsonVO.fail("文件上传失败");
        } catch (Exception e) {
            return JsonVO.fail("文件上传异常：" + e.getMessage());
        }
    }

    /**
     * 删除公告
     *
     * @param ids 公告id列表
     * @return 操作结果
     */
    @DeleteMapping("/remove")
    @ApiOperation("删除公告")
    @Override
    public JsonVO<String> removeAnnouncement(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的公告");
        }
        List<Long> removedIds = announcementService.removeAnnouncement(ids);
        return JsonVO.success("删除成功，共删除" + removedIds.size() + "条记录");
    }

    /**
     * 启用、停用公告
     *
     * @param ids   公告id列表
     * @param state 状态(0-停用,1-启用)
     * @return 操作结果
     */
    @PutMapping("/state")
    @ApiOperation("启用/停用公告")
    @Override
    public JsonVO<String> updateAnnouncementState(
            @ApiParam(value = "公告ID列表", required = true) @RequestBody List<Long> ids,
            @ApiParam(value = "状态(0-停用,1-启用)", required = true) @RequestParam("state") Integer state) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要操作的公告");
        }
        if (state == null || (state != 0 && state != 1)) {
            return JsonVO.fail("状态参数无效");
        }
        List<Long> updatedIds = announcementService.updateAnnouncementState(ids, state);
        String stateText = state == 1 ? "启用" : "停用";
        return JsonVO.success(stateText + "成功，共更新" + updatedIds.size() + "条记录");
    }
}
