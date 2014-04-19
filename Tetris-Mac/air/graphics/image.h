#ifndef image_h_
#define image_h_

namespace air
{
    typedef unsigned long	u32;
	typedef long			s32;
	typedef unsigned short	u16;
	typedef short			s16;
	typedef unsigned char	u8;
	typedef char			s8;
    // 2011-5-7   ���ַ�ʽ���������Ǵ�������ģ������ܶ�ͬһ������ʹ��SWAP
	#define SWAP(A, B)		(A) = (A) + (B);	\
							(B) = (A) - (B);	\
							(A) = (A) - (B)
	struct rgb
	{
		u8 r, g, b;
	};
	struct rgba
	{
		u8 r, g, b, a;
	};

	//////////////////////////////////////////////////////////////////////////
	// ֧�� 24 λδѹ��λͼ
	class CBmp
	{
	private:
		u8*	m_p_rgb;
		u8* m_p_rgba;
		u32	m_w;
		u32	m_h;

		// λͼ�ļ�ͷ��Ϣ
#pragma pack(1)
		struct head
		{
			u16 id;
			u32 size;
			u16 dummy1;
			u16 dummy2;
			u32 offset_image;
		};
#pragma pack()
		// λͼ�ļ���Ϣ
		struct info
		{
			u32 info_size;
			u32 pixel_width;
			u32 pixel_height;
			u16 planes;
			u16 bit_per_pixel;	// λͼλ��
			u32 compress;		// 0 ��ʾδѹ��
			u32 image_size;
			u32 horizon;
			u32 vertical;
			u32 color_used;
			u32 color_important;
		};

	public:
		CBmp();
		~CBmp();

		/*
			����λͼ
			p_file��	λͼ�ļ�
			����ֵ��	����ɹ� / ʧ��
		*/
		bool load(const char* p_file);

		/*
			�� RGB ͼ������ת��Ϊ RGBA
			r��g��b��	͸��ɫ
		*/
		void convert_to_rgba(u8 r, u8 g, u8 b);

		/*
			�õ�λͼ�����Ϣ
		*/
		const u8* rgb_data() const;
		const u8* rgba_data() const;
		u32 width() const;
		u32 height() const;

		/*
			�ͷ��ڴ�
		*/
		void unload();
	private:
		CBmp(const CBmp&);
		CBmp& operator=(const CBmp&);
	};

	//////////////////////////////////////////////////////////////////////////
	// ֧�� 32 λ���� alpha ͨ����δѹ�� tga
	class CTga
	{
	private:
		u32 m_w;
		u32 m_h;
		u8* m_p_rgba;	// rgb or rgba

		// tga �ļ�ͷ
#pragma pack(1)
		struct head
		{
			u8 info_length;
			u8 color_map_type;
			u8 image_type;
			u8 color_map[5];
			u16 x_origin;
			u16 y_origin;
			u16 image_width;
			u16 image_height;
			u8 bit_per_pixel;
			u8 image_desc;
		};
#pragma pack()

	public:
		CTga();
		~CTga();

		/*
			����tga
			p_file��	λͼ�ļ�
			����ֵ��	����ɹ� / ʧ��
		*/
		bool load(const char* p_file);

		/*
			�ͷ��ڴ�
		*/
		void unload();

		/*
			�õ�ͼ�������Ϣ
		*/
		const u8* data() const;
		u32 width() const;
		u32 height() const;

	private:
		CTga(const CTga&);
		CTga& operator=(const CTga&);
	};
}

#endif
