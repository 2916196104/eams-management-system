package com.zeroone.star.academic.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;

import java.util.List;

/**
 * 教室管理业务接口
 */
public interface ClassroomService {
    /**
     * 分页查询教室
     * @param query 查询条件
     * @return 分页结果
     */
    PageDTO<ClassroomVO> getList(ClassroomQuery query);

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
    Long save(ClassroomDTO classroomDTO);

    /**
     * 删除教室
     * @param ids 教室ID列表
     * @return 删除的教室ID列表
     */
    List<Long> delete(List<Long> ids);
}
