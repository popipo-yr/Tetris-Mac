#ifndef timer_h_
#define timer_h_

namespace air 
{
	class CTimer
	{
	private:
		double	m_sec_per_count;	// CPU ִ�� 1 Count �ķѵ�����
		__int64	m_start_tick;		// ��ʱ������ʱ��
		bool	m_pause;			// ��ʱ����ͣ��־

	public:
		CTimer();
		~CTimer();

		/*
			���ü�ʱ����ʼ��ʱʱ��
		*/
		void reset();

		/*
			��ͣ / ������ʱ��
			flag��	true	-- ��ͣ��ʱ
					false	-- �ָ���ʱ
		*/
		void pause(bool flag);

		/*
			�����ĺ��� / �� / ���� / ʱ
		*/
		double pass_ms();
		double pass_s();
		double pass_m();
		double pass_h();

	private:
		CTimer(const CTimer&);
		CTimer& operator =(const CTimer&);
	};
}

#endif