#pragma once

#include "EventListener.h"
#include "IFont.h"
#include "Vector2.h"
#include "Size.h"
#include "Color.h"

class UIParameters
{
protected:
	Vector2		m_Location = Vector2(0, 0);
	Size		m_Size = SizeT<int>(100, 100);
	bool		m_FixedSize = true;
	bool		m_HasFocus = false;
	bool		m_Visable = true;
	IFont*		m_Font = nullptr;
	std::string m_Text = "";
	Color		m_TextColor = Color();

public:

	EventListener OnLocationChanged;
	EventListener OnSizeChanged;
	EventListener OnFixedSizeChanged;
	EventListener OnFocusChanged;
	EventListener OnVisableChanged;
	EventListener OnFontChanged;
	EventListener OnTextChanged;
	EventListener OnTextColorChanged;

#pragma region propertys
	Vector2& GetLocation()
	{
		return m_Location;
	}

	void SetLocation(Vector2 _Location)
	{
		m_Location = _Location;
		OnLocationChanged.SetEvent(this, nullptr);
	}

	Size& GetSize()
	{
		return m_Size;
	}

	void SetSize(Size _Size)
	{
		m_Size = _Size;
		OnSizeChanged.SetEvent(this, nullptr);
	}

	bool& GetFixedSize()
	{
		return m_FixedSize;
	}

	void SetFixedSize(bool _FixedSize)
	{
		m_FixedSize = _FixedSize;
		OnFixedSizeChanged.SetEvent(this, nullptr);
	}

	bool& GetHasFocus()
	{
		return m_HasFocus;
	}

	bool& GetVisable()
	{
		return m_Visable;
	}

	void SetVisable(bool _Visable)
	{
		m_Visable = _Visable;
		OnVisableChanged.SetEvent(this, nullptr);
	}

	IFont* GetFont() const
	{
		return m_Font;
	}

	void SetFont(IFont* _Font)
	{
		m_Font = _Font;
		OnFontChanged.SetEvent(this, nullptr);
	}

	std::string& GetText()
	{
		return m_Text;
	}

	void SetText(std::string _Text)
	{
		m_Text = _Text;
		OnTextChanged.SetEvent(this, nullptr);
	}

	Color& GetTextColor()
	{
		return m_TextColor;
	}

	void SeTextColor(Color _TextColor)
	{
		m_TextColor = _TextColor;
		OnTextColorChanged.SetEvent(this, nullptr);
	}
#pragma endregion 
};