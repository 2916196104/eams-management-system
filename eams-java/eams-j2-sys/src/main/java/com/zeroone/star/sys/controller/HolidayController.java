package com.zeroone.star.sys.controller;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Holiday.HolidayDTO;
import com.zeroone.star.project.j2.sys.HolidayApis;
import com.zeroone.star.project.query.j2.sys.holiday.HolidayQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sys.entity.Holiday;
import com.zeroone.star.sys.service.IHolidayService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.time.LocalDateTime;

/**
 * <p>
 * 节假日设置 前端控制器
 * </p>
 *
 * @author Wind
 * @since 2026-03-23
 */
@RestController
@Api(tags = "节假日管理")
@RequestMapping("/sys/holiday")
public class HolidayController implements HolidayApis {

    @Autowired
    private IHolidayService holidayService;

    /**
     * 节日条件、分页查询
     * @param query 查询条件
     * @return 查询结果
     */
    @GetMapping("/page")
    @ApiOperation("获取节日列表 (条件 + 分页)")
    @Override
    public JsonVO<PageDTO<HolidayDTO>> pageQueryHoliday(HolidayQuery query) {
        // 构建分页对象
        Page<Holiday> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 构建查询条件
        QueryWrapper<Holiday> queryWrapper = new QueryWrapper<>();

        // 添加节日日期列表条件（IN 查询）
        if (query.getHolidayList() != null && !query.getHolidayList().isEmpty()) {
            queryWrapper.in("date", query.getHolidayList());
        }

        // 按时间倒序排列
        queryWrapper.orderByDesc("id");

        // 执行分页查询（使用 Service 层的 page 方法）
        Page<Holiday> resultPage = holidayService.page(page, queryWrapper);

        // 转换为 PageDTO 并返回
        PageDTO<HolidayDTO> pageDTO = PageDTO.create(resultPage, HolidayDTO.class);
        return JsonVO.success(pageDTO);
    }

    /**
     * 节日新增
     * @param holidayDto 新增数据
     * @return 新增结果
     */
    @PostMapping("/add")
    @ApiOperation("添加节日")
    @Override
    public JsonVO<String> addHoliday(@RequestBody @Valid HolidayDTO holidayDto) {
        // 参数校验
        if (holidayDto == null || holidayDto.getHolidayTime() == null) {
            return JsonVO.fail("节日时间不能为空");
        }

        // 创建 Holiday 实体对象
        Holiday holiday = new Holiday();
        holiday.setDate(holidayDto.getHolidayTime());
        holiday.setAddTime(LocalDateTime.now());
        // TODO: 后续可从登录上下文获取创建人 ID
        // holiday.setCreator(currentUserId);

        // 保存到数据库（使用 Service 层的 save 方法）
        boolean success = holidayService.save(holiday);

        if (success) {
            return JsonVO.success("添加成功，节日 ID: " + holiday.getId());
        } else {
            return JsonVO.fail("添加失败");
        }
    }

    /**
     * 节日删除
     * @param id 要删除数据的编号
     * @return 删除结果
     */
    @DeleteMapping("/remove/{id}")
    @ApiOperation("删除节日")
    @Override
    public JsonVO<String> removeHoliday(@PathVariable Long id) {
        // 参数校验
        if (id == null) {
            return JsonVO.fail("节日 ID 不能为空");
        }

        // 检查节日是否存在（使用 Service 层的 getById 方法）
        Holiday holiday = holidayService.getById(id);
        if (holiday == null) {
            return JsonVO.fail("节日不存在，ID: " + id);
        }

        // 执行删除（使用 Service 层的 removeById 方法）
        boolean success = holidayService.removeById(id);

        if (success) {
            return JsonVO.success("删除成功");
        } else {
            return JsonVO.fail("删除失败");
        }
    }
}
