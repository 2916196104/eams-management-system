package com.zeroone.star.project.j9.operation;

import com.zeroone.star.project.dto.j9.operation.CreditMallSaveDTO;
import com.zeroone.star.project.query.j9.operation.CreditMallPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CreditMallDetailVO;
import com.zeroone.star.project.vo.j9.operation.CreditMallPageVO;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

/**
 * 积分商城礼品管理API接口
 */
public interface CreditMallApis {

    /**
     * 根据ID获取礼品详情
     */
    JsonVO<CreditMallDetailVO> queryDetailById(
            @ApiParam(value = "礼品ID", required = true) @PathVariable Long id);

    /**
     * 保存/新增礼品
     */
    JsonVO<Void> addCreditMall(@RequestBody CreditMallSaveDTO saveDTO);

    /**
     * 分页查询礼品列表
     */
    JsonVO<List<CreditMallPageVO>> queryCreditMallPage(CreditMallPageQuery pageQuery);

    /**
     * 删除礼品（支持批量删除）
     */
    JsonVO<String> removeCreditMall(
            @ApiParam(value = "礼品ID列表", required = true) @RequestBody List<Long> ids);

    /**
     * 启/禁用礼品（支持批量）
     */
    JsonVO<String> modifyCreditMallState(
            @ApiParam(value = "礼品ID列表", required = true) @RequestBody List<Long> ids,
            @ApiParam(value = "状态：0禁用 1启用", required = true) @RequestParam Integer state);
}
