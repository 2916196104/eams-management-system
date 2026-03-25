package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.interact.entity.Homework;
import com.zeroone.star.interact.mapper.HomeworkMapper;
import com.zeroone.star.interact.service.HomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;


@Service
public class HomeworkServiceImpl implements HomeworkService {

    @Autowired
    private HomeworkMapper homeworkMapper;

    /**
     * 获取作业列表
     * @param homeworkQuery
     * @return
     */
    @Override
    public PageDTO<HomeworkListDto> pageQuery(HomeworkQuery homeworkQuery) {
        // 创建分页对象
        Page<Homework> page = new Page<>(homeworkQuery.getPageIndex(), homeworkQuery.getPageSize());

        // 构建查询条件
        LambdaQueryWrapper<Homework> wrapper = new LambdaQueryWrapper<>();
        // 标题模糊查询
        if (StringUtils.hasText(homeworkQuery.getTitle())) {
            wrapper.like(Homework::getTitle, homeworkQuery.getTitle());
        }
        // 班级精确查询
        if (homeworkQuery.getClass_id() != null) {
            wrapper.eq(Homework::getClassId, homeworkQuery.getClass_id());
        }
        // 按添加时间降序排列
        wrapper.orderByDesc(Homework::getAddTime);

        // 执行分页查询
        Page<Homework> resultPage = homeworkMapper.selectPage(page, wrapper);

        // 转换为DTO
        return PageDTO.create(resultPage, entity -> {
            HomeworkListDto dto = new HomeworkListDto();
            dto.setId(entity.getId());
            dto.setTitle(entity.getTitle());
            dto.setClass_id(entity.getClassId());
            dto.setAdd_time(entity.getAddTime());
            // TODO: 需要关联查询用户表获取发布者名称
            // dto.setCreator(creatorName);
            // TODO: 需要统计提交数
            // dto.setSubmit_data(submitCount);
            return dto;
        });
    }

    /**
     * 获取作业详情
     * @param id
     * @return
     */
    @Override
    public HomeworkDetailVO getHomeworkDetail(Long id) {
        Homework entity = homeworkMapper.selectById(id);
        if (entity == null) {
            return null;
        }
        HomeworkDetailVO vo = new HomeworkDetailVO();
        vo.setId(entity.getId());
        vo.setClass_id(entity.getClassId());
        vo.setTitle(entity.getTitle());
        vo.setContent(entity.getContent());
        return vo;
    }


    /**
     * 保存作业
     * @param homeworkDetailDto
     * @return
     */
    @Override
    public Long saveHomework(HomeworkDetailDto homeworkDetailDto) {
        Homework entity = new Homework();
        entity.setClassId(homeworkDetailDto.getClass_id());
        entity.setTitle(homeworkDetailDto.getTitle());
        entity.setContent(homeworkDetailDto.getContent());

        // 判断是修改还是新增：id不为空且数据库中存在该记录才是修改
        boolean isUpdate = false;
        if (homeworkDetailDto.getId() != null) {
            Homework existingHomework = homeworkMapper.selectById(homeworkDetailDto.getId());
            isUpdate = (existingHomework != null);
        }

        if (isUpdate) {
            // 修改操作
            entity.setId(homeworkDetailDto.getId());
            entity.setEditTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取editor
            // entity.setEditor(currentUserId);
            homeworkMapper.updateById(entity);
        } else {
            // 新增操作（不使用前端传入的id，让数据库自动生成）
            entity.setAddTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取creator
            // entity.setCreator(currentUserId);
            homeworkMapper.insert(entity);
        }
        return entity.getId();
    }
}
