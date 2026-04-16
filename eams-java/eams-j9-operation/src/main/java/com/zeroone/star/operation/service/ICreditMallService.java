package com.zeroone.star.operation.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.operation.entity.CreditMallDO;
import com.zeroone.star.project.dto.j9.operation.CreditMallSaveDTO;
import com.zeroone.star.project.query.j9.operation.CreditMallPageQuery;
import java.util.List;
import com.zeroone.star.project.vo.j9.operation.CreditMallDetailVO;
import com.zeroone.star.project.vo.j9.operation.CreditMallPageVO;

/**
 * 积分商城礼品 业务层接口
 */
public interface ICreditMallService extends IService<CreditMallDO> {

    /**
     * 根据ID查询礼品详情
     * @param id 礼品ID
     * @return 礼品详情VO
     */
    CreditMallDetailVO getDetailById(Long id);

    /**
     * 新增/修改礼品
     * @param saveDTO 新增/修改参数
     * @return 是否成功
     */
    boolean saveCreditMall(CreditMallSaveDTO saveDTO);

    /**
     * 分页查询礼品列表
     * @param pageQuery 分页查询参数
     * @return 分页结果
     */
    IPage<CreditMallPageVO> listCreditMallPage(CreditMallPageQuery pageQuery);

    /**
     * 批量更新礼品状态（启用/禁用）
     * @param ids 礼品ID列表
     * @param state 状态：0禁用 1启用
     * @return 是否成功
     */
    boolean updateState(List<Long> ids, Integer state);
}