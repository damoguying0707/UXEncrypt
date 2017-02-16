//
//  UXRC4.m
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import "UXRC4.h"
#import "rc4.h"
#import "Signature.h"

@implementation UXRC4

+ (NSData *)rc4Data:(NSData *)data withKey:(NSString *)key {
    
    RC4_KEY lkey;
    unsigned char *p_key = (unsigned char *)[key cStringUsingEncoding:NSISOLatin1StringEncoding];
    RC4_set_key(&lkey, (int)[key length], p_key);
    
    unsigned char *pStrReaultEncrypt = (unsigned char *)malloc([data length]);
    RC4(&lkey, [data length], (unsigned char *)[data bytes], pStrReaultEncrypt);
    NSData *retData = [NSData dataWithBytes:pStrReaultEncrypt length:[data length]];
    free(pStrReaultEncrypt);
    
    return retData;
}

+ (NSString *)encryptRC42:(NSString *)aInput {
    
    uint8_t *epwd = calloc(1, ([aInput length]+40)*2);
    RC4_s((uint8_t*)[aInput cStringUsingEncoding:NSASCIIStringEncoding], [aInput length], epwd);
    return [NSString stringWithCString:(char*)epwd encoding:NSASCIIStringEncoding];
}

+ (NSString *)decryptRC4:(NSString *)aInput key:(NSString *)aKey {
    
    NSString *result = aInput;
    RC4_KEY key;
    unsigned char *p = NULL;
    p = (unsigned char *)[aKey cStringUsingEncoding:NSISOLatin1StringEncoding];
    RC4_set_key(&key, (int)[aKey length], p);
    const char * src2 = (const char *)[aInput cStringUsingEncoding:NSISOLatin1StringEncoding];
    int nLen = (int)[aInput length];
    unsigned char *src=[UXStringUtils hexToByte:src2];
    unsigned char *pStrReaultEncrypt = (unsigned char *)malloc(nLen/2 + 1);
    RC4(&key, nLen/2, src, pStrReaultEncrypt);
    pStrReaultEncrypt[nLen/2] = 0;
    result = [NSString stringWithCString:(char *)pStrReaultEncrypt encoding:NSISOLatin1StringEncoding];
    free(pStrReaultEncrypt);
    free(src);
    return result;
}

@end
