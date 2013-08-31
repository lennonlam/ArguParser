#ifndef __ARGU_PARSER_H__
#define __ARGU_PARSER_H__

#include <vector>
#include <string>

using namespace std;

/// <!--===================================================================-->
///     ArguParser aims at providing a collection of command-line arguments
///     This allows user to check whether a argument exists 
///     and get a argument value(s) easily
/// <!--===================================================================-->
class ArguParser
{
public:
    ArguParser() : m_wargv(NULL), m_argc(0) {};
    virtual ~ArguParser() { Clear(); };

    //! <!------------------------------------------------------------------->
    //!         Send arguments to parser
    //! @param  argc:  Argument count   [IN]
    //! @param  argv:  Argument values  [IN]
    //! <!------------------------------------------------------------------->
    void Parse (const int argc, char*    argv[]);
    void Parse (const int argc, wchar_t* argv[]);

    //! <!------------------------------------------------------------------->
    //!         Get argument value by tag, 
    //!         (which means getting the argument after the tag argement)
    //! @param  tag:  tag string        [IN]
    //! @param  val:  value string      [OUT]
    //! @return 0: success | -1 tag doesn't exist
    //! <!------------------------------------------------------------------->
    int  GetTagValue(const string  tag, string&  val);
    int  GetTagValue(const wstring tag, wstring& val);

    //! <!------------------------------------------------------------------->
    //!         Get multiple values of a tag
    //!         (which means getting the multiple argument after the tag argement)
    //! @param  tag:  tag string                    [IN]
    //! @param  n:    number of value string needed [IN]
    //! @param  val:  array of value string         [OUT]
    //! @return 0: success | -1 tag doesn't exist
    //! <!------------------------------------------------------------------->
    int GetTagMultiValue(const string  tag, const unsigned int n, vector<string>&  val);
    int GetTagMultiValue(const wstring tag, const unsigned int n, vector<wstring>& val);

    //! <!------------------------------------------------------------------->
    //!         Check if a tag exists
    //! @param  tag:      tag string                         [IN]
    //! @param  argvIdx:  Index of the tag in argument list  [OUT | Optional]
    //! @return Exists or not
    //! <!------------------------------------------------------------------->
    bool IsTagExists(const string tag,  unsigned int* argvIdx = NULL);
    bool IsTagExists(const wstring tag, unsigned int* argvIdx = NULL);

    //! <!------------------------------------------------------------------->
    //!         Get argument string by index
    //! @param  idx:   Index             [IN]
    //! @param  argu:  Argument staring  [OUT]
    //! <!------------------------------------------------------------------->
    inline void GetArguByIdx(const unsigned int idx, string& argu);
    inline void GetArguByIdx(const unsigned int idx, wstring& argu);

private:
    void      Clear();

    wstring*        m_wargv;
    unsigned int    m_argc;
};

#endif
