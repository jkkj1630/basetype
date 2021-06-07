#ifndef VSTRING_H
#define VSTRING_H

#include <string>

#include "vtypes.h"

class vstring;

#ifdef VVEC_H_
#include "vvec.h"
using vstringvec = vvec<vstring>;
#else
#include <vector>
using vstringvec = ::std::vector<vstring>;
#endif

namespace  fcpp{

class vstring : public std::string
{
public:
    vstring();
    vstring(const vchar*p);
    ~vstring();

    vchar at(vint32 i) const;

    vint32 find(const vchar&ch)  const;
    vint32 find(vint32 start, const vchar ch) const;
    vint32 find(vint32 start, const vchar*s) const;
    vint32 find(vint32 start, const vstring&s) const;

    bool startWith(const vchar&ch) const;
    bool startWith(const vchar*s) const;
    bool startWith(const vstring&s) const;

    bool endWith(const vchar&ch) const;

    vstring& removeAt(vint32 start, vint32 len = 1);
    vstring& remove(const vchar&ch);
    vstring& remove(const vchar*s);
    vstring& remove(const vstring&s);

    vstring& replace(const vchar*s1, const vchar*s2);
    vstring& replace(const vchar*s1, const vstring&s2);
    vstring& replace(const vstring&s1, const vchar*s2);
    vstring& replace(const vstring&s1, const vstring&s2);

    vstring subBeginWith(const vstring&begin) const;
    vstring subBeginWithOut(const vstring&begin) const;
    vstring subEndWith(const vstring&end) const;
    vstring subEndWithOut(const vstring&end) const;

    vstring& format(const vchar*fmt, ...);

#ifdef VVEC_H_
    vstringvec split(const vchar*sep) const;
    vstringvec split(const vstring&sep) const;
#endif

    bool isEmpty();

    vstring& toUpper();
    vstring& toLower();

    vint32 toNum();
    vfloat32 toFloat32();
    vstring toBase64();

    static vstring fromFormat(const vchar*fmt, ...);
    static vstring fromNum(const vint32 n);

    static vstring randomStr(vint32 len);

    static vint32 vstrlen(const vchar*);

private:

    static bool vstrLess(const vchar *s1, const vchar *s2);

    vstring& replace(const vchar*s1, vint32 len1, const vchar*s2, vint32 len2);

    inline void setStr(const vchar*);

};

}
#endif // VSTR_H
