package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.PayOverdueDTO;
import com.zeroone.star.project.dto.j8.stumanager.RefundDTO;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.j8.stumanager.common.RegistryRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.PayOverdueDTO;
import com.zeroone.star.project.dto.j8.stumanager.RefundDTO;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.j8.stumanager.common.RegistryRecordsApis;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.stumanager.service.IRegistryRecordsService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;


/**
 * 报名记录
 */
@RestController
@RequestMapping("/stu/common/registry-records")
@Api(tags = "共用接口-报名记录")
public class RegistryRecordsController implements RegistryRecordsApis {
    @Autowired
    private IRegistryRecordsService registryRecordsService;

    @GetMapping("/query-all")
    @ApiOperation("获取报名记录 (条件 + 分页)")
    @Override
    public JsonVO<PageDTO<RegistryRecordsDTO>> queryRegistryRecords(@RequestBody RegistryRecordsQuery condition) {

        if (condition.getPageSize() == 0) {
            condition.setPageIndex(1);
            condition.setPageSize(Integer.MAX_VALUE);
        }
        PageDTO<RegistryRecordsDTO> result = registryRecordsService.queryRegistryRecords(condition);
        return JsonVO.success(result);
    }


    @PutMapping("/modify-refund/{id}")
    @ApiOperation("退费")
    @Override
    public JsonVO<String> modifyRefund(RefundDTO dto, @PathVariable Long id) {
        String result = registryRecordsService.modifyRefund(dto, id);
        return JsonVO.success(result);
    }

    @PutMapping("/modify-payOverdue/{id}")
    @ApiOperation("缴纳欠费")
    @Override
    public JsonVO<String> modifyPayOverdue(PayOverdueDTO dto, @PathVariable Long id) {
        String result = registryRecordsService.modifyPayOverdue(dto, id);
        return JsonVO.success(result);
    }
}
