//
//  NSString+AES.h
//

#import <Foundation/Foundation.h>

@interface NSString (AES)

/**
 *  AES加密
 *
 *  @param key 加密的key
 */
- (NSString *)AES256EncryptWithKey:(NSString *)key;

/**
 *  AES解密
 *
 *  @param key 解密的key
 */
- (NSString *)AES256DecryptWithKey:(NSString *)key;

@end
