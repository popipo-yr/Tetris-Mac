#ifndef sprite_h_
#define sprite_h_

#include <string>
using std::string;

namespace air
{
	class CSprite
	{
    protected:
		string m_image;
		float	 m_x, m_y, m_z;
		float	 m_w, m_h;
		float	 m_angle;
		unsigned char	m_alpha;
        struct aabb
        {
            float left, right, bottom, top;
        };
        aabb m_aabb;
	public:
        CSprite();
		virtual ~CSprite();
		// ��ʼ������
		// image��	������
		// x��y��	λ��
		// w��h��	�ߴ�
		void init(string image, float x, float y, float w, float h);
		// �ƶ�����
		// x��y��	�ƶ���
		void move(float x, float y);
		// ֱ�ӽ�����ŵ�ָ��λ��
		// x��y��	λ��
		void put(float x, float y);
		// ������Ϊԭ����ת����
		// angle��	�Ƕ�
		void rotate(float angle);
		// �ı�͸����
		// alpha��	alphaֵ�ı���
		void fade(int alpha);
		// ���ƾ���
		virtual void draw();
		// ������
		float pos_x() const;
		float pos_y() const;
		float width() const;
		float height() const;
		// ��ʼ����ײ����
		// left��right��bottom��top����ײ�еı߽�
		void init_aabb(float left, float right, float bottom, float top);
		// ������ײ����
		aabb box() const
		{
            return m_aabb;
		}
		// ��ײ���
		// spr�� ���м��ľ���
		// ����ֵ�� �Ƿ�����ײ
		bool is_collide(const CSprite& spr) const;
		void debug_draw_aabb() const;
	private:
		CSprite(const CSprite&);
		CSprite& operator=(const CSprite&);
	};
	//////////////////////////////////////////////////////////////////////////
	class CTimer;
	class CAniSprite : public CSprite
	{
	public:
		enum Sequence { X, Y };  // ����֡��ʲô��ʽ���
	private:
		CTimer* m_p_pace_controller;              // �����ٶȿ���
		unsigned int m_interval_ms;			    // ֡���
		unsigned int m_cur_x, m_cur_y;		    // ��ǰ֡
		unsigned int m_total_x, m_total_y;	    // ��������������
		unsigned int m_frame_w, m_frame_h;	// ֡��֡��
		Sequence m_seq;						        // ֡����
	public:
		CAniSprite();
		~CAniSprite();
		// ��ʼ����������
		// ms��              ÿ֡�������
		// total_x��total_y����������������
		// seq��             ֡���з�ʽ
		void init_ani(unsigned int ms, unsigned int total_x, unsigned int total_y, Sequence seq);
		// ����Ҫ���ŵĶ���֡����
		// n�����ŵڼ���֡����
		void set_sequence(unsigned int idx);
		// ���ƾ���
		virtual void draw();
	private:
        void _draw(unsigned int x, unsigned int y);
		CAniSprite(const CAniSprite&);
		CAniSprite& operator=(const CAniSprite&);
	};
}

#endif
