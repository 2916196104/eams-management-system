package com.zeroone.star.interact.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.interact.entity.Homework;
import com.zeroone.star.project.dataobject.j6.interact.HomeworkDO;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface HomeworkMapper extends BaseMapper<Homework> {

    /**
     * 分页查询作业(分页+条件)
     *
     * @param homeworkQuery
     * @return
     */
    List<HomeworkListDto> pageQuery(HomeworkQuery homeworkQuery);

    /**
     *
     * 根据id查询作业详情
     * @param id
     * @return
     */
    @Select("select id, class_id, title, content from homework where id = #{id}")
    HomeworkDetailVO selectById(Long id);
}
