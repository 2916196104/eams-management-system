package com.zeroone.star.student.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ClassDTO;
import com.zeroone.star.project.dto.j4.student.ClassStudentDTO;

import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.query.j4.student.ClassQuery;

import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.vo.j4.student.ClassDetailVO;
import com.zeroone.star.student.entity.ClassStudentDO;
import com.zeroone.star.student.entity.ContactRecordDO;
import com.zeroone.star.student.mapper.ClassMapper;
import com.zeroone.star.student.mapper.ClassStudentMapper;
import com.zeroone.star.student.mapper.ContactRecordMapper;
import com.zeroone.star.student.service.StudentService;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
public class StudentServiceImpl implements StudentService {

    @Resource
    private ClassMapper classMapper;

    @Resource
    private ClassStudentMapper classStudentMapper;

    @Override
    public PageDTO<ClassDTO> queryClassPage(ClassQuery condition) {
        long pageIndex = condition.getPageIndex();
        long pageSize = condition.getPageSize();

        if (pageIndex < 1) pageIndex = 1;
        if (pageSize < 1) pageSize = 10;

        Page<ClassDetailVO> pageParam = new Page<>(pageIndex, pageSize);
        IPage<ClassDetailVO> resultPage = classMapper.selectClassPage(pageParam, condition);

        List<ClassDTO> dtoList = new ArrayList<>();
        List<ClassDetailVO> records = resultPage.getRecords();
        if (records != null) {
            for (ClassDetailVO vo : records) {
                dtoList.add(convertToClassDTO(vo));
            }
        }

        PageDTO<ClassDTO> pageDTO = new PageDTO<>();
        pageDTO.setRows(dtoList);
        pageDTO.setTotal(resultPage.getTotal());
        pageDTO.setPageIndex(resultPage.getCurrent());
        pageDTO.setPageSize(resultPage.getSize());
        pageDTO.setPages(resultPage.getPages());

        return pageDTO;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long joinClass(ClassStudentDTO dto) {
        if (dto.getClassId() == null) {
            throw new IllegalArgumentException("班级ID不能为空");
        }
        if (dto.getStudentId() == null) {
            throw new IllegalArgumentException("学生ID不能为空");
        }

        com.zeroone.star.student.entity.ClassDO classDO = classMapper.selectById(dto.getClassId());
        if (classDO == null || (classDO.getDeleted() != null && classDO.getDeleted() == 1)) {
            throw new RuntimeException("班级不存在");
        }

        int count = classStudentMapper.countByClassAndStudent(dto.getClassId(), dto.getStudentId());
        if (count > 0) {
            throw new RuntimeException("该学员已在班级中");
        }

        int currentCount = classStudentMapper.countByClassId(dto.getClassId());
        if (classDO.getPlannedStudentCount() != null && currentCount >= classDO.getPlannedStudentCount()) {
            throw new RuntimeException("班级人数已满");
        }

        ClassStudentDO classStudentDO = new ClassStudentDO();
        classStudentDO.setClassId(dto.getClassId());
        classStudentDO.setStudentId(dto.getStudentId());
        classStudentDO.setAddTime(LocalDateTime.now());
        classStudentDO.setCreator(dto.getStudentId());
        classStudentDO.setDeleted(0);
        classStudentDO.setConsumeCourseId(classDO.getCourseId());

        classStudentMapper.insert(classStudentDO);

        return classStudentDO.getId();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> quitClass(Long classId, Long studentId) {
        if (classId == null || studentId == null) {
            throw new IllegalArgumentException("参数不能为空");
        }

        LambdaQueryWrapper<ClassStudentDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(ClassStudentDO::getClassId, classId)
                .eq(ClassStudentDO::getStudentId, studentId)
                .eq(ClassStudentDO::getDeleted, 0);

        List<ClassStudentDO> list = classStudentMapper.selectList(queryWrapper);

        if (list == null || list.isEmpty()) {
            throw new RuntimeException("学员不在该班级中");
        }

        List<Long> deletedIds = new ArrayList<>();
        for (ClassStudentDO record : list) {
            record.setDeleted(1);
            classStudentMapper.updateById(record);
            deletedIds.add(record.getId());
        }

        return deletedIds;
    }

    private ClassDTO convertToClassDTO(ClassDetailVO vo) {
        ClassDTO dto = new ClassDTO();
        BeanUtils.copyProperties(vo, dto);
        if (vo.getPlannedStudentCount() != null) {
            dto.setMaxStudentCount(vo.getPlannedStudentCount());
        }
        return dto;
    }
    @Resource
    private ContactRecordMapper contactRecordMapper;

    @Override
    public PageDTO<FollowUpDTO> queryFollowUpPage(FollowUpQuery condition) {
        // 1. 创建分页参数对象
        Page<FollowUpDTO> pageParam = new Page<>(condition.getPageIndex(), condition.getPageSize());

        // 2. 执行查询，返回 IPage
        IPage<FollowUpDTO> iPage = contactRecordMapper.selectFollowUpPage(pageParam, condition);

        // 3. 强转并转换成 PageDTO
        return PageDTO.create((Page<FollowUpDTO>) iPage);
    }

    @Override
    @Transactional
    public Long saveFollowUp(FollowUpDTO dto) {
        ContactRecordDO recordDO = new ContactRecordDO();
        BeanUtil.copyProperties(dto, recordDO); // 使用文档提到的 BeanUtil

        if (dto.getId() == null) {
            recordDO.setAddTime(LocalDateTime.now());
            contactRecordMapper.insert(recordDO);
        } else {
            contactRecordMapper.updateById(recordDO);
        }
        return recordDO.getId();
    }

    @Override
    public Long removeFollowUp(Long id) {
        contactRecordMapper.deleteById(id);
        return id;
    }

    @Override
    public FollowUpDTO getFollowUpDetail(Long id) {
        ContactRecordDO recordDO = contactRecordMapper.selectById(id);
        if (recordDO == null) return null;
        FollowUpDTO dto = new FollowUpDTO();
        BeanUtil.copyProperties(recordDO, dto);
        return dto;
    }
}
