//
//  UXBase64.m
//  YouxinClient
//
//  Created by vincen.li on 16/2/16.
//  Copyright © 2016年 UXIN CO. All rights reserved.
//

#import "UXBase64.h"

@implementation UXBase64

+ (NSString *)base64EncodedStringWithString:(NSString *)plainString {
    NSData *plainData = [plainString dataUsingEncoding:NSUTF8StringEncoding];
    return [plainData base64EncodedStringWithOptions:0];
}

+ (NSData *)base64EncodedDataWithString:(NSString *)plainString {
    NSData *plainData = [plainString dataUsingEncoding:NSUTF8StringEncoding];
    return [plainData base64EncodedDataWithOptions:0];
}

+ (NSString *)stringWithBase64EncodedString:(NSString *)base64String {
    NSData *decodedData = [[NSData alloc] initWithBase64EncodedString:base64String options:0];
    return [[NSString alloc] initWithData:decodedData encoding:NSUTF8StringEncoding];
}

+ (NSData *)dataWithBase64EncodedString:(NSString *)base64String {
    return [[NSData alloc] initWithBase64EncodedString:base64String options:0];
}

@end
