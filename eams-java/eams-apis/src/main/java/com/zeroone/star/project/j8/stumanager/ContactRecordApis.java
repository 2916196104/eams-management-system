package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j8.stumanager.AddContactRecordDTO;
import com.zeroone.star.project.vo.JsonVO;

public interface ContactRecordApis {
    JsonVO<ExtendPageDTO> getContactRecords(Long studentId, Integer page, Integer size);
    
    JsonVO<Void> addContactRecord(AddContactRecordDTO dto);
    
    JsonVO<Void> deleteContactRecord(Long id);
}