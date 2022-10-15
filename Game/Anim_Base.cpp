#include "pch.h"
#include "Anim_Base.h"
#include "SpriteSheet.h"

namespace Mac {

	Anim_Base::Anim_Base()
		: m_frameCurrent(0)
		, m_frameStart(0)
		, m_frameEnd(0)
		, m_frameRow(0)
		, m_frameTime(0.0f)
		, m_elapsedTime(0.0f)
		, m_frameActionStart(-1)
		, m_frameActionEnd(-1)
		, m_loop(false)
		, m_playing(false)
	{
	}

	void Anim_Base::SetSpriteSheet(SpriteSheet* l_sheet)
	{
		m_spriteSheet = l_sheet;
	}

	void Anim_Base::SetFrame(Frame l_frame)
	{
		if (
			(
				l_frame >= m_frameStart
				&&
				l_frame <= m_frameEnd
			)
			||
			(
				l_frame >= m_frameEnd
				&&
				l_frame <= m_frameStart
			)
		)
		{
			m_frameCurrent = l_frame;
		}
	}

	void Anim_Base::SetStartFrame(Frame l_frame)
	{
		m_frameStart = l_frame;
	}

	void Anim_Base::SetEndFrame(Frame l_frame)
	{
		m_frameEnd = l_frame;
	}

	void Anim_Base::SetFrameRow(Frame l_row)
	{
		m_frameRow = l_row;
	}

	void Anim_Base::SetActionStart(Frame l_frame)
	{
		m_frameActionStart = l_frame;
	}

	void Anim_Base::SetActionEnd(Frame l_frame)
	{
		m_frameActionEnd = l_frame;
	}

	void Anim_Base::SetFrameTime(float l_time)
	{
		m_frameTime = l_time;
	}

	void Anim_Base::SetLooping(bool l_loop)
	{
		m_loop = l_loop;
	}

	void Anim_Base::SetName(const std::string& l_name)
	{
		m_name = l_name;
	}

	Mac::SpriteSheet* Anim_Base::GetSpriteSheet()
	{
		return m_spriteSheet;
	}

	Mac::Frame Anim_Base::GetFrame()
	{
		return m_frameCurrent;
	}

	Mac::Frame Anim_Base::GetStartFrame()
	{
		return m_frameStart;
	}

	Mac::Frame Anim_Base::GetEndFrame()
	{
		return m_frameEnd;
	}

	Mac::Frame Anim_Base::GetFrameRow()
	{
		return m_frameRow;
	}

	int Anim_Base::GetActionStart()
	{
		return m_frameActionStart;
	}

	int Anim_Base::GetActionEnd()
	{
		return m_frameActionEnd;
	}

	float Anim_Base::GetFrameTime()
	{
		return m_frameTime;
	}

	float Anim_Base::GetElapsedTime()
	{
		return m_elapsedTime;
	}

	bool Anim_Base::IsLooping()
	{
		return m_loop;
	}

	bool Anim_Base::IsPlaying()
	{
		return m_playing;
	}

	bool Anim_Base::IsInAction()
	{
		if (m_frameActionStart == -1 || m_frameActionEnd == -1)
			return true;

		return (
			m_frameCurrent >= m_frameActionStart
			&&
			m_frameCurrent <= m_frameActionEnd
		);
	}

	std::string Anim_Base::GetName()
	{
		return m_name;
	}

	void Anim_Base::Play()
	{
		m_playing = true;
	}

	void Anim_Base::Pause()
	{
		m_playing = false;
	}

	void Anim_Base::Stop()
	{
		m_playing = false;

		Reset();
	}

	void Anim_Base::Reset()
	{
		m_frameCurrent = m_frameStart;
		m_elapsedTime = 0.0f;

		CropSprite();
	}

	void Anim_Base::Update(const float& l_deltaTime)
	{
		if (!m_playing)
			return;

		m_elapsedTime += l_deltaTime;

		if (m_elapsedTime < m_frameTime)
			return;

		FrameStep();
		CropSprite();
		m_elapsedTime = 0;
	}

}