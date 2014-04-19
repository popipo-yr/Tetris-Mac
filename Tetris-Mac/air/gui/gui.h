#ifndef gui_static_h_
#define gui_static_h_
#include "../graphics/openGL.h"
#include <string>
#include <list>
using std::string;
using std::list;
namespace air
{
     ////////////////////////////////////////////////////////////////////////
	// gui�ؼ�����
	class CGuiObject
	{
	protected:
		unsigned int m_id;			// Ψһ��ʶ
		float	 m_x, m_y;			        // �ؼ����½�����
		float	 m_width, m_height;	// �ؼ��ߴ�
		//bool	 m_visible;			        // �Ƿ�ɼ���Ŀǰû�������
		bool m_focus;                   // �Ƿ�ӵ�н���
    public:
        // gui��Ϣ
        enum { NIL, KEY_DOWN, KEY_UP, MOUSE_MOVE, MOUSE_L_DOWN, MOUSE_L_UP };
        enum { SHIFT = 1 };
        struct msg
        {
            int type;     // ��Ϣ����
            int key;      // �����ֵ
            int flags;    // ����״̬
            float x, y;   // ���λ��
        };
	public:
        // ����ؼ�
        // id��     Ψһ��ʶ
        // x��y��  λ��
        // w��h�� �ߴ�
		CGuiObject(unsigned int id, float x, float y, float w, float h);
		virtual ~CGuiObject();
		// �Ƿ��ý���
		// ����ֵ��true -- �н��� / false -- �޽���
		bool is_focus() const;
		// ʧȥ����
		void lost();
		// ���ؿؼ�ID
        // ����ֵ��	�ؼ�ID
		unsigned int get_id() const;
		// ����ӿ� ////////////////////////////////////////////////////////////////////////
		// ���ƿؼ�
		virtual void draw() = 0;
		// �¼���Ӧ
		// e����Ϣ
		// ����ֵ���¼��Ƿ񱻴���
		virtual bool on_msg(const msg& e) = 0;
		// �ж������Ƿ��ڿؼ���Χ��
        // x��y��	ĳ�������
        // ����ֵ�� true -- ���ڿؼ��� / false -- ���ڿؼ���
		virtual bool is_over(float x, float y) = 0;
	private:
		CGuiObject();
		CGuiObject(const CGuiObject&);
		CGuiObject& operator =(const CGuiObject&);
	};
	////////////////////////////////////////////////////////////////////////
	// gui������
	class CGuiSystem
	{
	private:
		typedef list<CGuiObject*>	GuiList;
		GuiList m_gui_object_list;
	public:
		CGuiSystem();
		~CGuiSystem();
        // ��ӿؼ�
        // p_obj�� �ؼ�����
		void add(CGuiObject* p_obj);
		// �����ó�ʼ��GUI
        // p_config��	�����ļ�
		bool load_from_config(const char* p_config);
		//	�������пؼ�
		void draw();
		// ������Ϣ����
		// ����ֵ�� �ؼ�ID
		enum { NO_MSG = 0xffff };
		unsigned int process_msg();
		 // ȡ�����пؼ��Ľ���
		void all_lost();
		// ����һ���ؼ�
		CGuiObject* get(unsigned int id);
	private:
		CGuiSystem(const CGuiSystem&);
		CGuiSystem& operator=(const CGuiSystem&);
	};
	////////////////////////////////////////////////////////////////////////
	// �ı���ǩ
	class CLabel : public CGuiObject
	{
	private:
		string m_text;				    // �ı�����
		string m_pen;				// ����������
		color m_text_color;		    // �ı���ɫ
	public:
		CLabel(unsigned int id, float x, float y, string text, string pen, color c);
		virtual void draw();
		virtual bool on_msg(const msg& e);
		virtual bool is_over(float x, float y);
	private:
		CLabel();
		CLabel(const CLabel&);
		CLabel& operator=(const CLabel&);
	};
	////////////////////////////////////////////////////////////////////////
	// ��ť
	class CButton : public CGuiObject
	{
	private:
		string	m_up_tex;			// ����������
		string	m_down_tex;		// ����������
		string	m_over_tex;		// ����������
		enum ButtonState	{ B_UP, B_DOWN, B_OVER };
		ButtonState	m_state;
	public:
		CButton(unsigned int id, float x, float y, float width, float height, string up_tex, string down_tex, string over_tex);
		virtual void draw();
		virtual bool on_msg(const msg& e);
		virtual bool is_over(float x, float y);
	private:
		CButton();
		CButton(const CButton&);
		CButton& operator=(const CButton&);
	};
	////////////////////////////////////////////////////////////////////////
	// �༭��
	class CEdit : public CGuiObject
	{
    private:
        string m_pen;   // ��������
        string m_result;   // �༭���ı�
    public:
        CEdit(unsigned int id, float x, float y, float width, float height, string pen);
        ~CEdit();
        virtual void draw();
		virtual bool on_msg(const msg& e);
		virtual bool is_over(float x, float y);
		// ȡ�ñ༭�����������
		string content() const;
    private:
        bool is_full() const;   // �༭���Ƿ�����
        CEdit();
        CEdit(const CEdit&);
        CEdit& operator=(const CEdit&);
	};
}
#endif
