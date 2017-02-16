//
//  UXBase64.h
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UXBase64 : NSObject

/**
 *  Base64 编码字符串
 *
 *  @param plainString 待编码明文字符串
 *
 *  @return 编码后的字符串
 */
+ (NSString *)base64EncodedStringWithString:(NSString *)plainString;

/**
 *  Base64 编码字符串成
 *
 *  @param plainString 待编码明文字符串
 *
 *  @return 编码后的数据
 */
+ (NSString *)base64EncodedDataWithString:(NSString *)plainString;

/**
 *  Base64 解码字符串
 *
 *  @param base64String 已编码 Base64 字符串
 *
 *  @return 解码后的明文字符串
 */
+ (NSString *)stringWithBase64EncodedString:(NSString *)base64String;

/**
 *  Base64 解码字符串
 *
 *  @param base64String 已编码的 Base64 字符串
 *
 *  @return 解码后的明文数据
 */
+ (NSData *)dataWithBase64EncodedString:(NSString *)base64String;

@end
