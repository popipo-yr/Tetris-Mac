#ifndef music_h_
#define music_h_

#include "fmod/fmod.h"
#include "fmod/fmod_errors.h"
#include <string>
#include <map>
using std::map;
using std::string;

namespace air
{
	class CMusic
	{
	private:
		enum { MUSIC, SOUND };
		struct data
		{
			int type;
			FMOD_SOUND* p_sound;
		};
		typedef map<string, data>           MusicMap;
		typedef map<string, FMOD_CHANNEL*>  ChannelMap;
	private:
		FMOD_SYSTEM*	m_p_system;
		MusicMap		m_musics;
		ChannelMap		m_channels;
	public:
		CMusic();
		~CMusic();
		/*
			��������/��Ч�����ֿ���ѭ�����ţ�������ͣ����Чֻ����һ��
			file��		�ļ�·��
			name��		������
		*/
		bool load_music(string file, string name);
		bool load_sound(string file, string name);
		/*
			���������ļ�����������Դ
			config��		�����ļ���
		*/
		void load_from_config(string config);
		/*
			����ָ��������
		*/
		bool play(string name);
		/*
			��ͣ����
		*/
		void pause(string name);
		/*
			��������
		*/
		void proceed(string name);
		/*
			�ڴ��ͷ�
		*/
		void free();
		/*
			����
		*/
		void update();
	private:
		void _check(FMOD_RESULT r);
	private:
		CMusic(const CMusic&);
		CMusic& operator=(const CMusic&);
	};
	extern CMusic* g_p_music;
}

#endif
