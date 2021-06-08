#include <stdlib.h>
#include <string.h>

#include "vcrypto.h"

namespace  fcpp{

vcrypto::vcrypto()
{
}

vcrypto::~vcrypto()
{
}

vstring vcrypto::Base64Encode(const vbytes&b)
{
    vuchar alphabetMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vint32 len = b.size();
    vchar*tmpBuf = new vchar[len / 3 * 4 + 10];
    memset(tmpBuf, 0, len / 3 * 4 + 10);
    vint32 encodeIndex = 0;
    vint32 i = 0;

    const vuchar*s = static_cast<const vuchar*>(b.data());
    for (encodeIndex = 0; i+3 <= len; i+=3)
    {
        tmpBuf[encodeIndex++] = alphabetMap[s[i]>>2];                             //取出第一个字符的前6位并找出对应的结果字符
        tmpBuf[encodeIndex++] = alphabetMap[((s[i]<<4)&0x30)|(s[i+1]>>4)];     //将第一个字符的后2位与第二个字符的前4位进行组合并找到对应的结果字符
        tmpBuf[encodeIndex++] = alphabetMap[((s[i+1]<<2)&0x3c)|(s[i+2]>>6)];   //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        tmpBuf[encodeIndex++] = alphabetMap[s[i+2]&0x3f];                         //取出第三个字符的后6位并找出结果字符
    }

    if (i < len)
    {
        vuint32 tail = len - i;
        if (tail == 1)
        {
            tmpBuf[encodeIndex++] = alphabetMap[s[i]>>2];
            tmpBuf[encodeIndex++] = alphabetMap[(s[i]<<4)&0x30];
            tmpBuf[encodeIndex++] = '=';
            tmpBuf[encodeIndex++] = '=';
        }
        else
        {
            tmpBuf[encodeIndex++] = alphabetMap[s[i]>>2];
            tmpBuf[encodeIndex++] = alphabetMap[((s[i]<<4)&0x30)|(s[i+1]>>4)];
            tmpBuf[encodeIndex++] = alphabetMap[(s[i+1]<<2)&0x3c];
            tmpBuf[encodeIndex++] = '=';
        }
    }
    vstring sRet(tmpBuf);
    delete[] tmpBuf;
    return sRet;
}

vstring vcrypto::Base64Encode(const vstring&s)
{
    vuchar alphabet_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vint32 textLen = static_cast<vint32>(s.length());
    vint32 base64Len = textLen / 3 * 4 + 5;
    vchar*tmpBuf = new vchar[base64Len];
    memset(tmpBuf, 0, base64Len);
    vint32 encodeIndex = 0;
    vint32 i = 0;
    for (encodeIndex = 0; i+3 <= textLen; i+=3)
    {
        tmpBuf[encodeIndex++] = alphabet_map[s[i]>>2];                             //取出第一个字符的前6位并找出对应的结果字符
        tmpBuf[encodeIndex++] = alphabet_map[((s[i]<<4)&0x30)|(s[i+1]>>4)];     //将第一个字符的后2位与第二个字符的前4位进行组合并找到对应的结果字符
        tmpBuf[encodeIndex++] = alphabet_map[((s[i+1]<<2)&0x3c)|(s[i+2]>>6)];   //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        tmpBuf[encodeIndex++] = alphabet_map[s[i+2]&0x3f];                         //取出第三个字符的后6位并找出结果字符
    }

    if (i < textLen)
    {
        vuint32 tail = textLen - i;
        if (tail == 1)
        {
            tmpBuf[encodeIndex++] = alphabet_map[s[i]>>2];
            tmpBuf[encodeIndex++] = alphabet_map[(s[i]<<4)&0x30];
            tmpBuf[encodeIndex++] = '=';
            tmpBuf[encodeIndex++] = '=';
        }
        else
        {
            tmpBuf[encodeIndex++] = alphabet_map[s[i]>>2];
            tmpBuf[encodeIndex++] = alphabet_map[((s[i]<<4)&0x30)|(s[i+1]>>4)];
            tmpBuf[encodeIndex++] = alphabet_map[(s[i+1]<<2)&0x3c];
            tmpBuf[encodeIndex++] = '=';
        }
    }
    vstring sRet(tmpBuf);
    delete[] tmpBuf;
    return sRet;
}

vbytes vcrypto::Base64Decode(const vstring&s)
{
    vuchar reverse_map[] =
    {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255, 255, 255, 255, 255,
        255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
        255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 255, 255, 255, 255
    };
    vint32 decodeIndex = 0;
    vuchar quad[4];
    vbytes byteRet;
    vint32 codeLen = static_cast<vint32>(s.length());
    byteRet.resize(codeLen / 4 * 3 + 5);
    for (vint32 i = 0; i < codeLen; i += 4) {
        for (vint32 k = 0; k < 4; k++) {
            quad[k] = reverse_map[static_cast<vint32>(s[i + k])];//分组，每组四个分别依次转换为base64表内的十进制数
        }

        byteRet[decodeIndex++] = static_cast<vuchar>(quad[0] << 2) | (quad[1] >> 4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的前2位进行组合

        if (quad[2] >= 64) {
            break;
        }
        else if (quad[3] >= 64) {
            byteRet[decodeIndex++] = static_cast<vuchar>(quad[1] << 4) | (quad[2] >> 2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应base64表的十进制数的前4位进行组合
            break;
        }
        else {
            byteRet[decodeIndex++] = static_cast<vuchar>(quad[1] << 4) | (quad[2] >> 2);
            byteRet[decodeIndex++] = static_cast<vuchar>(quad[2] << 6) | quad[3];//取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
        }
    }
    return byteRet;
}

}   //fcpp
