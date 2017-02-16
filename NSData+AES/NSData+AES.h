//
//  NSData+AES.h
//

#import <Foundation/Foundation.h>

@interface NSData (AES)

/**
 *  AES加密
 *
 *  @param key 加密的key
 */
- (NSData *)AES256EncryptWithKey:(NSString *)key;

/**
 *  AES解密
 *
 *  @param key 解密的key
 */
- (NSData *)AES256DecryptWithKey:(NSString *)key;

- (NSString *)toHexString;

+ (NSData *)fromHexString:(NSString *)hexString;

@end
