#include "Signature.h"
#include <stdlib.h>
#include <time.h>
#include "rc4.h"
#include <CommonCrypto/CommonCrypto.h>
#include <stdio.h>


#pragma mark - 常量定义
#define KEY					"1a81160d06119b64f3ee64003f3cab4d8d9e5132244940137d2f013c1107008f"
#define KEY_SIZE			(sizeof(KEY)-1)
#define KEYT				"1122334455667788"
#define KEYT_SIZE			(sizeof(KEYT)-1)

#define RC4_MAIN_KEY		"asdfgh"
#define RC4_MAIN_KEY_SIZE	(sizeof(RC4_MAIN_KEY)-1)
#define RC4_KEY1			"uxin!@#2015wrong"
#define RC4_KEY1_SIZE		(sizeof(RC4_KEY1)-1)
#define RC4_KEY2			"echo!@#2015suvbh"
#define RC4_KEY2_SIZE		(sizeof(RC4_KEY2)-1)

#define SN_SIZE				16


#pragma mark - SHA1Binary2Hex And SHA1Hex2Binary
unsigned char alphaList[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void SHA1Binary2Hex(unsigned char* pSrc, unsigned long nSrcLen, unsigned char* pDest, unsigned long nDestLen) {
    unsigned long nIndex = 0;
    
    if (pSrc == NULL || pDest == NULL || (nSrcLen * 2) > nDestLen) {
        return;
    }
    
    for (; nIndex < nSrcLen; ++nIndex) {
        unsigned char cHigh = alphaList[(unsigned char)((pSrc[nIndex] >> 4))];
        unsigned char cLow = alphaList[(unsigned char)((pSrc[nIndex] & 0x0F))];
        
        pDest[nIndex * 2] = cHigh;
        pDest[nIndex * 2 + 1] = cLow;
    }
}

void SHA1Hex2Binary(const unsigned char* pSrc, const unsigned long nSrcLen, unsigned char* pDest, unsigned long nDestLen) {
    unsigned long nIndex = 0;
    
    if (pSrc == NULL || pDest == NULL || (nDestLen * 2) < nSrcLen) {
        return;
    }
    
    for (; nIndex < nSrcLen; ++nIndex) {
        if (nIndex % 2) {
            unsigned char cLow = (pSrc[nIndex] >= '0' && pSrc[nIndex] <= '9') ? (unsigned char)pSrc[nIndex] - '0' : (unsigned char)pSrc[nIndex] - 'a' + 10;
            pDest[nIndex / 2] |= cLow;
        } else {
            unsigned char cHigh = (pSrc[nIndex] >= '0' && pSrc[nIndex] <= '9') ? (unsigned char)pSrc[nIndex] - '0' : (unsigned char)pSrc[nIndex] - 'a' + 10;
            pDest[nIndex / 2] = cHigh;
            pDest[nIndex / 2] <<= 4;
        }
    }
}

#pragma mark - 加解密
char alphaMap[10] = {'d','e','y','b','i','p','v','k','z','o'};

// Get the real unencrypted key
void GetRealKey(unsigned char* pKey) {
    // Get unencrypted key
    RC4_KEY rc4Key;
    
    unsigned char* pKeyBinary = (unsigned char*)malloc(KEY_SIZE / 2 + 1);
    memset(pKeyBinary, 0, KEY_SIZE / 2 + 1);
    
    SHA1Hex2Binary((const unsigned char *)KEY, KEY_SIZE, pKeyBinary, KEY_SIZE / 2 + 1);
    
    RC4_set_key(&rc4Key, KEYT_SIZE, (const unsigned char *)KEYT);
    RC4(&rc4Key, KEY_SIZE / 2, pKeyBinary, pKey);
    
    free(pKeyBinary);
    pKeyBinary = NULL;
}

//************************************
// Method:    Get the signature of the input data
// FullName:  Signature
// Returns:   void
// Qualifier: public
// Parameter: const unsigned char*
//				[IN] The data pointer to be signed
//			  const unsigned long
//				[IN] The data length
//			  unsigned char*
//				[OUT] The signature output (PS: The length of pSignature must be greater than 40 and set to 0)
//************************************
void Signature(const unsigned char* pData, const unsigned long nDataLen, unsigned char* pSignature) {
    CC_SHA1_CTX context;
    unsigned char digest[20] = {0};
    
    unsigned char* pKey = (unsigned char*)malloc(KEY_SIZE + 1);
    unsigned char* pBuffer = (unsigned char*)malloc(nDataLen + KEY_SIZE + 1);
    
    if (pData == NULL || pSignature == NULL || nDataLen == 0) {
        free(pKey);
        free(pBuffer);
        
        pKey = NULL;
        pBuffer = NULL;
        
        return;
    }
    
    memset(pKey, 0, KEY_SIZE + 1);
    
    GetRealKey(pKey);
    
    memset(pBuffer, 0, nDataLen + KEY_SIZE / 2 + 1);
    memcpy(pBuffer, pData, nDataLen);
    memcpy(pBuffer + nDataLen, pKey, KEY_SIZE / 2);
    
    CC_SHA1_Init(&context);
    CC_SHA1_Update(&context, pBuffer, (CC_LONG)(nDataLen + KEY_SIZE / 2));
    CC_SHA1_Final(digest, &context);
    
    SHA1Binary2Hex(digest, 20, pSignature, 40);
    
    free(pKey);
    free(pBuffer);
    
    pKey = NULL;
    pBuffer = NULL;
}

//************************************
// Method:    Encrypt data using enhanced RC4 algorithm
// FullName:  RC4_s
// Returns:   void
// Qualifier: public
// Parameter: const unsigned char*
//				[IN] The data pointer to be encrypted
//			  const unsigned long
//				[IN] The data length
//			  unsigned char*
//				[OUT] The encrypted data output (PS: The length of pEncrypted should be greater than (nDataLen + RC4_MAIN_KEY_SIZE + SN_SIZE) * 2)
//************************************
void RC4_s(const unsigned char* pData, const unsigned long nDataLen, unsigned char* pEncrypted) {
    RC4_KEY rc4Key;
    unsigned long nSN = 0;
    
    unsigned char pTemp[SN_SIZE] = {0};
    unsigned char* pDataEncrypted1 = (unsigned char*)malloc(nDataLen);
    unsigned char* pDataEncrypted2 = (unsigned char*)malloc(nDataLen + RC4_MAIN_KEY_SIZE + SN_SIZE);
    unsigned char* pDataEncryptedFinal = (unsigned char*)malloc(nDataLen + RC4_MAIN_KEY_SIZE + SN_SIZE);
    
    memset(pDataEncrypted1, 0, nDataLen);
    memset(pDataEncrypted2, 0, nDataLen + RC4_MAIN_KEY_SIZE + SN_SIZE);
    memset(pDataEncryptedFinal, 0, nDataLen + RC4_MAIN_KEY_SIZE + SN_SIZE);
    
    if (pData == NULL || pEncrypted == NULL || nDataLen == 0) {
        free(pDataEncrypted1);
        free(pDataEncrypted2);
        free(pDataEncryptedFinal);
        
        pDataEncrypted1 = NULL;
        pDataEncrypted2 = NULL;
        pDataEncryptedFinal = NULL;
        
        return;
    }
    
    //Get SN
    nSN = rand() % 0x7FFFFFFF;
    
    sprintf(pTemp, "%d", nSN);
    
    //Get Data Encrypted 1 data encrypted = RC4(data, key1)
    RC4_set_key(&rc4Key, RC4_KEY1_SIZE, RC4_KEY1);
    RC4(&rc4Key, nDataLen, pData, pDataEncrypted1);
    
    //Get Data Encrypted 2 final encrypted = RC4(data encrypted + main key + SN, key2)
    memcpy(pDataEncrypted2, pDataEncrypted1, nDataLen);
    memcpy(pDataEncrypted2 + nDataLen, RC4_MAIN_KEY, RC4_MAIN_KEY_SIZE);
    memcpy(pDataEncrypted2 + nDataLen + RC4_MAIN_KEY_SIZE, pTemp, strlen(pTemp));
    
    RC4_set_key(&rc4Key, RC4_KEY2_SIZE, RC4_KEY2);
    RC4(&rc4Key, nDataLen + RC4_MAIN_KEY_SIZE + strlen(pTemp), pDataEncrypted2, pDataEncryptedFinal);
    
    SHA1Binary2Hex(pDataEncryptedFinal, nDataLen + RC4_MAIN_KEY_SIZE + strlen(pTemp), pEncrypted, (nDataLen + RC4_MAIN_KEY_SIZE + strlen(pTemp)) * 2);
    
    free(pDataEncrypted1);
    free(pDataEncrypted2);
    free(pDataEncryptedFinal);
    
    pDataEncrypted1 = NULL;
    pDataEncrypted2 = NULL;
    pDataEncryptedFinal = NULL;
}