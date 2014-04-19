/*
	����С����
*/
#ifndef common_h_
#define common_h_

#include <string>
#include <sstream>
#include <cstdlib>
using std::string;

namespace air
{
	// ���ù��ߺ�
	#define SAFE_DELETE(x)			{ if (x) { delete (x);		(x) = NULL; } }
	#define SAFE_DELETE_ARRAY(x)	{ if (x) { delete[] (x);	(x) = NULL; } }
	#define SAFE_FREE(x)			{ if (x) { free(x);			(x) = NULL; } }
	// �ַ���ת��Ϊ������
	inline float str_to_float(string num)
	{
		return static_cast<float>(atof(num.c_str()));
	}
	inline float stf(string num)
	{
		return str_to_float(num);
	}
	// �ַ���ת��Ϊ����
	inline int str_to_int(string num)
	{
		return atoi(num.c_str());
	}
	inline int sti(string num)
	{
		return str_to_int(num);
	}
	// ��������ת��Ϊ�ַ���
    template<class T>
    std::string tostr(const T& r)
    {
        std::ostringstream oss;
        oss.precision(5);
        oss.setf(std::ios_base::fixed);
        oss << r;
        return oss.str();
    }

	// ��������
	typedef unsigned long	u32;
	typedef long			s32;
	typedef unsigned short	u16;
	typedef short			s16;
	typedef unsigned char	u8;
	typedef char			s8;
}

#endif
