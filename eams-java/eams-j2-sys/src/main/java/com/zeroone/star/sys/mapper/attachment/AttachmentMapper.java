package com.zeroone.star.sys.mapper.attachment;

import com.zeroone.star.project.query.j2.sys.attachment.AttachmentQuery;
import com.zeroone.star.sys.entity.attachment.Attachment;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 附件管理表 Mapper 接口
 * </p>
 *
 * @author dapeng
 * @since 2026-03-21
 */
@Mapper
public interface AttachmentMapper extends BaseMapper<Attachment> {

}
