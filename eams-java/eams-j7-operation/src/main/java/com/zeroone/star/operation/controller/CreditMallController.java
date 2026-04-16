package com.zeroone.star.operation.controller;


import com.zeroone.star.operation.service.ICreditMallService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallAddDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallStateUpdateDTO;
import com.zeroone.star.project.j7.operation.CreditMallApis;
import com.zeroone.star.project.query.j7.operation.CreditMallListQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;


import javax.annotation.Resource;
import javax.validation.constraints.NotBlank;
import java.util.List;

@Api(tags = "积分礼品管理")
@Validated
@RestController
@RequestMapping("/j7-operation/j7-credit-mall")
public class CreditMallController implements CreditMallApis {
    @Resource
    ICreditMallService creditMallService;

    @PostMapping("/add-credit-mall")
    @Override
    @ApiOperation("保存礼品")
    public JsonVO<String> addPointsGift(@RequestBody @Validated CreditMallAddDTO addDto) {
        String id = creditMallService.saveCreditMall(addDto);
        if(id!=null) {
            return JsonVO.success(id);
        }
        return JsonVO.fail("保存失败");
    }

    @GetMapping("/query-list-credit-mall")
    @Override
    @ApiOperation("获取礼品列表")
    public JsonVO<PageDTO<CreditMallDTO>> queryAllPointsGift(@Validated CreditMallListQuery condition) {
        return JsonVO.success(creditMallService.listAllCreditMalls(condition));
    }

    @GetMapping("/query-by-id/{id}")
    @Override
    @ApiOperation("获取礼品详情")
    @ApiImplicitParam(name = "id", value = "编号", required = true, example = "1770589234567890123", paramType = "path")
    public JsonVO<CreditMallDetailDTO> queryById(@PathVariable String id) {
        if (id == null || id.trim().isEmpty()) {
            return JsonVO.fail("ID不能为空");
        }
        CreditMallDetailDTO creditMall = creditMallService.getCreditMallById(id);
        if(creditMall == null) {
            return JsonVO.fail("积分礼品id不存在");
        }
        return JsonVO.success(creditMall);
    }
    @DeleteMapping("/remove-credit-mall")
    @Override
    @ApiOperation("删除礼品")
    public JsonVO<String> removePointsGift(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的礼品");
        }
        return creditMallService.removePointsGift(ids);
    }

    @ApiOperation("启用/禁用礼品")
    @PutMapping("/enable-credit-mall")
    @Override
    public JsonVO<String> enablePointsGift(@RequestBody CreditMallStateUpdateDTO updateDTO) {
        if (updateDTO.getIds() == null || updateDTO.getIds().isEmpty()) {
            return JsonVO.fail("请选择要操作的礼品");
        }
        if (updateDTO.getState() == null) {
            return JsonVO.fail("状态值不能为空");
        }
        if (updateDTO.getState() != 0 && updateDTO.getState() != 1) {
            return JsonVO.fail("状态值只能为0（禁用）或1（启用）");
        }
        return creditMallService.enablePointsGift(updateDTO.getIds(), updateDTO.getState());
    }


}
