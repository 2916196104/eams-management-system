package com.zeroone.star.interact.service.impl;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.mapper.GradeMapper;
import com.zeroone.star.interact.service.IGradeService;
import com.zeroone.star.project.dataobject.j6.interact.GradeDO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import org.springframework.stereotype.Service;
import com.zeroone.star.project.dto.PageDTO;
import javax.annotation.Resource;
@Service
public class GradeServiceImpl extends ServiceImpl<GradeMapper, GradeDO> implements IGradeService {
    @Resource
    private GradeMapper gradeMapper;
    /**
     * 获取成绩单列表（条件+分页）
     * @param condition 查询条件
     * @return
     */
    @Override
    public PageDTO<GradeFormDTO> queryForm(GradeFormQuery condition) {
        //1.构建分页对象
        Page<GradeFormDTO> page=new Page<>(condition.getPageIndex(),condition.getPageSize());
        //2.自定义SQL查询
        IPage<GradeFormDTO> result=gradeMapper.queryForm(page,condition.getTitle(),condition.getCreator());
        //3.转换为PageDTO
        return PageDTO.create((Page<GradeFormDTO>) result);
    }
}