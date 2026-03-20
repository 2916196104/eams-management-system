package com.zeroone.star.academic.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.academic.mapper.ClassroomMapper;
import com.zeroone.star.academic.service.ClassroomService;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
public class ClassroomServiceImpl extends ServiceImpl<ClassroomMapper, ClassroomVO> implements ClassroomService {

    public IPage<ClassroomVO> getList(ClassroomQuery query) {
        return this.baseMapper.getList(new Page<>(query.getPageIndex(), query.getPageSize()),query);
    }

    public ClassroomVO getClassroomById(Long id) {
        ClassroomVO classroomVO = this.getById(id);
        return classroomVO;
    }
    @Transactional(rollbackFor = Exception.class)
    public Boolean save(ClassroomDTO classroomDTO) {
        ClassroomVO classroomVO = new ClassroomVO();
        BeanUtils.copyProperties(classroomDTO, classroomVO);
        if(classroomVO.getId() == null) {
            // 创建时所属学校是创建者的所属学校
            classroomVO.setSchoolId(classroomDTO.getSchoolId());
        }
        return this.saveOrUpdate(classroomVO);
    }
}