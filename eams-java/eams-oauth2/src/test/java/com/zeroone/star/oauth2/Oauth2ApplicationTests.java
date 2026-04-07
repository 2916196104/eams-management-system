package com.zeroone.star.oauth2;

import org.junit.jupiter.api.Test;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;

import static org.junit.jupiter.api.Assertions.assertTrue;

class Oauth2ApplicationTests {
    private final PasswordEncoder passwordEncoder = new BCryptPasswordEncoder();

    @Test
    void passwordEncoderCanRoundTripPassword() {
        String encodedPassword = passwordEncoder.encode("123456");
        assertTrue(passwordEncoder.matches("123456", encodedPassword));
    }
}
