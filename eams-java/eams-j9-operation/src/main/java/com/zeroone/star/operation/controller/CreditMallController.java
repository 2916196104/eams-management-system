package com.zeroone.star.operation.controller;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.operation.service.ICreditMallService;
import com.zeroone.star.project.j9.operation.CreditMallApis;
import com.zeroone.star.project.dto.j9.operation.CreditMallSaveDTO;
import com.zeroone.star.project.query.j9.operation.CreditMallPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j9.operation.CreditMallDetailVO;
import com.zeroone.star.project.vo.j9.operation.CreditMallPageVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.List;

/**
 * 积分商城礼品管理Controller
 */
@Api(tags = "积分商城礼品管理")
@RestController
@RequestMapping("credit-mall")
public class CreditMallController implements CreditMallApis {

    @Autowired
    private ICreditMallService creditMallService;

    @GetMapping("detail/{id}")
    @ApiOperation("根据ID获取礼品详情")
    @Override
    public JsonVO<CreditMallDetailVO> queryDetailById(
            @ApiParam(value = "礼品ID", required = true) @PathVariable Long id) {
        CreditMallDetailVO detailVO = creditMallService.getDetailById(id);
        return JsonVO.success(detailVO);
    }

    @PostMapping("save")
    @ApiOperation("保存/新增礼品")
    @Override
    public JsonVO<Void> addCreditMall(
            @Valid @RequestBody CreditMallSaveDTO saveDTO) {
       boolean success = creditMallService.saveCreditMall(saveDTO);
        if (success) {
            return JsonVO.create(null, ResultStatus.SUCCESS.getCode(), "保存成功");
        } else {
            return JsonVO.fail("保存失败");
        }
    }

    @GetMapping("list")
    @ApiOperation("分页查询礼品列表")
    @Override
    public JsonVO<List<CreditMallPageVO>> queryCreditMallPage(CreditMallPageQuery pageQuery) {
        IPage<CreditMallPageVO> pageResult = creditMallService.listCreditMallPage(pageQuery);
        return JsonVO.success(pageResult.getRecords());
    }

    @DeleteMapping
    @ApiOperation("删除礼品（支持批量删除）")
    @Override
    public JsonVO<String> removeCreditMall(
            @ApiParam(value = "礼品ID列表", required = true) @RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的礼品");
        }
        boolean success = creditMallService.removeByIds(ids);
        return success ? JsonVO.success("删除成功") : JsonVO.fail("删除失败");
    }

    @PutMapping("enable-disable")
    @ApiOperation("启/禁用礼品（支持批量）")
    @Override
    public JsonVO<String> modifyCreditMallState(
            @ApiParam(value = "礼品ID列表", required = true) @RequestBody List<Long> ids,
            @ApiParam(value = "状态：0禁用 1启用", required = true) @RequestParam Integer state) {
        boolean success = creditMallService.updateState(ids, state);
        return success ? JsonVO.success("操作成功") : JsonVO.fail("操作失败");
    }
}
