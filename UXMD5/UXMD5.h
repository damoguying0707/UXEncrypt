//
//  UXMD5.h
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UXMD5 : NSObject

/**
 *  string md5加密
 *
 *  @param str 源数据
 *
 *  @return 加密后的数据
 */
+ (NSString *)md5String:(NSString *)str;

/**
 *  data md5加密
 *
 *  @param data 源数据
 *
 *  @return 加密后的数据
 */
+ (NSString *)md5Data:(NSData *)data;

/**
 *  sha1加密
 *
 *  @param source 源数据
 *
 *  @return 加密后的数据
 */
+ (NSString *)getShaString:(NSString *)source;

@end
