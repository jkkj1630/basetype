#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vbasisalgor.h"
#include "vbasistime.h"
#include "vstring.h"
#include "vcrypto.h"

namespace  fcpp{

vstring::vstring()
{
}

vint32 vstring::vstrlen(const vchar*s)
{
    vint32 size = 0;
    while(s[size])
    {
        ++size;
    }
    return size;
}

vstring vstring::fromFormat(const vchar*__restrict fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vbytes bstr;
    int len = vsnprintf(nullptr, 0, fmt, args);
    if(len) {
        bstr.resize(len + 1);
    }
    vsprintf(static_cast<vchar*>(bstr.data()), fmt, args);
    va_end(args);
    return vstring(static_cast<vchar*>(bstr.data()));
}

vstring vstring::fromNum(const vint32 n)
{
    return fromFormat("%d", n);
}

vstring vstring::randomStr(vint32 len)
{
    vstring random;
    for (int i = 0;i < len;i++) {
        int randomType = vcurNs() & 2;
        if(randomType == 0) {
            random += static_cast<vchar>((vcurNs() & 25) + 'a');
        }
        else if(randomType == 1) {
            random += static_cast<vchar>((vcurNs() & 25) + 'A');
        }
        else {
            random += static_cast<vchar>((vcurNs() & 9) + '0');
        }
    }
    return random;
}

bool vstring::vstrLess(const vchar *s1, const vchar *s2)
{
    vint32 diff = 0;
    while (*s1 && *s2) {
        diff = (*s1 - *s2);
        if(diff < 0)
        {
            return true;
        }
        else if(diff > 0)
        {
            return false;
        }
        s1++;
        s2++;
    }
    return false;
}

vstringvec vstring::split(const vchar*sep) const
{
    return split(vstring(sep));
}

vstringvec vstring::split(const vstring&sep) const
{
    size_type sepLen = sep.length();
    vstringvec vecSplited;
    const vchar*ptr = data();
    vstring tmp;
    while (*ptr != 0) {
        if(*ptr == sep[0])
        {
            bool bSame = true;
            for (size_type i = 0; i < sepLen; i++) {
                if(ptr[i] != sep[i])
                {
                    bSame = false;
                    break;
                }
            }
            if(bSame)
            {
                if(tmp.length())
                {
                    vecSplited.push_back(tmp);
                    tmp.empty();
                }
                ptr += sepLen;
                continue;
            }
        }
        tmp += *ptr;
        ptr++;
    }
    if(tmp.length())
    {
        vecSplited.push_back(tmp);
    }
    return vecSplited;
}

bool vstring::isEmpty()
{
    return empty();
}

vstring& vstring::toUpper()
{
    vchar*pstr = data();
    size_type len = length();
    for(size_type i = 0; i < len; ++i)
    {
        if(pstr[i] > 0x60 && pstr[i] < 0x7B)
        {
            pstr[i] -= 0x20;
        }
    }
    return *this;
}

vstring& vstring::toLower()
{
    vchar*pstr = data();
    size_type len = length();
    for(size_type i = 0; i < len; ++i)
    {
        if(pstr[i] > 0x40 && pstr[i] < 0x5B)
        {
            pstr[i] += 0x20;
        }
    }
    return *this;
}

vint32 vstring::toNum()
{
    int sign = 1, tmp = 0, i = 0;

    const vchar*pstr = data();
     while(pstr[i] == ' ')
     {
         ++i;    //1.忽略前导空格
     }

     if(pstr[i] == '+' || pstr[i] == '-')    //2.确定正负号
     {
         sign = 1 - 2 * (pstr[i++] == '-');    //s[i]为+的话sign依旧为1，为-的话sign为-1
     }

     while(pstr[i] >= '0' && pstr[i] <= '9')   //3.检查输入是否合法
     {
         if(tmp > MAX_INT32 / 10 || (tmp == MAX_INT32 / 10 && pstr[i] - '0' > 7))    //4.是否溢出
         {
             return sign == 1 ? MAX_INT32 : MIN_INT32;
         }
         tmp = tmp * 10 + (pstr[i++] - '0');    //5.不加括号有溢出风险
     }
     return tmp * sign;
}

vfloat32 vstring::toFloat32()
{
    const vchar*s = data();
    vdouble64 tf;
    vint32 nc,i,neg;

    tf = 0.0;
    if (s[0] == '-') {
        neg = 1;
    }
    else {
        neg = 0;
    }
    /* search for decimal point */
    for (nc=neg;( isdigit(s[nc]) && (s[nc] != '.') && (s[nc] != '\0')); nc++) ;

    for (i=neg; ( (isdigit(s[i]) || (s[i] == '.')) && (s[i] != '\0') ) ;i++)
    {
        /* printf("%c %d %lf\n",s[i],nc-i,tf); */
        switch((nc-i))
        {
            case 0:break;
            case 1:tf += (s[i] - '0');  break;
            case 2:tf += (s[i] - '0') * 10; break;
            case 3:tf += (s[i] - '0') * 100; break;
            case 4:tf += (s[i] - '0') * 1000; break;
            case 5:tf += (s[i] - '0') * 10000; break;
            case 6:tf += (s[i] - '0') * 100000; break;
            case 7:tf += (s[i] - '0') * 1000000; break;
            case 8:tf += (s[i] - '0') * 10000000; break;
            case 9:tf += (s[i] - '0') * 100000000.0; break;
            case 10:tf += (s[i] - '0') * 1000000000.0; break;
            case 11:tf += (s[i] - '0') * 10000000000.0;  break;
            case 12:tf += (s[i] - '0') * 100000000000.0; break;
            case 13:tf += (s[i] - '0') * 1000000000000.0; break;
            case 14:tf += (s[i] - '0') * 10000000000000.0; break;
            case 15:tf += (s[i] - '0') * 100000000000000.0; break;
            case 16:tf += (s[i] - '0') * 1000000000000000.0; break;
            case 17:tf += (s[i] - '0') * 10000000000000000.0; break;
            case 18:tf += (s[i] - '0') * 100000000000000000.0; break;
            case 19:tf += (s[i] - '0') * 1000000000000000000.0; break;
            case -1:tf += (s[i] - '0') * 0.1; break;
            case -2:tf += (s[i] - '0') * 0.01; break;
            case -3:tf += (s[i] - '0') * 0.001; break;
            case -4:tf += (s[i] - '0') * 0.0001; break;
            case -5:tf += (s[i] - '0') * 0.00001; break;
            case -6:tf += (s[i] - '0') * 0.000001; break;
            case -7:tf += (s[i] - '0') * 0.0000001; break;
            case -8:tf += (s[i] - '0') * 0.00000001; break;
            case -9:tf += (s[i] - '0') * 0.000000001; break;
            case -10:tf += (s[i] - '0') * 0.0000000001; break;
            case -11:tf += (s[i] - '0') * 0.00000000001; break;
            case -12:tf += (s[i] - '0') * 0.000000000001; break;
            case -13:tf += (s[i] - '0') * 0.0000000000001; break;
            case -14:tf += (s[i] - '0') * 0.00000000000001; break;
            case -15:tf += (s[i] - '0') * 0.000000000000001; break;
            case -16:tf += (s[i] - '0') * 0.0000000000000001; break;
            case -17:tf += (s[i] - '0') * 0.00000000000000001; break;
            case -18:tf += (s[i] - '0') * 0.000000000000000001; break;
            case -19:tf += (s[i] - '0') * 0.0000000000000000001; break;
            default : break;
        }
    }
    if (neg) {
        tf *= -1.0;
    }
    return static_cast<float>(tf);
}

vstring vstring::toBase64()
{
    return vcrypto::Base64Encode(*this);
}

bool vstring::endWith(const vchar&ch) const
{
    return data()[length() - 1] == ch;
}

bool vstring::startWith(const vchar&ch) const
{
    return data()[0] == ch;
}

bool vstring::startWith(const vchar*s) const
{
    size_type index = 0;
    size_type len1 = length();
    size_type len2 = vstrlen(s);
    while (1) {
        if(index < len2) {
            if(index < len1) {
                if(data()[index] != s[index]) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else
        {
            return true;
        }
        ++index;
    }
}

bool vstring::startWith(const vstring&s) const
{
    return startWith(s.data());
}

vstring& vstring::remove(size_type start, size_type len)
{
    erase(start, start + len);
    return *this;
}

vstring& vstring::remove(const vchar&ch)
{
    size_type index = 0;
    while ((index = find(ch, index)) != npos) {
        erase(index, 1);
    }
    return *this;
}

vstring& vstring::remove(const vchar*s)
{
    int len = vstrlen(s);
    size_type index = 0;
    while ((index = find(s, index)) != npos) {
        remove(index, len);
    }
    return *this;
}

vstring& vstring::remove(const vstring&s)
{
    return remove(s.data());
}

vstring& vstring::format(const vchar*__restrict fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = std::vsnprintf(nullptr, 0, fmt, args);
    if(len) {
        resize(len + 1);
    }
    vsprintf(data(), fmt, args);
    va_end(args);
    return *this;
}

vstring& vstring::replace(const vchar*s1, size_type len1, const vchar*s2)
{
    size_type index = 0;
    while ((index = find(s1, index)) != npos) {
        std::string::replace(index, len1, s2);
    }
    return *this;
}

vstring& vstring::replace(const vchar*s1, const vchar*s2)
{
    size_type len1 = vstrlen(s1);
    return replace(s1, len1, s2);
}

vstring& vstring::replace(const vstring&s1, const vchar*s2)
{
    return replace(s1.data(), s1.length(), s2);
}

vstring& vstring::replace(const vchar*s1, const vstring&s2)
{
    size_type len1 = vstrlen(s1);
    return replace(s1, len1, s2.data());
}

vstring& vstring::replace(const vstring&s1, const vstring&s2)
{
    return replace(s1.data(), s1.length(), s2.data());
}

vstring vstring::subBeginWith(const vstring&begin) const
{
    size_type beginIndex = std::string::find(begin);
    if(beginIndex != npos) {
        return vstring(data() + beginIndex);
    }
    else {
        return vstring(*this);
    }
}

vstring vstring::subBeginWithOut(const vstring&begin) const
{
    size_type endIndex = find(begin);
    if(endIndex != npos) {
        return vstring(data() + endIndex + begin.length());
    }
    else {
        return vstring(*this);
    }
}

vstring vstring::subEndWith(const vstring&end) const
{
    size_type endIndex = find(end);
    if(endIndex != npos)
    {
        return substr(0, endIndex + end.length());
    }
    else
    {
        return vstring(*this);
    }
}

vstring vstring::subEndWithOut(const vstring&end) const
{
    size_type endIndex = find(end);
    if(endIndex != npos)
    {
        return substr(0, endIndex);
    }
    else
    {
        return vstring(*this);
    }
}

}   //fcpp
