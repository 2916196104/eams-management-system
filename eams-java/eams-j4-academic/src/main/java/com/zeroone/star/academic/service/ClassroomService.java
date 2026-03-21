package com.zeroone.star.academic.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.academic.entity.Classroom;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;

/**
 * 教室管理业务接口
 */
public interface ClassroomService extends IService<Classroom> {
    /**
     * 分页查询教室
     * @param query 查询条件
     * @return 分页结果
     */
    IPage<ClassroomVO> getList(ClassroomQuery query);

    /**
     * 根据ID查询教室
     * @param id 教室ID
     * @return 教室详情
     */
    ClassroomVO getClassroomById(Long id);

    /**
     * 保存教室
     * @param classroomDTO 教室信息
     * @return 教室ID
     */
    Boolean save(ClassroomDTO classroomDTO);
}
