package com.zeroone.star.sys.service.impl.optlog;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogOperatorQuery;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogQuery;
import com.zeroone.star.sys.entity.Staff;
import com.zeroone.star.sys.entity.SysLog;
import com.zeroone.star.sys.mapper.StaffMapper;
import com.zeroone.star.sys.service.SysLogService;
import com.zeroone.star.sys.service.optlog.OptlogService;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import javax.annotation.Resource;
import java.time.format.DateTimeFormatter;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class OptlogServiceImpl implements OptlogService {
    @Resource
    private SysLogService sysLogService;
    @Resource
    private StaffMapper staffMapper;

    @Override
    public PageDTO<OptlogDTO> queryOptlog(OptlogQuery query) {
        if (query == null) {
            query = new OptlogQuery();
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;

        Page<SysLog> page = new Page<>(pageIndex, pageSize);
        QueryWrapper<SysLog> wrapper = new QueryWrapper<>();
        wrapper.like(StringUtils.hasText(query.getType()), "type", query.getType());
        wrapper.like(StringUtils.hasText(query.getInfo()), "info", query.getInfo());
        wrapper.eq(query.getOperator() != null && query.getOperator() > 0, "operator", query.getOperator());
        wrapper.orderByDesc("add_time").orderByDesc("id");

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

        return PageDTO.create(result, src -> {
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
    }

    @Override
    public PageDTO<OptlogOperatorDTO> queryOptlogOperators(OptlogOperatorQuery query) {
        if (query == null) {
            query = new OptlogOperatorQuery();
        }
        long pageIndex = query.getPageIndex() > 0 ? query.getPageIndex() : 1;
        long pageSize = query.getPageSize() > 0 ? query.getPageSize() : 10;

        Page<OptlogOperatorDTO> page = new Page<>(pageIndex, pageSize);
        Page<OptlogOperatorDTO> result = staffMapper.selectOptlogOperators(page, query.getName());
        return PageDTO.create(result);
    }
}

