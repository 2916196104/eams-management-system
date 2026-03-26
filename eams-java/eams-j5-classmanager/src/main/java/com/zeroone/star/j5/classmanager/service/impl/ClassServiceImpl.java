package com.zeroone.star.j5.classmanager.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.classmanager.mapper.ClassMapper;
import com.zeroone.star.j5.classmanager.service.ClassService;
import com.zeroone.star.project.DO.j5.classmanager.ClassDO;
import com.zeroone.star.project.dto.j5.classmanager.ClassDTO;
import com.zeroone.star.project.query.j5.classmanager.ClassPageQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.List;

@Service
public class ClassServiceImpl extends ServiceImpl<ClassMapper, ClassDO> implements ClassService {
    @Resource
    private ClassMapper classMapper;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveClass(ClassDTO classDTO) {
        ClassDO classDO = new ClassDO();

        BeanUtils.copyProperties(classDTO,classDO);

        int insert = classMapper.insert(classDO);
        return (long) insert;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long removeClass(List<Long> ids) {
        int delete = classMapper.deleteBatchIds(ids);
        return (long) delete;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long endClass(List<Long> ids) {
        QueryWrapper<ClassDO> classDOQueryWrapper = new QueryWrapper<>();
        classDOQueryWrapper.in("id", ids);

        ClassDO classDO = new ClassDO();
        classDO.setBeOver(1);  // 设置班级为完结状态

        int update = classMapper.update(classDO, classDOQueryWrapper);
        return (long) update;
    }

    /**
     * 分页查询班级列表
     */
    @Override
    public IPage<ClassListVO> queryClassPage(ClassPageQuery query) {
        Page<ClassListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        return classMapper.selectClassPage(page, query);
    }

    /**
     * 查询班级详情
     */
    public ClassListVO getClassDetail(Long id) {
        return classMapper.selectClassDetail(id);
    }

}
