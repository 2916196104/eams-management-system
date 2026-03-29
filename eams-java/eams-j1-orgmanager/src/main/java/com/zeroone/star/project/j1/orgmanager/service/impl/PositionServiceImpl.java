package com.zeroone.star.project.j1.orgmanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j1.orgmanager.PositionDTO;
import com.zeroone.star.project.entity.j1.orgmanager.Position;
import com.zeroone.star.project.entity.j1.orgmanager.StaffOrgInfo;
import com.zeroone.star.project.j1.orgmanager.mapper.position.PositionMapper;
import com.zeroone.star.project.j1.orgmanager.mapper.position.StaffOrgInfoMapper;
import com.zeroone.star.project.j1.orgmanager.service.IPositionService;
import com.zeroone.star.project.query.j1.orgmanager.PositionQueryCondition;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

@Service
public class PositionServiceImpl implements IPositionService {
    @Resource
    private PositionMapper positionMapper;
    @Resource
    private StaffOrgInfoMapper staffOrgInfoMapper;
    @Resource
    private UserHolder userHolder;

    @Override
    public List<String> listNames(String name) {
        LambdaQueryWrapper<Position> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(Position::getName);
        if (name != null && !name.trim().isEmpty()) {
            wrapper.like(Position::getName, name.trim());
        }
        wrapper.orderByDesc(Position::getId);
        return positionMapper.selectList(wrapper).stream()
                .map(Position::getName)
                .filter(Objects::nonNull)
                .collect(Collectors.toList());
    }

    @Override
    public PageDTO<PositionDTO> list(PositionQueryCondition condition) {
        LambdaQueryWrapper<Position> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(Position::getId, Position::getName);
        if (condition.getName() != null && !condition.getName().trim().isEmpty()) {
            wrapper.like(Position::getName, condition.getName().trim());
        }
        wrapper.orderByDesc(Position::getId);

        Page<Position> page = new Page<>(condition.getPage(), condition.getPageSize());
        Page<Position> records = positionMapper.selectPage(page, wrapper);
        return PageDTO.create(records, PositionDTO.class);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean save(PositionDTO dto) {
        String name = dto.getName().trim();
        LambdaQueryWrapper<Position> duplicateWrapper = new LambdaQueryWrapper<>();
        duplicateWrapper.eq(Position::getName, name);
        if (dto.getId() != null) {
            duplicateWrapper.ne(Position::getId, dto.getId());
        }
        if (positionMapper.selectCount(duplicateWrapper) > 0) {
            throw new IllegalArgumentException("职位名称已存在");
        }

        Long currentUserId = getCurrentUserId();
        LocalDateTime now = LocalDateTime.now();
        if (dto.getId() == null) {
            Position entity = new Position();
            entity.setName(name);
            entity.setAddTime(now);
            entity.setCreator(currentUserId);
            return positionMapper.insert(entity) == 1;
        }

        LambdaQueryWrapper<Position> existsWrapper = new LambdaQueryWrapper<>();
        existsWrapper.eq(Position::getId, dto.getId());
        if (positionMapper.selectCount(existsWrapper) == 0) {
            throw new IllegalArgumentException("职位不存在");
        }

        Position entity = new Position();
        entity.setId(dto.getId());
        entity.setName(name);
        entity.setEditTime(now);
        entity.setEditor(currentUserId);
        return positionMapper.updateById(entity) == 1;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean delete(List<Long> ids) {
        List<Long> distinctIds = ids.stream().filter(Objects::nonNull).distinct().collect(Collectors.toList());
        if (distinctIds.isEmpty()) {
            throw new IllegalArgumentException("职位ID列表不能为空");
        }

        LambdaQueryWrapper<StaffOrgInfo> usageWrapper = new LambdaQueryWrapper<>();
        usageWrapper.in(StaffOrgInfo::getPositionId, distinctIds);
        usageWrapper.and(wrapper -> wrapper.eq(StaffOrgInfo::getDeleted, 0).or().isNull(StaffOrgInfo::getDeleted));
        if (staffOrgInfoMapper.selectCount(usageWrapper) > 0) {
            throw new IllegalArgumentException("职位已被员工使用，不能删除");
        }

        return positionMapper.deleteBatchIds(distinctIds) > 0;
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
