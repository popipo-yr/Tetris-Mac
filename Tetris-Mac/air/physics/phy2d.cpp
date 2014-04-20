#include "phy2d.h"
#include <math.h>
namespace air
{
    namespace phy
    {
        // CPoint /////////////////////////////////////////////////////
        CPoint::CPoint()
        {
            m_position = vec2(0.0f, 0.0f);
            m_velocity = vec2(0.0f, 0.0f);
            m_mass = m_inv_mass = 0.0f;
            m_acc_force = vec2(0.0f, 0.0f);
        }
        CPoint::~CPoint()
        {
        }
        void CPoint::init(const vec2& pos, const vec2& vel, float mass)
        {
            m_position = pos;
            m_velocity = vel;
            m_mass = mass;
            m_inv_mass = 1 / mass;
        }
        void CPoint::add_force(const vec2& f)
        {
            if (f.x == 0.0f && f.y == 0.0f)
                return;
            m_acc_force = m_acc_force + f;
        }
        void CPoint::run(float dt)
        {
            vec2 a = m_acc_force * m_inv_mass * dt;   // a = f / m
            m_velocity = m_velocity + a;   // add velocity
            m_position = m_position + m_velocity * dt;  // update linear position
            m_acc_force = vec2(0.0f, 0.0f);   // reset force
        }
        vec2& CPoint::position()
        {
            return m_position;
        }
        vec2& CPoint::velocity()
        {
            return m_velocity;
        }
        float CPoint::mass()
        {
            return m_mass;
        }
        // CSpring /////////////////////////////////////////////////////
		CSpring::CSpring(CPoint* a, CPoint* b, float k, float rl, float fr)
		{
			m_pt1 = a;
			m_pt2 = b;
			m_k = k;
			m_reset_length = rl;
			m_friction = fr;
		}
		void CSpring::calculate_force()
		{
			vec2 v = m_pt1->position() - m_pt2->position();
			float r = v.length();
			vec2 f;
			if (r != 0.0f)
            {
                float d = fabsf(r - m_reset_length);
                f = f + (v.unitize() * d * -m_reset_length);   // f = -kx
                f = f + (m_pt1->velocity() - m_pt2->velocity()) * -m_friction;   // 鎽╂摝鍔