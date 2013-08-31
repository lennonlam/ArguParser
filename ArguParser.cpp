#include "ArguParser.h"

#define SAFE_DEL_ARRAY(ptr) { if (ptr) {delete [] ptr; ptr = NULL;} }

wstring str2wstr(const string s);
string  wstr2str(const wstring ws);

/// <!--===================================================================-->
///     ArguParser aims at providing a collection of command-line arguments
///     This allows user to check whether a argument exists 
///     and get a argument value(s) easily
/// <!--===================================================================-->
void ArguParser::Clear()
{
    SAFE_DEL_ARRAY(m_wargv);
    m_argc = 0;
}

//! <!------------------------------------------------------------------->
//!         Send arguments to parser
//! @param  argc:  Argument count   [IN]
//! @param  argv:  Argument values  [IN]
//! <!------------------------------------------------------------------->
void ArguParser::Parse(const int argc, char* argv[])
{
    Clear();
    m_wargv = new wstring[argc];
    m_argc = argc;
    for (int i = 0; i < argc; ++i)
        m_wargv[i].assign(str2wstr(argv[i]));
};
void ArguParser::Parse(const int argc, wchar_t* argv[])
{
    Clear();
    m_wargv = new wstring[argc];
    m_argc = argc;
    for (int i = 0; i < argc; ++i)
        m_wargv[i].assign(argv[i]);
};

//! <!------------------------------------------------------------------->
//!         Get argument value by tag, 
//!         (which means getting the argument after the tag argement)
//! @param  tag:  tag string        [IN]
//! @param  val:  value string      [OUT]
//! @return 0: success | -1 tag doesn't exist
//! <!------------------------------------------------------------------->
int ArguParser::GetTagValue(const string tag, string& val)
{
    val.clear();
    wstring wVal, wTag = str2wstr(tag);
    int ret = GetTagValue(wTag, wVal);
    if (ret == 0)
        val = wstr2str(wVal);
    return ret;
}
int ArguParser::GetTagValue(const wstring tag, wstring& val)
{
    unsigned int idx = -1;
    int ret = -1;
    val.clear();
    if (IsTagExists(tag, &idx))
    {
        if (idx < m_argc-1)
        {
            val = m_wargv[idx+1];
            ret = 0;
        }
    }
    return ret;
}

//! <!------------------------------------------------------------------->
//!         Get multiple values of a tag
//!         (which means getting the multiple argument after the tag argement)
//! @param  tag:  tag string                    [IN]
//! @param  n:    number of value string needed [IN]
//! @param  val:  array of value string         [OUT]
//! @return 0: success | -1 tag doesn't exist
//! <!------------------------------------------------------------------->
int ArguParser::GetTagMultiValue(const string tag, const unsigned int n, vector<string>& val)
{
    if (n == 0)
        return 0;

    val.clear();
    wstring wTag = str2wstr(tag);
    vector<wstring> wVal;

    int ret = GetTagMultiValue(wTag, n, wVal);
    if (ret == 0)
    {
        for (vector<wstring>::iterator it = wVal.begin(); it != wVal.end(); ++it)
            val.push_back(wstr2str(*it));
    }
    return ret;
}
int ArguParser::GetTagMultiValue(const wstring tag, const unsigned int n, vector<wstring>& val)
{
    if (n == 0)
        return 0;

    unsigned int idx = -1;
    int ret = -1;
    val.clear();
    val.reserve(n);
    if (IsTagExists(tag, &idx))
    {
        for (unsigned int i = 1; i <= n; ++i)
        {
            if (idx+i < m_argc)
            {
                val.push_back(m_wargv[idx+i]);
                ret = 0;
            }
            else
                ret = -1;
        }
    }
    return ret;
}

//! <!------------------------------------------------------------------->
//!         Check if a tag exists
//! @param  tag:      tag string                         [IN]
//! @param  argvIdx:  Index of the tag in argument list  [OUT | Optional]
//! @return Exists or not
//! <!------------------------------------------------------------------->
bool ArguParser::IsTagExists(const string tag, unsigned int* argvIdx)
{
    return IsTagExists(str2wstr(tag), argvIdx);
}
bool ArguParser::IsTagExists(const wstring tag, unsigned int* argvIdx)
{
    for (unsigned int i = 0; i < m_argc; ++i)
    {
        if (wcscmp(m_wargv[i].c_str(), tag.c_str()) == 0)
        {
            if (argvIdx)
                *argvIdx = i;
            return true;
        }
    }
    return false;
}

//! <!------------------------------------------------------------------->
//!         Get argument string by index
//! @param  idx:   Index             [IN]
//! @param  argu:  Argument staring  [OUT]
//! <!------------------------------------------------------------------->
void ArguParser::GetArguByIdx(const unsigned int idx, string& argu)
{
    wstring wargu;
    GetArguByIdx(idx, wargu);
    argu =wstr2str(wargu);
    return;
}
void ArguParser::GetArguByIdx(const unsigned int idx, wstring& argu)
{
    argu = L"";
    if (idx < m_argc)
        argu = m_wargv[idx];
    return;
}

wstring str2wstr(const string s)
{
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    SAFE_DEL_ARRAY(_Dest);
    return result;
}
string  wstr2str(const wstring ws)
{
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    SAFE_DEL_ARRAY(_Dest);
    return result;
}