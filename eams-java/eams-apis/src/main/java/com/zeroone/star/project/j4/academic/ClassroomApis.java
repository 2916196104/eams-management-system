package com.zeroone.star.project.j4.academic;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import org.springframework.web.bind.annotation.PathVariable;

import java.util.List;

/**
 * <p>
 * 描述：教室接口声明
 * </p>
 * @author ab
 */
public interface ClassroomApis {
    /**
     * 分页查询教室信息
     * @param query 教室查询参数
     * @return 教室列表
     */
    JsonVO<PageDTO<ClassroomVO>> queryClassroom(ClassroomQuery query);

    /**
     * 根据ID查询教室信息
     * @param id 教室ID
     * @return 教室信息
     */
    JsonVO<ClassroomVO> getClassroomById(@PathVariable Long id);

    /**
     * 保存教室信息
     * @param classroomDTO 教室信息
     * @return 保存结果
     */
    JsonVO<Long> saveClassroom(ClassroomDTO classroomDTO);
    /**
     * 批量删除教室信息
     * @param ids 教室ID列表
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteClassroom(List<Long> ids);
}
