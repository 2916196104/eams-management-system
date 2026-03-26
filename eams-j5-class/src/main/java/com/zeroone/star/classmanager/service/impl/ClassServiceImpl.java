package com.zeroone.star.classmanager.service.impl;


import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.classmanager.mapper.ClassManagerMapper;
import com.zeroone.star.classmanager.service.IClassService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import org.springframework.stereotype.Service;
import com.zeroone.star.project.Do.j5.classmanager.ClassDO;

import javax.annotation.Resource;

/**
 * <p>
 * 班级 服务实现类
 * </p>
 *
 * @author 阿伟
 * @since 2026-03-19
 */
@Service
public class ClassServiceImpl extends ServiceImpl<ClassManagerMapper, ClassDO> implements IClassService {
        @Resource
        private ClassManagerMapper ClassManagerMapper;
    /**
     * 分页查询班级列表
     */
    @Override
    public IPage<ClassListVO> queryClassPage(ClassPageQuery query) {
        Page<ClassListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        return ClassManagerMapper.selectClassPage(page, query);
    }

    /**
     * 查询班级详情
     */
    public ClassListVO getClassDetail(Long id) {
        return ClassManagerMapper.selectClassDetail(id);
    }
}
