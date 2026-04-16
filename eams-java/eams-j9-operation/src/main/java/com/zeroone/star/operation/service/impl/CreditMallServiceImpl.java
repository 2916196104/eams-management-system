package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.CreditMallDO;
import com.zeroone.star.operation.mapper.CreditMallMapper;
import com.zeroone.star.operation.service.ICreditMallService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.dto.j9.operation.CreditMallSaveDTO;
import com.zeroone.star.project.query.j9.operation.CreditMallPageQuery;
import com.zeroone.star.project.vo.j9.operation.CreditMallDetailVO;
import com.zeroone.star.project.vo.j9.operation.CreditMallPageVO;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.Assert;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;

/**
 * 积分商城礼品 业务层实现（适配UserHolder完整逻辑）
 */
@Service
public class CreditMallServiceImpl extends ServiceImpl<CreditMallMapper, CreditMallDO>
        implements ICreditMallService {

    @Resource
    private UserHolder userHolder;

    @Autowired
    private CreditMallMapper creditMallMapper;

    /**
     * 根据ID查询礼品详情
     */
    @Override
    public CreditMallDetailVO getDetailById(Long id) {
        if (id == null || id <= 0) {
            throw new IllegalArgumentException("礼品ID不能为空且必须为正整数");
        }

        CreditMallDO creditMallDO = this.getOne(
                new LambdaQueryWrapper<CreditMallDO>()
                        .eq(CreditMallDO::getId, id)
                        .eq(CreditMallDO::getDeleted, 0)
        );
        if (creditMallDO == null) {
            throw new IllegalArgumentException("礼品不存在或已删除");
        }

        CreditMallDetailVO detailVO = new CreditMallDetailVO();
        BeanUtils.copyProperties(creditMallDO, detailVO);
        return detailVO;
    }


    /**
     * 保存/更新积分商城礼品信息（使用MP自动填充公共字段）
     * @param saveDTO 保存参数
     * @return 保存结果
     */
    @Override
    public boolean saveCreditMall(CreditMallSaveDTO saveDTO) {
        // 1. 核心业务参数校验
        if (saveDTO == null) {
            throw new IllegalArgumentException("保存参数不能为空");
        }
        if (saveDTO.getName() == null || saveDTO.getName().trim().isEmpty()) {
            throw new IllegalArgumentException("礼品名称不能为空");
        }
        if (saveDTO.getMaterialId() == null || saveDTO.getMaterialId() <= 0) {
            throw new IllegalArgumentException("物料分类ID不能为空且必须为正整数");
        }
        if (saveDTO.getCategoryId() == null || saveDTO.getCategoryId() <= 0) {
            throw new IllegalArgumentException("礼品分类ID不能为空且必须为正整数");
        }
        if (saveDTO.getCredit() == null || saveDTO.getCredit() <= 0) {
            throw new IllegalArgumentException("兑换积分不能为空且必须为正整数");
        }

        // 2. DTO转DO（仅复制业务字段，公共字段交给MP自动填充）
        CreditMallDO creditMallDO = new CreditMallDO();
        BeanUtils.copyProperties(saveDTO, creditMallDO);

        // 3. 仅保留非公共字段的默认值设置（MP无法自动填充的业务默认值）
        if (creditMallDO.getId() == null) {
            // 新增时的业务默认值（非公共字段，MP不处理）
            creditMallDO.setDeleted(0);
            creditMallDO.setSaleNum(0);
            creditMallDO.setViewNum(0);
            creditMallDO.setState(1);
        }

        // 4. 直接调用MP的saveOrUpdate，公共字段由MetaObjectHandler自动填充
        return this.saveOrUpdate(creditMallDO);
    }

    /**
     * 分页查询礼品列表
     */
    @Override
    public IPage<CreditMallPageVO> listCreditMallPage(CreditMallPageQuery pageQuery) {
        if (pageQuery == null) {
            throw new IllegalArgumentException("分页查询参数不能为空");
        }
        if (pageQuery.getPageIndex() < 1) {
            throw new IllegalArgumentException("页码不能小于1");
        }
        if (pageQuery.getPageSize() < 1) {
            throw new IllegalArgumentException("每页条数不能小于1");
        }

        Page<CreditMallPageVO> page = new Page<>(pageQuery.getPageIndex(), pageQuery.getPageSize());
        return baseMapper.pageQueryWithSchoolName(page, pageQuery);
    }

    @Override
    public boolean updateState(List<Long> ids, Integer state) {
        return this.update().set("state", state).in("id", ids).update();
    }
}