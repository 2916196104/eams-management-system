package com.zeroone.star.j7.interaction.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j7.interaction.GradeDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeRecordSaveDTO;
import com.zeroone.star.project.entity.Grade;
import com.zeroone.star.project.entity.GradeRecord;
import com.zeroone.star.project.query.j7.interaction.GradeQuery;
import com.zeroone.star.project.query.j7.interaction.GradeRecordQuery;
import com.zeroone.star.project.vo.j7.interaction.GradeRecordVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface GradeRecordMapper extends BaseMapper<GradeRecord> {

    /**
     * 分页查询成绩列表
     * @param page 分页对象
     * @param query 查询条件
     * @return 成绩VO分页结果
     */
    IPage<GradeRecordVO> selectGradeList(Page<?> page, @Param("query") GradeRecordQuery query);

    /**
     * 保存或更新成绩记录
     * @param entity 成绩记录实体
     * @return 操作影响的行数
     */
    int saveOrUpdateGradeRecord(@Param("entity") GradeRecord entity);

    /**
     * 根据ID列表删除成绩记录
     * @param ids 成绩记录ID列表
     * @return 删除数量
     */
    int deleteGradeRecords(@Param("ids") java.util.List<Long> ids);

    /**
     * 分页查询考核项列表
     * @param page 分页对象
     * @param query 查询条件
     * @return 考核项分页结果
     */
    IPage<Grade> selectGradePage(Page<?> page, @Param("query") GradeQuery query);
}
