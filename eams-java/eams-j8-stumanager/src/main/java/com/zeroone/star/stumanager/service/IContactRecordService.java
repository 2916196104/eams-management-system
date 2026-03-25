package com.zeroone.star.stumanager.service;

import com.zeroone.star.stumanager.entity.ContactRecord;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddFollowRecordDTO;
import com.zeroone.star.project.vo.j8.stumanager.FollowRecordVO;

import java.util.List;

/**
 * <p>
 * 学员跟进表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IContactRecordService extends IService<ContactRecord> {
    ExtendPageDTO<FollowRecordVO> getFollowRecords(Long studentId, Integer page, Integer size);
    Boolean addFollowRecord(AddFollowRecordDTO dto);
    Boolean deleteFollowRecord(Long id);
}

