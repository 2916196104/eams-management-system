package com.zeroone.star.operation.controller;

import com.zeroone.star.operation.service.DemoCardService;
import com.zeroone.star.operation.service.ITrialCardService;
import com.zeroone.star.project.dto.j7.operation.*;
import com.zeroone.star.project.query.j7.operation.TrialCardQuery;
import com.zeroone.star.project.query.j7.operation.TrialRecordQuery;
import com.zeroone.star.project.j7.operation.TrialCardApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.operation.TrialCardDetailVO;
import com.zeroone.star.project.vo.j7.operation.TrialCardVO;
import com.zeroone.star.project.vo.j7.operation.TrialRecordVO;
import com.zeroone.star.operation.service.DemoCardService;
import com.zeroone.star.project.dto.j7.operation.DemoCardDTO;
import com.zeroone.star.project.j7.operation.DemoCardApi;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

@RestController
@RequestMapping("/j7-operation/j7-trial")
@Api(tags = "试听卡管理")
@Validated
public class TrialCardController implements TrialCardApis,DemoCardApi {

    @Resource
    private ITrialCardService trialCardService;

    @Override
    @GetMapping("/trialList")
    @ApiOperation("获取试听卡列表")
    public JsonVO<TrialPageDTO<TrialCardVO>> queryTrialCardList(TrialCardQuery query) {
        return JsonVO.success(trialCardService.queryTrialCardList(query));
    }


    @Override
    @GetMapping("/query-detail/{id}")
    @ApiOperation("获取试听卡详情")
    public JsonVO<TrialCardDetailVO> queryTrialCardDetail(@PathVariable Long id) {
        if (id <= 0) {
            return JsonVO.fail("Id不合法");
        }
        TrialCardDetailVO detail = trialCardService.queryTrialCardDetail(id);
        if (detail == null) {
            return JsonVO.fail("试听卡不存在");
        }
        return JsonVO.success(detail);
    }

    @Override
    @GetMapping("/recordsList")
    @ApiOperation("获取试听卡领取记录")
    public JsonVO<TrialPageDTO<TrialRecordVO>> queryTrialCardRecords(TrialRecordQuery query) {
        if (query == null || query.getTrialId() == null) {
            return JsonVO.fail("没有传试听卡ID，无法查询试听卡领取记录");
        }
        if (query.getTrialId() <= 0) {
            return JsonVO.fail("试听卡ID不合法，请重新上传");
        }
        return JsonVO.success(trialCardService.queryTrialCardRecords(query));
    }

    @PostMapping("/save-trial")
    @ApiOperation("保存试听卡")
    @Override
    public JsonVO<Long> saveDemoCard(@RequestBody DemoCardDTO demoCardDTO) {
        Long id = demoCardService.saveDemoCard(demoCardDTO);
        return JsonVO.success(id);
    }

    /**
     * 删除试听卡
     * @param ids 试听卡编号
     * @return 删除结果
     */
    @ApiOperation("删除试听卡")
    @DeleteMapping("/remove-trial")
    @Override
    public JsonVO<Boolean> removeTrialCard(
            @ApiParam(value = "试听卡ID列表", required = true)
            @RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的试听卡");
        }
        Boolean result = trialCardService.removeTrialCard(ids);
        if (!result) {
            return JsonVO.fail("删除试听卡失败");
        }
        return JsonVO.success(true);
    }

    @Autowired
    private DemoCardService demoCardService;



}
