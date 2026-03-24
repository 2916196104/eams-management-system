package com.zeroone.star.j1.console.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j1.console.entity.NoticeDO;
import com.zeroone.star.project.dto.j1.console.ConsoleNoticeDTO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

/**
 * <p>
 * 公告表 Mapper 接口
 * </p>
 * @author hxb
 */
@Mapper
public interface NoticeMapper extends BaseMapper<NoticeDO> {

    /**
     * 分页查询公告列表
     * @param page 分页参数
     * @param title 标题（模糊查询）
     * @return 分页结果
     */
    IPage<ConsoleNoticeDTO> selectNoticePage(
            Page<ConsoleNoticeDTO> page,
            @Param("title") String title
    );
}
