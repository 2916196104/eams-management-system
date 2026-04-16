package com.zeroone.star.eas.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.eas.entity.ClassGrade;
import com.zeroone.star.eas.mapper.ClassGradeMapper;
import com.zeroone.star.eas.service.IGradeManagerService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.ClassGradeDto;
import com.zeroone.star.project.dto.j6.eas.GradeNameDto;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 年级管理Service实现类
 */
@Service
public class GradeManagerServiceImpl extends ServiceImpl<ClassGradeMapper, ClassGrade> implements IGradeManagerService {

    /**
     * 分页查询年级列表
     *
     * @param query 查询条件
     * @return 分页数据
     */
    @Override
    public PageDTO<ClassGradeDto> queryPage(GradeManagerQuery query) {
        // 创建分页对象
        Page<ClassGrade> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 构建查询条件
        LambdaQueryWrapper<ClassGrade> wrapper = new LambdaQueryWrapper<>();
        // 年级名称模糊查询
        if (StringUtils.hasText(query.getName())) {
            wrapper.like(ClassGrade::getName, query.getName());
        }
        // 入学年份精确查询
        if (query.getYear() != null) {
            wrapper.eq(ClassGrade::getYear, query.getYear());
        }
        // 按排序值升序排列
        wrapper.orderByAsc(ClassGrade::getSortNum);

        // 执行分页查询
        Page<ClassGrade> resultPage = this.page(page, wrapper);

        // 转换为DTO
        return PageDTO.create(resultPage, entity -> {
            ClassGradeDto dto = new ClassGradeDto();
            dto.setId(entity.getId());
            dto.setName(entity.getName());
            dto.setYear(entity.getYear());
            dto.setRemark(entity.getRemark());
            dto.setSortNum(entity.getSortNum());
            return dto;
        });
    }

    /**
     * 根据ID获取年级详情
     *
     * @param id 年级ID
     * @return 年级详情
     */
    @Override
    public ClassGradeDto getGradeById(Long id) {
        ClassGrade entity = this.getById(id);
        if (entity == null) {
            return null;
        }
        ClassGradeDto dto = new ClassGradeDto();
        dto.setId(entity.getId());
        dto.setName(entity.getName());
        dto.setYear(entity.getYear());
        dto.setRemark(entity.getRemark());
        dto.setSortNum(entity.getSortNum());
        return dto;
    }

    /**
     * 获取年级名称列表（用于下拉框）
     *
     * @return 年级名称列表
     */
    @Override
    public List<GradeNameDto> queryGradeNameList() {
        // 查询所有年级，按排序值升序排列
        LambdaQueryWrapper<ClassGrade> wrapper = new LambdaQueryWrapper<>();
        wrapper.orderByAsc(ClassGrade::getSortNum);
        List<ClassGrade> list = this.list(wrapper);

        // 转换为GradeNameDto
        return list.stream().map(entity -> {
            GradeNameDto dto = new GradeNameDto();
            dto.setId(entity.getId());
            dto.setName(entity.getName());
            return dto;
        }).collect(Collectors.toList());
    }

    /**
     * 保存年级（新增或修改）
     *
     * @param classGradeDto 年级信息
     * @return 年级ID
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveClassGrade(ClassGradeDto classGradeDto) {
        ClassGrade entity = new ClassGrade();
        entity.setName(classGradeDto.getName());
        entity.setYear(classGradeDto.getYear());
        entity.setRemark(classGradeDto.getRemark());
        entity.setSortNum(classGradeDto.getSortNum());

        // 判断是修改还是新增：id不为空且数据库中存在该记录才是修改
        boolean isUpdate = false;
        if (classGradeDto.getId() != null) {
            ClassGrade existingGrade = this.getById(classGradeDto.getId());
            isUpdate = (existingGrade != null);
        }

        if (isUpdate) {
            // 修改操作
            entity.setId(classGradeDto.getId());
            entity.setEditTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取editor
            // entity.setEditor(currentUserId);
            this.updateById(entity);
        } else {
            // 新增操作（不使用前端传入的id，让数据库自动生成）
            entity.setAddTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取creator
            // entity.setCreator(currentUserId);
            this.save(entity);
        }
        return entity.getId();
    }

    /**
     * 批量删除年级
     *
     * @param ids 年级ID列表
     * @return 删除的ID列表
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> deleteClassGrade(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return new ArrayList<>();
        }
        // 逻辑删除
        this.removeByIds(ids);
        return ids;
    }

    /**
     * 批量升级年级
     * 升级操作：将入学年份减1（年级升高），例如2024级升级为2023级
     *
     * @param ids 年级ID列表
     * @return 升级的ID列表
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> upgradeClassGrade(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return new ArrayList<>();
        }

        // 查询需要升级的年级
        List<ClassGrade> gradeList = this.listByIds(ids);
        for (ClassGrade grade : gradeList) {
            // 年级升级：入学年份加1
            grade.setYear(grade.getYear() + 1);
            // 更新年级名称：例如"2024级"变为"2025级"
            String name = grade.getName();
            if (name != null && name.matches("\\d{4}级")) {
                int year = Integer.parseInt(name.substring(0, 4));
                grade.setName((year + 1) + "级");
            }
            grade.setEditTime(LocalDateTime.now());
        }
        // 批量更新
        this.updateBatchById(gradeList);
        return ids;
    }
}
