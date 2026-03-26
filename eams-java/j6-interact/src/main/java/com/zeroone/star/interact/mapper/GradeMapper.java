package com.zeroone.star.interact.mapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dataobject.j6.interact.GradeDO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
@Mapper
public interface GradeMapper extends BaseMapper<GradeDO> {
    IPage<GradeFormDTO> queryForm(Page<GradeFormDTO> page,
                                  @Param("title") String title,
                                  @Param("creator") Long creator);
}