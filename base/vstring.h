#ifndef VSTRING_H
#define VSTRING_H

#include <string>
#include <vector>

namespace  fcpp{

class vstring;

using vstringvec = std::vector<vstring>;

class vstring : public std::string
{
public:
    vstring();
    vstring(const vchar*p) : std::string(p) {
    }
    vstring(const std::string&s) : std::string(s) {
    }
    ~vstring() {

    }

    bool startWith(const vchar&ch) const;
    bool startWith(const vchar*s) const;
    bool startWith(const vstring&s) const;

    bool endWith(const vchar&ch) const;

    vstring& remove(size_type start, size_type len = 1);
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

    vstring& format(const vchar*__restrict fmt, ...);

    vstringvec split(const vchar*sep) const;
    vstringvec split(const vstring&sep) const;

    bool isEmpty();

    vstring& toUpper();
    vstring& toLower();

    vint32 toNum();
    vfloat32 toFloat32();
    vstring toBase64();

    static vstring fromFormat(const vchar*__restrict fmt, ...);
    static vstring fromNum(const vint32 n);

    static vstring randomStr(vint32 len);

    static vint32 vstrlen(const vchar*);

private:

    static bool vstrLess(const vchar *s1, const vchar *s2);

    vstring& replace(const vchar*s1, size_type len1, const vchar*s2);

    inline void setStr(const vchar*);

};

}
#endif // VSTRING_H
