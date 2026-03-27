package com.zeroone.star.student.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.vo.j4.student.FollowUpVO;
import com.zeroone.star.student.entity.ContactRecordDO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ContactRecordMapper extends BaseMapper<ContactRecordDO> {
    /**
     * 分页查询跟进记录，关联学生表获取姓名 [cite: 1613, 1651]
     */

    IPage<FollowUpVO> selectFollowUpPage(Page<?> page, @Param("condition") FollowUpQuery condition);
}