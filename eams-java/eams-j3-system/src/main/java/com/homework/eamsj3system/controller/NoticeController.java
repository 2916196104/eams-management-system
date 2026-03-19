package com.homework.eamsj3system.controller;

import com.homework.eamsj3system.dto.NoticeDTO;
import com.homework.eamsj3system.query.NoticeQuery;
import com.homework.eamsj3system.service.INoticeService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * <p>
 * 内部公告 控制器（框架）
 * </p>
 * @author 阿伟
 */
@RestController
@RequestMapping("/notice")
@Tag(name = "内部公告管理", description = "内部公告相关接口")
public class NoticeController {

    @Autowired
    private INoticeService noticeService;

    /**
     * 1. 获取内部公告列表（条件 + 分页）
     * @param query 查询条件
     * @return 返回分页数据
     */
    @GetMapping("/page-list")
    @Operation(summary = "分页查询公告列表", description = "支持条件查询和分页")
    public Object pageList(NoticeQuery query) {
        // TODO: 待实现
        return null;
    }

    /**
     * 2. 获取内部公告详情
     * @param id 公告 ID
     * @return 返回公告详情
     */
    @GetMapping("/get-by-id/{id}")
    @Operation(summary = "获取公告详情", description = "根据 ID 获取公告详细信息")
    public Object getById(@PathVariable Long id) {
        // TODO: 待实现
        return null;
    }

    /**
     * 3. 保存内部公告（新增或修改）
     * @param noticeDTO 公告数据传输对象
     * @return 操作结果
     */
    @PostMapping("/save")
    @Operation(summary = "保存公告", description = "新增或修改公告信息")
    public Object save(@RequestBody NoticeDTO noticeDTO) {
        // TODO: 待实现
        return null;
    }

    /**
     * 4. 删除内部公告（支持批量删除）
     * @param ids 公告 ID 列表，逗号分隔
     * @return 操作结果
     */
    @DeleteMapping("/delete")
    @Operation(summary = "删除公告", description = "支持单个或批量删除")
    public Object delete(@RequestParam("ids") List<Long> ids) {
        // TODO: 待实现
        return null;
    }
}
