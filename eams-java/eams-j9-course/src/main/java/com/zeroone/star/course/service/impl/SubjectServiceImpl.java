package com.zeroone.star.course.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.course.entity.SubjectDO;
import com.zeroone.star.course.mapper.SubjectMapper;
import com.zeroone.star.course.service.ISubjectService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.subject.SubjectDTO;
import com.zeroone.star.project.query.j9.subject.SubjectQuery;
import com.zeroone.star.project.vo.j9.subject.SubjectNameVO;
import com.zeroone.star.project.vo.j9.subject.SubjectVO;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class SubjectServiceImpl extends ServiceImpl<SubjectMapper, SubjectDO> implements ISubjectService {
    @Override
    public List<SubjectNameVO> listSubjectNames() {
        LambdaQueryWrapper<SubjectDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.select(SubjectDO::getId,SubjectDO::getName)
                .orderByDesc(SubjectDO::getSortNum);
        List<SubjectDO> list = baseMapper.selectList(wrapper);

        return list.stream().map(item -> {
            SubjectNameVO vo = new SubjectNameVO();
            vo.setId(item.getId());
            vo.setSubjectName(item.getName());
            return vo;
        }).collect(Collectors.toList());
    }

    @Override
    public PageDTO<SubjectVO> listSubjectPage(SubjectQuery condition) {
        LambdaQueryWrapper<SubjectDO> wrapper = new LambdaQueryWrapper<>();
        if(condition.getSubjectName() != null && !condition.getSubjectName().isEmpty()){
            wrapper.like(SubjectDO::getName,condition.getSubjectName());
        }
        wrapper.orderByDesc(SubjectDO::getSortNum);

        Page<SubjectDO> page = new Page<>(condition.getPageIndex(),condition.getPageSize());
        baseMapper.selectPage(page,wrapper);

        List<SubjectVO> voList = page.getRecords().stream().map(item -> {
            SubjectVO vo = new SubjectVO();
            vo.setId(item.getId());
            vo.setSubjectName(item.getName());
            vo.setSortNum(item.getSortNum());
            vo.setInfo(item.getInfo());
            return vo;
        }).collect(Collectors.toList());

        PageDTO<SubjectVO> result = new PageDTO<>();
        result.setPageIndex(page.getCurrent());
        result.setPageSize(page.getSize());
        result.setTotal(page.getTotal());
        result.setPages(page.getPages());
        result.setRows(voList);
        return result;
    }

    @Override
    public Long saveSubject(SubjectDTO subjectDTO) {
        LocalDateTime now = LocalDateTime.now();

        SubjectDO subjectDO = new SubjectDO();
        BeanUtil.copyProperties(subjectDTO,subjectDO);

        if(subjectDTO.getId() == null){
            subjectDO.setAddTime(now);
            subjectDO.setEditTime(now);
            baseMapper.insert(subjectDO);
        }else{
            subjectDO.setEditTime(now);
            int rows = baseMapper.updateById(subjectDO);
            if(rows == 0){
                throw new RuntimeException("科目不存在，id：" + subjectDTO.getId());
            }
        }
        return subjectDO.getId();
    }

    @Override
    public boolean removeSubjects(List<Long> ids) {
        return baseMapper.deleteBatchIds(ids) > 0;
    }
}
