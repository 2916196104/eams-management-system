package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.StudentCreditLogDO;
import com.zeroone.star.operation.mapper.StudentCreditLogMapper;
import com.zeroone.star.operation.service.IStudentCreditLogService;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.StudentCreditAdjustDTO;
import com.zeroone.star.project.query.j9.operation.StudentCreditLogQuery;
import com.zeroone.star.project.vo.j9.operation.StudentCreditAdjustVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditLogVO;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;

/**
 * 学生积分变动记录 服务实现类
 */
@Service
public class StudentCreditLogServiceImpl extends ServiceImpl<StudentCreditLogMapper, StudentCreditLogDO> implements IStudentCreditLogService {

    @Resource
    private UserHolder userHolder;

    @Override
    public PageDTO<StudentCreditLogVO> listCreditLogs(StudentCreditLogQuery condition) {
        // 安全处理：如果当前页小于1，默认为1；如果每页条数小于等于0，默认为10
        long current = condition.getPageIndex() < 1 ? 1 : condition.getPageIndex();
        long size = condition.getPageSize() <= 0 ? 10 : condition.getPageSize();
        
        Page<StudentCreditLogVO> page = new Page<>(current, size);
        baseMapper.selectCreditLogPage(page, condition);
        return PageDTO.create(page);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public StudentCreditAdjustVO updateStudentCredit(StudentCreditAdjustDTO adjustDTO) {
        // 1. 获取当前操作用户信息
        Long staffId = null;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            if (currentUser != null && currentUser.getId() != null) {
                staffId = Long.valueOf(currentUser.getId());
            }
        } catch (Exception ignored) {
        }

        // 2. 查询该学生最近一条积分记录以获取当前积分
        LambdaQueryWrapper<StudentCreditLogDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(StudentCreditLogDO::getStudentId, adjustDTO.getStudentId())
                .orderByDesc(StudentCreditLogDO::getAddTime)
                .last("LIMIT 1");
        StudentCreditLogDO lastLog = baseMapper.selectOne(queryWrapper);

        int currentCredit = 0;
        Long userId = null;
        Long schoolId = null;
        
        if (lastLog != null) {
            currentCredit = lastLog.getCurrentCredit() != null ? lastLog.getCurrentCredit() : 0;
            userId = lastLog.getUserId();
            schoolId = lastLog.getSchoolId();
        } else {
            // 如果没有历史记录，通常需要从 student 表查询 userId，这里先尝试抛出异常或设置默认
            // 正常业务下，学生创建时应该就有关联的 userId
            throw new RuntimeException("找不到该学生的历史积分记录，无法确定关联的用户账号");
        }
        
        int newCredit = currentCredit + adjustDTO.getAdjustCredit();

        // 校验变动后的数据是否正常（余额是否大于等于0）
        if (newCredit < 0) {
            StudentCreditAdjustVO failVo = new StudentCreditAdjustVO();
            failVo.setSuccess(false);
            failVo.setCurrentCredit(currentCredit);
            return failVo;
        }

        // 3. 构造新的积分变动记录
        StudentCreditLogDO newLog = new StudentCreditLogDO();
        newLog.setStudentId(adjustDTO.getStudentId());
        newLog.setUserId(userId);
        newLog.setSchoolId(schoolId);
        newLog.setCredit(adjustDTO.getAdjustCredit());
        newLog.setCurrentCredit(newCredit);
        newLog.setRemark(adjustDTO.getAdjustReason() != null ? adjustDTO.getAdjustReason() : "管理员手动调整");
        newLog.setStaffId(staffId);
        newLog.setChangeType(0); // 设置一个默认的变更类型，例如 0-管理员调整
        newLog.setAddTime(LocalDateTime.now());

        boolean saved = save(newLog);
        
        // 4. 更新学生表的总积分余额
        if (saved) {
            baseMapper.updateStudentCredit(adjustDTO.getStudentId(), newCredit);
        }

        // 5. 构造返回结果
        StudentCreditAdjustVO vo = new StudentCreditAdjustVO();
        vo.setSuccess(saved);
        vo.setCurrentCredit(newCredit);
        return vo;
    }
}
