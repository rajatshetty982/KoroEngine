#pragma once

#include "koropch.h"
#include "KoroEngine/Core/Log.h"
#include "KoroEngine/Events/EventType.h"
#include <string>


namespace Koro {

struct EventHeader
{
	EventType Type;
	uint32_t Size; // actual size of the event ahead
	uint32_t TotalStep; // total size including header, event and the padding
};	

class EventBuffer
{
public:
	EventBuffer(size_t size = 1024 * 1024)
	{
		m_BufferStart = new std::byte[size];
		m_BufferEnd = m_BufferStart + size;
		m_Head = m_BufferStart;
	}

	~EventBuffer()
	{
		// NOTE: for later: need to call destructors for everything in buffer
		delete[] m_BufferStart;
	}

	template<typename T>
	void PushDerivedEvent(const T& specificEvent)
	{
		Push<T>(specificEvent);
	}

	template<typename T, typename... Args>
	void Push(Args&&... args)
	{
		// find the total size needed

		// NOTE: we are taking the actual needed total size and padding it to have multiples of 8, to make it cpu friendly
		// totalSize = ((totalSize + 7) / 8) * 8;
		// (totalSize + 7) & ~7; // does the same thing as above.
		size_t totalSize = (sizeof(EventHeader) + sizeof(T) + 7) & ~7;
		
		// do we have room for the new event?
		if (m_Head + totalSize > m_BufferEnd)
		{
			// NOTE: We will make this a dynamic arena allocator later, returning right now, to get to the next part of the engine quickly for now
			// TODO: write this completely
			//
			 // KORO_ENG_CRITICAL("EventBuffer buffer full. Cant take in the new event type: ",std::to_string((long)T::GetStaticType()));
			return;
		}

		// if we have the room, write the header
		EventHeader* header = reinterpret_cast<EventHeader*>(m_Head);
		header->Type = T::GetStaticType();
		header->Size = sizeof(T);
		header->TotalStep = totalSize;

		// after the header place the new event
		void* paylodPos = m_Head + sizeof(EventHeader);
		new (paylodPos) T(std::forward<Args>(args)...); // basically: create a T type obj at payloadPos with the passed args

		m_Head += totalSize; // move the head pointer ahead by byt size of eventheader and T

	}

	std::byte* GetStart()
	{
		return m_BufferStart;
	}

	std::byte* Gethead()
	{
		return m_Head;
	}

	std::byte* GetEnd()
	{
		return m_BufferEnd;
	}


	void Clear()
	{
		m_Head = m_BufferStart;
	}


private:
	std::byte* m_BufferStart;
	std::byte* m_BufferEnd;
	std::byte* m_Head;
};

  /**
   *  @brief  Processes all events in the passed event buffer and calls OnEvent(*Event) for each.
   *  @return void
   *  *
   */
void ProcessBuffer(EventBuffer& buffer);

}
