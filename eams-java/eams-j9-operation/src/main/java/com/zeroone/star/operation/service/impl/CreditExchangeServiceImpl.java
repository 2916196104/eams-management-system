package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.CreditExchangeDO;
import com.zeroone.star.operation.mapper.CreditExchangeMapper;
import com.zeroone.star.operation.mapper.CreditMallMapper;
import com.zeroone.star.operation.service.ICreditExchangeService;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CreditExchangeBatchAuditDTO;
import com.zeroone.star.project.query.j9.operation.CreditExchangeQuery;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeBatchAuditVO;
import com.zeroone.star.project.vo.j9.operation.CreditExchangeVO;
import com.zeroone.star.operation.entity.StudentCreditLogDO;
import com.zeroone.star.operation.mapper.StudentCreditLogMapper;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;

/**
 * 积分商城兑换记录 服务实现类
 */
@Service
@Slf4j
public class CreditExchangeServiceImpl extends ServiceImpl<CreditExchangeMapper, CreditExchangeDO> implements ICreditExchangeService {

    @Resource
    private UserHolder userHolder;

    @Resource
    private StudentCreditLogMapper studentCreditLogMapper;

    @Resource
    private CreditMallMapper creditMallMapper;

    @Override
    public PageDTO<CreditExchangeVO> listCreditExchanges(CreditExchangeQuery condition) {
        // 安全处理分页参数
        long current = condition.getPageIndex() < 1 ? 1 : condition.getPageIndex();
        long size = condition.getPageSize() <= 0 ? 10 : condition.getPageSize();
        
        Page<CreditExchangeVO> page = new Page<>(current, size);
        baseMapper.selectCreditExchangePage(page, condition);
        return PageDTO.create(page);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public CreditExchangeBatchAuditVO updateExchangeAudit(CreditExchangeBatchAuditDTO auditDTO) {
        List<Long> ids = auditDTO.getIds();
        Integer state = auditDTO.getVerifyState();
        String remark = auditDTO.getVerifyRemark();

        Long staffId = null;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            if (currentUser != null && currentUser.getId() != null) {
                staffId = Long.valueOf(currentUser.getId());
            }
        } catch (Exception ignored) {
        }

        int successCount = 0;
        for (Long id : ids) {
            // 1. 获取原申请记录
            CreditExchangeDO original = getById(id);
            if (original == null) continue;

            // 2. 更新审核状态
            CreditExchangeDO exchangeDO = new CreditExchangeDO();
            exchangeDO.setId(id);
            exchangeDO.setVerifyState(state);
            exchangeDO.setVerifyRemark(remark);
            exchangeDO.setVerifyStaff(staffId);
            exchangeDO.setVerifyTime(LocalDateTime.now());
            // 手动设置审计字段
            exchangeDO.setEditor(staffId);
            exchangeDO.setEditTime(LocalDateTime.now());
            
            if (updateById(exchangeDO)) {
                successCount++;
                
                // 3. 如果审核状态改为“已拒绝” (3)，需要退还积分并增加礼品库存
                if (state == 3 && original.getVerifyState() != 3) {
                    refundCreditAndStock(original, staffId);
                }
            }
        }

        CreditExchangeBatchAuditVO result = new CreditExchangeBatchAuditVO();
        result.setSuccessCount(successCount);
        result.setFailCount(ids.size() - successCount);
        result.setAllSuccess(successCount == ids.size());
        
        return result;
    }

    /**
     * 退还积分和库存逻辑
     */
    private void refundCreditAndStock(CreditExchangeDO exchange, Long staffId) {
        int refundAmount;
        try {
            refundAmount = Integer.parseInt(exchange.getCredit());
        } catch (NumberFormatException e) {
            throw new RuntimeException("积分值格式错误: " + exchange.getCredit(), e);
        }
        Long studentId = exchange.getStudentId();

        // 1. 获取当前积分余额（通过最后一条日志）
        LambdaQueryWrapper<StudentCreditLogDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(StudentCreditLogDO::getStudentId, studentId)
                .orderByDesc(StudentCreditLogDO::getAddTime)
                .last("LIMIT 1");
        StudentCreditLogDO lastLog = studentCreditLogMapper.selectOne(queryWrapper);

        int currentBalance = (lastLog != null && lastLog.getCurrentCredit() != null) ? lastLog.getCurrentCredit() : 0;
        int newBalance = currentBalance + refundAmount;

        // 2. 插入退还日志
        StudentCreditLogDO refundLog = new StudentCreditLogDO();
        refundLog.setStudentId(studentId);
        refundLog.setUserId(exchange.getUserId());
        refundLog.setSchoolId(exchange.getSchoolId());
        refundLog.setCredit(refundAmount);
        refundLog.setCurrentCredit(newBalance);
        refundLog.setRemark("积分兑换申请被拒绝，退还积分");
        refundLog.setStaffId(staffId);
        refundLog.setChangeType(2);
        refundLog.setAddTime(LocalDateTime.now());
        studentCreditLogMapper.insert(refundLog);

        // 3. 更新学生表余额
        studentCreditLogMapper.updateStudentCredit(studentId, newBalance);

        // 4. 增加礼品库存
        creditMallMapper.incrementStock(exchange.getCreditMallId(), exchange.getNum());
    }
}
