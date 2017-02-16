//
//  NSString+AES.h
//

#import "NSData+AES.h"
#import <CommonCrypto/CommonCryptor.h>
#import "NSData+AES.h"

@implementation NSString (AES)

- (NSString *)AES256EncryptWithKey:(NSString *)key {

    if ([self isEqualToString:@""]) {
        return @"";
    }
    
    __autoreleasing NSString *encryptString = nil;
    NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
    
    if (data) {
        NSData *dataOfEncrypt = [data AES256EncryptWithKey:key];
        encryptString = [dataOfEncrypt toHexString];
    }
    
    return encryptString;
}

- (NSString *)AES256DecryptWithKey:(NSString *)key {
    
    if ([self isEqualToString:@""]) {
        return @"";
    }
    
    __autoreleasing NSString *decryptString = nil;
    
    NSData *data = [NSData fromHexString:self];
    if (data) {
        NSData *dataOfDecrypt = [data AES256DecryptWithKey:key];
        decryptString = [[NSString alloc] initWithData:dataOfDecrypt encoding:NSUTF8StringEncoding];
    }
    
    return decryptString;
}



@end
