package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.entity.Advertisement;
import com.zeroone.star.interact.mapper.AnnouncementMapper;
import com.zeroone.star.interact.service.AnnouncementService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AnnouncementDTO;
import com.zeroone.star.project.query.j6.interact.AnnouncementListQuery;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 公告管理服务实现类
 *
 * @author maban
 * @since 2026-03-28
 */
@Service
public class AnnouncementServiceImpl extends ServiceImpl<AnnouncementMapper, Advertisement> implements AnnouncementService {

    /**
     * 类型映射：类型编码 -> 类型名称
     */
    private static final Map<Integer, String> TYPE_NAME_MAP = new HashMap<>();

    static {
        TYPE_NAME_MAP.put(1, "学生端首页弹出");
        TYPE_NAME_MAP.put(2, "学生端首页公告");
        TYPE_NAME_MAP.put(3, "学生端首页Banner");
        TYPE_NAME_MAP.put(4, "普通公告");
    }

    @Override
    public PageDTO<AnnouncementDTO> queryPage(AnnouncementListQuery query) {
        // 创建分页对象
        Page<Advertisement> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 构建查询条件
        LambdaQueryWrapper<Advertisement> wrapper = new LambdaQueryWrapper<>();
        // 标题模糊查询
        if (StringUtils.hasText(query.getTitle())) {
            wrapper.like(Advertisement::getTitle, query.getTitle());
        }
        // 发布者精确查询
        if (query.getCreatorId() != null) {
            wrapper.eq(Advertisement::getCreator, query.getCreatorId());
        }
        // 类型精确查询
        if (query.getType() != null) {
            wrapper.eq(Advertisement::getType, query.getType());
        }
        // 按创建时间降序排列
        wrapper.orderByDesc(Advertisement::getAddTime);

        // 执行分页查询
        Page<Advertisement> resultPage = this.page(page, wrapper);

        // 转换为DTO
        return PageDTO.create(resultPage, this::convertToDTO);
    }

    @Override
    public AnnouncementDTO getDetail(Long id) {
        Advertisement entity = this.getById(id);
        if (entity == null) {
            return null;
        }
        return convertToDTO(entity);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveAnnouncement(AnnouncementDTO dto) {
        Advertisement entity = new Advertisement();
        entity.setTitle(dto.getTitle());
        entity.setContent(dto.getContent());
        entity.setType(dto.getType());
        entity.setCover(dto.getImageUrl());

        // 判断是修改还是新增
        boolean isUpdate = false;
        if (dto.getId() != null) {
            Advertisement existing = this.getById(dto.getId());
            isUpdate = (existing != null);
        }

        if (isUpdate) {
            // 修改操作
            entity.setId(dto.getId());
            entity.setEditTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取editor
            // entity.setEditor(currentUserId);
            this.updateById(entity);
        } else {
            // 新增操作
            entity.setAddTime(LocalDateTime.now());
            entity.setState(1); // 默认启用
            // TODO: 从当前登录用户获取creator
            // entity.setCreator(currentUserId);
            this.save(entity);
        }
        return entity.getId();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> removeAnnouncement(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return new ArrayList<>();
        }
        // 逻辑删除
        this.removeByIds(ids);
        return ids;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> updateAnnouncementState(List<Long> ids, Integer state) {
        if (ids == null || ids.isEmpty()) {
            return new ArrayList<>();
        }
        // 批量更新状态
        LambdaUpdateWrapper<Advertisement> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.in(Advertisement::getId, ids)
                .set(Advertisement::getState, state)
                .set(Advertisement::getEditTime, LocalDateTime.now());
        this.update(updateWrapper);
        return ids;
    }

    @Override
    public String getTypeName(Integer type) {
        return TYPE_NAME_MAP.getOrDefault(type, "未知类型");
    }

    /**
     * 将实体转换为DTO
     *
     * @param entity 实体对象
     * @return DTO对象
     */
    private AnnouncementDTO convertToDTO(Advertisement entity) {
        AnnouncementDTO dto = new AnnouncementDTO();
        dto.setId(entity.getId());
        dto.setTitle(entity.getTitle());
        dto.setContent(entity.getContent());
        dto.setType(entity.getType());
        dto.setTypeName(getTypeName(entity.getType()));
        dto.setImageUrl(entity.getCover());
        dto.setCreatorId(entity.getCreator());
        dto.setCreateTime(entity.getAddTime());
        dto.setState(entity.getState());
        // TODO: 关联查询用户表获取发布者姓名
        // dto.setCreatorName(creatorName);
        return dto;
    }
}
