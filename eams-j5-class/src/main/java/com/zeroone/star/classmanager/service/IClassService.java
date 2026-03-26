package com.zeroone.star.classmanager.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.Do.j5.classmanager.ClassDO;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;

/**
 * <p>
 * 班级 服务类
 * </p>
 *
 * @author 阿伟
 * @since 2026-03-19
 */
public interface IClassService extends IService<ClassDO> {
    public IPage<ClassListVO> queryClassPage(ClassPageQuery query);
    public ClassListVO getClassDetail(Long id);
}
