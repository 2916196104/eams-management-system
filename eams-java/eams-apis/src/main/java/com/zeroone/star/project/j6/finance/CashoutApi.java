package com.zeroone.star.project.j6.finance;


import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.project.dto.j6.finance.BatchVerifyDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * <p>
 * 请款管理API接口（抽象层）
 * </p>
 * <p>版权: &copy;01星球</p>
 * <p>地址: 01星球总部</p>
 *
 * @author 你的名字
 * @version 1.0.0
 */
public interface CashoutApi {


    /**
     * 批量通过请款
     *
     * @param dto 批量操作参数（IDs+审核备注）
     * @return 操作结果
     */
    JsonVO<Void> batchPass(@RequestBody BatchVerifyDTO dto);

    /**
     * 批量驳回请款
     *
     * @param dto 批量操作参数（IDs+驳回备注，备注必填）
     * @return 操作结果
     */
    JsonVO<Void> batchReject(@RequestBody BatchVerifyDTO dto);
}