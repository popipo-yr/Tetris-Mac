// 2D���ε�ͼ
#ifndef map_h_
#define map_h_
#include <string>
using std::string;
namespace air
{
	class CMap
	{
	private:
		string m_tex;				// ����������
		unsigned int* m_p_map;		// ͼ��ͼ��
		unsigned int* m_p_flag;		// ͼ������
		unsigned int m_tile_size;	// ������ͼ��
		unsigned int m_tile_num_x;	// X ����ͼ����
		unsigned int m_tile_num_y;	// Y ����ͼ����
		struct View
		{
			unsigned int left, right, bottom, top;
			unsigned int width, hight;
		};
		View m_view;				// �ӿ�
		unsigned int m_draw_num_x;	// X ����Ҫ���Ƶ�ͼ����
		unsigned int m_draw_num_y;	// Y ����Ҫ���Ƶ�ͼ����
	public:
		CMap();
		~CMap();
		// �������ó�ʼ����ͼ
        // p_config��	�����ļ�
        // view_x��	�ӿڿ�
        // view_y��	�ӿڸ�
		bool init(const char* p_config, unsigned int view_w, unsigned int view_h);
		// �ƶ��ӿ�
        // x��y��	�ƶ���
		void scroll(int x, int y);
		// ���Ƶ�ͼ
		void draw();
	private:
		CMap(const CMap&);
		CMap& operator=(const CMap&);
	};
}

#endif
