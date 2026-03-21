package com.zeroone.star.project.j1.orgmanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j1.orgmanager.PositionSetDTO;
import com.zeroone.star.project.j1.orgmanager.entity.Position;
import com.zeroone.star.project.j1.orgmanager.entity.StaffOrgInfo;
import com.zeroone.star.project.j1.orgmanager.mapper.PositionMapper;
import com.zeroone.star.project.j1.orgmanager.mapper.StaffOrgInfoMapper;
import com.zeroone.star.project.j1.orgmanager.service.IStaffOrgInfoService;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;

/**
 * <p>
 * 描述：员工组织信息业务层实现
 * </p>
 *
 * @author gzx
 * @version 1.0.0
 */
@Service
public class StaffOrgInfoServiceImpl implements IStaffOrgInfoService {
    @Resource
    private StaffOrgInfoMapper staffOrgInfoMapper;
    @Resource
    private PositionMapper positionMapper;
    @Resource
    private UserHolder userHolder;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean setStaffPosition(PositionSetDTO dto) {
        LambdaQueryWrapper<Position> positionWrapper = new LambdaQueryWrapper<>();
        positionWrapper.eq(Position::getId, dto.getPositionId());
        if (positionMapper.selectCount(positionWrapper) == 0) {
            throw new IllegalArgumentException("职位不存在");
        }

        LambdaQueryWrapper<StaffOrgInfo> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(StaffOrgInfo::getId, StaffOrgInfo::getCreator);
        wrapper.eq(StaffOrgInfo::getStaffId, dto.getStaffId());
        wrapper.eq(StaffOrgInfo::getOrgId, dto.getOrgId());
        wrapper.last("limit 1");
        StaffOrgInfo staffOrgInfo = staffOrgInfoMapper.selectOne(wrapper);

        Long creator = dto.getCreator() != null ? dto.getCreator() : getCurrentUserId();
        if (staffOrgInfo == null) {
            StaffOrgInfo entity = new StaffOrgInfo();
            entity.setStaffId(dto.getStaffId());
            entity.setOrgId(dto.getOrgId());
            entity.setPositionId(dto.getPositionId());
            entity.setCreator(creator);
            entity.setDeleted(0);
            entity.setAddTime(LocalDateTime.now());
            return staffOrgInfoMapper.insert(entity) == 1;
        }

        staffOrgInfo.setPositionId(dto.getPositionId());
        staffOrgInfo.setDeleted(0);
        if (creator != null) {
            staffOrgInfo.setCreator(creator);
        }
        return staffOrgInfoMapper.updateById(staffOrgInfo) == 1;
    }

    private Long getCurrentUserId() {
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            if (currentUser == null || currentUser.getId() == null) {
                return null;
            }
            return Long.valueOf(currentUser.getId());
        } catch (Exception exception) {
            return null;
        }
    }
}
