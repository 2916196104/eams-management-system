package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.entity.Advertisement;
import com.zeroone.star.interact.mapper.AdvertisementMapper;
import com.zeroone.star.interact.service.IAdvertisementService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.AdvertisementDTO;
import com.zeroone.star.project.query.j6.interact.AdvertisementListQuery;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

/**
 * 广告/通知管理 Service 实现类
 */
@Service
public class AdvertisementServiceImpl extends ServiceImpl<AdvertisementMapper, Advertisement>
        implements IAdvertisementService {

    /**
     * 类型描述映射
     */
    private static final String[] TYPE_DESC = {"未知", "学生端首页Banner", "学生端首页提示", "学生端首页弹窗"};

    /**
     * 分页查询广告列表
     */
    @Override
    public PageDTO<AdvertisementDTO> queryPage(AdvertisementListQuery query) {
        // 构建分页对象
        Page<Advertisement> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 构建查询条件
        LambdaQueryWrapper<Advertisement> wrapper = new LambdaQueryWrapper<>();

        // 标题模糊查询
        if (StringUtils.hasText(query.getTitle())) {
            wrapper.like(Advertisement::getTitle, query.getTitle());
        }
        // 类型精确查询
        if (query.getType() != null) {
            wrapper.eq(Advertisement::getType, query.getType());
        }
        // 状态精确查询
        if (query.getState() != null) {
            wrapper.eq(Advertisement::getState, query.getState());
        }
        // 按排序值升序，创建时间倒序
        wrapper.orderByAsc(Advertisement::getSortNum)
               .orderByDesc(Advertisement::getAddTime);

        // 执行分页查询
        Page<Advertisement> resultPage = this.page(page, wrapper);

        // 转换为 DTO
        return PageDTO.create(resultPage, this::toDTO);
    }

    /**
     * 获取广告详情
     */
    @Override
    public AdvertisementDTO getDetail(Long id) {
        Advertisement entity = this.getById(id);
        if (entity == null) {
            return null;
        }
        return toDTO(entity);
    }

    /**
     * 将 Advertisement 实体转换为 AdvertisementDTO
     */
    private AdvertisementDTO toDTO(Advertisement entity) {
        AdvertisementDTO dto = new AdvertisementDTO();
        dto.setId(entity.getId());
        dto.setTitle(entity.getTitle());
        dto.setType(entity.getType());
        // 设置类型描述
        if (entity.getType() != null && entity.getType() >= 1 && entity.getType() <= 3) {
            dto.setTypeDesc(TYPE_DESC[entity.getType()]);
        }
        dto.setContent(entity.getContent());
        dto.setCover(entity.getCover());
        dto.setCreator(entity.getCreator());
        dto.setAddTime(entity.getAddTime());
        dto.setState(entity.getState());
        dto.setSortNum(entity.getSortNum());
        dto.setEditor(entity.getEditor());
        dto.setEditTime(entity.getEditTime());
        dto.setCode(entity.getCode());
        return dto;
    }
}
