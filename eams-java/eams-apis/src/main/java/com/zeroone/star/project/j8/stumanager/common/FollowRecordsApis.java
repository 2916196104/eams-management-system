package com.zeroone.star.project.j8.stumanager.common;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddFollowRecordDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.FollowRecordVO;

/**
 * 跟进记录
 */
public interface FollowRecordsApis {
    JsonVO<ExtendPageDTO<FollowRecordVO>> getFollowRecords(Long studentId, Integer page, Integer size);

    JsonVO<Void> addFollowRecord(AddFollowRecordDTO dto);

    JsonVO<Void> deleteFollowRecord(Long id);

}
