package com.zeroone.star.project.components.user;

import lombok.Builder;
import lombok.Data;

import java.util.List;

@Data
@Builder
public class UserDTO {
    private String id;
    private String username;
    private Byte isEnabled;
    private List<String> roles;
    private Long orgId;
    private String terminalType;
}
