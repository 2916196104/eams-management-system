package com.zeroone.star.sys.controller;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.OptlogDTO;
import com.zeroone.star.project.dto.j2.sys.OptlogOperatorDTO;
import com.zeroone.star.project.j2.sys.OptlogApis;
import com.zeroone.star.project.query.j2.sys.OptlogOperatorQuery;
import com.zeroone.star.project.query.j2.sys.OptlogQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.sys.entity.Staff;
import com.zeroone.star.sys.entity.SysLog;
import com.zeroone.star.sys.mapper.StaffMapper;
import com.zeroone.star.sys.service.SysLogService;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import io.swagger.annotations.Api;

import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.time.format.DateTimeFormatter;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * <p>
 * 系统用户日志 前端控制器
 * </p>
 *
 * @author isme
 * @since 2026-03-15
 */
@RestController
@RequestMapping("/sys/optlog")
@Api(tags = "操作日志")
public class OptlogController implements OptlogApis {

    @Resource
    private SysLogService sysLogService;

    @Resource
    private StaffMapper staffMapper;

    @GetMapping
    @ApiOperation("获取操作日志(条件+分页）")
    @Override
    public JsonVO<PageDTO<OptlogDTO>> queryOptlog(OptlogQuery query) {
        if (query == null) {
            query = new OptlogQuery();
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;

        // 查询
        Page<SysLog> page = new Page<>(pageIndex, pageSize);
        QueryWrapper<SysLog> wrapper = new QueryWrapper<>();
        wrapper.like(StringUtils.hasText(query.getType()), "type", query.getType());
        wrapper.like(StringUtils.hasText(query.getInfo()), "info", query.getInfo());
        wrapper.eq(query.getOperator() != null && query.getOperator() > 0, "operator", query.getOperator());
        wrapper.orderByDesc("add_time");
        wrapper.orderByDesc("id");

        // 转换 构造映射关系
        Page<SysLog> result = sysLogService.page(page, wrapper);
        List<SysLog> records = result.getRecords() != null ? result.getRecords() : Collections.emptyList();
        List<Long> operatorIds = records.stream()
                .map(SysLog::getOperator)
                .filter(id -> id != null && id > 0)
                .distinct()
                .collect(Collectors.toList());
        Map<Long, String> operatorNameMap = operatorIds.isEmpty()
                ? Collections.emptyMap()
                : staffMapper.selectBatchIds(operatorIds).stream()
                .filter(s -> s.getId() != null)
                .collect(Collectors.toMap(Staff::getId, Staff::getName, (a, b) -> a));
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        PageDTO<OptlogDTO> dtoPage = PageDTO.create(result, src -> {
            OptlogDTO dto = new OptlogDTO();
            if (src.getAddTime() != null) {
                dto.setAdd_time(src.getAddTime().format(formatter));
            }
            if (src.getOperator() != null) {
                String operatorName = operatorNameMap.get(src.getOperator());
                dto.setOperator(StringUtils.hasText(operatorName) ? operatorName : String.valueOf(src.getOperator()));
            }
            dto.setType(src.getType());
            dto.setInfo(src.getInfo());
            dto.setOrg_id(src.getPath());
            dto.setOs_name(src.getOsName());
            dto.setBrowser_ver(src.getIp());

            String browserName = src.getBrowserName();
            String browserVer = src.getBrowserVer();
            String browser = "";
            if (StringUtils.hasText(browserName) && StringUtils.hasText(browserVer)) {
                browser = browserName + " " + browserVer;
            } else if (StringUtils.hasText(browserName)) {
                browser = browserName;
            } else if (StringUtils.hasText(browserVer)) {
                browser = browserVer;
            }
            dto.setBroswer_name(browser);

            if (src.getTimeCost() != null) {
                dto.setTime_cost(String.valueOf(src.getTimeCost()));
            }
            return dto;
        });

        return JsonVO.success(dtoPage);
    }

    @GetMapping("/operators")
    @ApiOperation("获取操作人列表（姓名+职位，条件+分页）")
    @Override
    public JsonVO<PageDTO<OptlogOperatorDTO>> queryOptlogOperators(OptlogOperatorQuery query) {
        if (query == null) {
            query = new OptlogOperatorQuery();
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;

        Page<OptlogOperatorDTO> page = new Page<>(pageIndex, pageSize);
        Page<OptlogOperatorDTO> result = staffMapper.selectOptlogOperators(page, query.getName());
        return JsonVO.success(PageDTO.create(result));
    }
}

