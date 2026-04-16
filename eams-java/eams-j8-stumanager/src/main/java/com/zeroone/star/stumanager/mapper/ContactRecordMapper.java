package com.zeroone.star.stumanager.mapper;

import com.zeroone.star.stumanager.entity.ContactRecord;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 学员跟进表 Mapper 接口
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Mapper
public interface ContactRecordMapper extends BaseMapper<ContactRecord> {
    List<ContactRecord> selectByStudentId(@Param("studentId") Long studentId);
}

