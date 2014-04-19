#ifndef phy2d_h_
#define phy2d_h_
#include "../math/math2d.h"
namespace air
{
    namespace phy
    {
        using air::math::vec2;
        // CPoint /////////////////////////////////////////////////////
        class CPoint
        {
        private:
            vec2 m_position;   // λ��
            vec2 m_velocity;   // �ٶ�
            float m_mass;   // ����
            float m_inv_mass;   // 1/����
            vec2 m_acc_force;   // ������֮��
        public:
            CPoint();
            ~CPoint();
            //	��ʼ��λ�ã��ٶȣ�����
            //	pos��	λ��
            //	vel��	�ٶ�
            //	mass��	����
            void init(const vec2& pos, const vec2& vel, float mass);
            //	���һ�����������������
            //	f	����
            void add_force(const vec2& f);
            //	����
            //	dt��  ����ϵ��
            void run(float dt);
            //	��������������
            vec2& position();
            vec2& velocity();
            float mass();
        private:
            CPoint(const CPoint&);
            CPoint& operator=(const CPoint&);
        };
        // CSpring /////////////////////////////////////////////////////
		class CSpring
		{
		private:
			CPoint* m_pt1;
			CPoint* m_pt2;
			float m_k;
			float m_reset_length;
			float m_friction;
		public:
			// ���췽��
			// a��b���ʵ�
			// k������ϵ��
			// rl��ԭʼ����
			// fr��Ħ����
			CSpring(CPoint* a, CPoint* b, float k, float rl, float fr);
			// ������
			void calculate_force();
		private:
			CSpring();
			CSpring(const CSpring&);
			CSpring& operator=(const CSpring&);
		};
		// force /////////////////////////////////////////////////////
		class IForceGen
		{
        public:
            IForceGen()   {};
            virtual void run(CPoint* p) = 0;   // p �����������õ��ʵ�
        private:
            IForceGen(const IForceGen&);
            IForceGen& operator=(const IForceGen&);
		};
		class CDrag : public IForceGen   // Ħ����
		{
        private:
            float m_k1, m_k2;
        public:
            CDrag(float k1, float k2);
            virtual void run(CPoint* p);
		};
		class CGravity : public IForceGen   // ����
		{
        private:
            vec2 m_g;
        public:
            CGravity(const vec2& g);
            virtual void run(CPoint* p);
		};
		/*class CSpring : public IForceGen   // ����
		{
        private:
            CPoint* m_p_other;
            float m_constant;
            float m_rest_length;
        public:
            CSpring(const CPoint* p_other, float constant, float rest_length);
            virtual void run(CPoint* p);
		};*/
		class CAnchoredSpring : public IForceGen   // ê�㵯��
		{
        private:
            vec2 m_anchor;
            float m_constant, m_rest_length;
        public:
            CAnchoredSpring(const vec2& anchor, float constant, float rest_length);
            virtual void run(CPoint* p);
            vec2 anchor() const;
		};
		// collide line /////////////////////////////////////////////////////
		class CLine
		{
        public:
            vec2 m_s, m_e;   // ��㣬�յ�
            vec2 m_nor;   // ������
            float m_l;   // ����
        public:
            CLine();
            ~CLine();
            // ������ײ�߶�
            // start��end����㣬�յ�
            void set(const vec2& start, const vec2& end);
            // ��������
            // v���ٶ�
            // ����ֵ���������ٶ�
            vec2 rebound(const vec2& v);
            // �㵽�߶ε��������
            // v����
            // ����ֵ������
            float mindist(const vec2& v);
        private:
            CLine(const CLine&);
            CLine& operator=(const CLine&);
		};
    }
}
#endif
