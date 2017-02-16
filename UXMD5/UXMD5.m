//
//  UXMD5.m
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import "UXMD5.h"

#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonDigest.h>

@implementation UXMD5

+ (NSString *)md5String:(NSString *)str {
    
    const char *cStr = [str UTF8String];
    
    if (cStr == NULL) {
        
        return @"";
    }
    
    unsigned char result[16];
    CC_MD5(cStr, (CC_LONG)strlen(cStr), result);
    
    return [[NSString stringWithFormat:
             @"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
             result[0], result[1], result[2], result[3],
             result[4], result[5], result[6], result[7],
             result[8], result[9], result[10], result[11],
             result[12], result[13], result[14], result[15]
             ] lowercaseString];
}

+ (NSString *)md5Data:(NSData *)data {
    
    unsigned char result[16];
    CC_MD5(data.bytes, (CC_LONG)data.length, result ); // This is the md5 call
    
    return [[NSString stringWithFormat:
             @"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
             result[0], result[1], result[2], result[3],
             result[4], result[5], result[6], result[7],
             result[8], result[9], result[10], result[11],
             result[12], result[13], result[14], result[15]
             ] lowercaseString];
}

+ (NSString *)getShaString:(NSString *)source {
    
    assert(source != nil);
    
    const char *cstr = [source UTF8String];
    //使用对应的CC_SHA1,CC_SHA256,CC_SHA384,CC_SHA512的长度分别是20,32,48,64
    unsigned char digest[CC_SHA1_DIGEST_LENGTH];
    //使用对应的CC_SHA256,CC_SHA384,CC_SHA512
    CC_SHA1(cstr,  (CC_LONG)strlen(cstr), digest);
    NSMutableString* result = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++) {
        [result appendFormat:@"%02x", digest[i]];
    }
    
    return result;
}

@end
