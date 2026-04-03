package com.zeroone.star.oauth2.controller;

import com.nimbusds.jose.jwk.JWKSet;
import com.nimbusds.jose.jwk.RSAKey;
import org.springframework.boot.autoconfigure.condition.ConditionalOnWebApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.security.KeyPair;
import java.security.interfaces.RSAPublicKey;
import java.util.Map;

@RestController
@ConditionalOnWebApplication
@RequestMapping("rsa")
public class KeyPairController {
    private final KeyPair keyPair;

    public KeyPairController(KeyPair keyPair) {
        this.keyPair = keyPair;
    }

    @GetMapping("public-key")
    public Map<String, Object> getPublicKey() {
        RSAPublicKey publicKey = (RSAPublicKey) keyPair.getPublic();
        RSAKey key = new RSAKey.Builder(publicKey).build();
        return new JWKSet(key).toJSONObject();
    }

    @GetMapping("private-key")
    public Map<String, Object> getPrivateKey() {
        return null;
    }
}
