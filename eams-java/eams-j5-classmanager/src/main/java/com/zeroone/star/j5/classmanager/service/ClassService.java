package com.zeroone.star.j5.classmanager.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.j5.classmanager.ClassDO;
import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import io.swagger.models.auth.In;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 班级 服务类
 * </p>
 *
 * @author 阿伟
 * @since 2026-03-19
 */

@Service
public interface ClassService extends IService<ClassDO> {
    /**
     * 保存班级
     *
     * @param classDTO 班级信息
     */

    Long saveClass(ClassDTO classDTO);

    /**
     * 批量删除班级
     *
     * @param ids 班级ID列表
     */
    Long removeClass(List<Long> ids);

    /**
     * 结束班级
     *
     * @param ids 班级ID列表
     */
    Long endClass(List<Long> ids);
     IPage<ClassListVO> queryClassPage(ClassPageQuery query);
     ClassListVO getClassDetail(Long id);

}

