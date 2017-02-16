//
//  UXRC4.h
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UXRC4 : NSObject

/**
 *  对data进行rc4加密
 *
 *  @param data 源data
 *  @param key  加密的key
 *
 *  @return 加密后的data
 */
+ (NSData *)rc4Data:(NSData *)data withKey:(NSString *)key;

/**
 *  RC4加密
 */
+ (NSString *)encryptRC42:(NSString *)aInput;

/**
 *  RC4解密
 */
+ (NSString *)decryptRC4:(NSString *)aInput key:(NSString *)aKey;

@end
