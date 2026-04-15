package com.zeroone.star.academic.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.academic.entity.Classroom;
import com.zeroone.star.academic.mapper.ClassroomMapper;
import com.zeroone.star.academic.service.ClassroomService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;

@Service
public class ClassroomServiceImpl extends ServiceImpl<ClassroomMapper, Classroom> implements ClassroomService {

    @Resource
    private UserHolder userHolder;

    @Override
    public IPage<ClassroomVO> getList(ClassroomQuery query) {
        return this.baseMapper.getList(new Page<>(query.getPageIndex(), query.getPageSize()), query);
    }

    @Override
    public ClassroomVO getClassroomById(Long id) {
        Classroom classroom = this.getById(id);
        if (classroom == null) {
            throw new IllegalArgumentException("教室不存在");
        }
        ClassroomVO classroomVO = new ClassroomVO();
        BeanUtils.copyProperties(classroom, classroomVO);
        return classroomVO;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Boolean save(ClassroomDTO classroomDTO) {
        Classroom classroom = new Classroom();
        BeanUtils.copyProperties(classroomDTO, classroom);

        if (classroom.getId() != null) {
            classroom.setId(null);
        }
        Long currentUserId = null;
        try {
            if (userHolder.getCurrentUser() != null) {
                currentUserId = Long.valueOf(userHolder.getCurrentUser().getId());
            }
        } catch (Exception ignored) {
        }

        LocalDateTime now = LocalDateTime.now();

        classroom.setSchoolId(classroomDTO.getSchoolId());
        classroom.setCreator(currentUserId);
        classroom.setAddTime(now);
        classroom.setDeleted(0);

        return this.save(classroom);
    }
}