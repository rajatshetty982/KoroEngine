#include "EventBuffer.h"

namespace Koro {
class Event;

void ProcessBuffer(EventBuffer& buffer)
{
	std::byte* current = buffer.GetStart();
	while (current < buffer.Gethead())
	{
		// theres a event header before every event, which has the needed info, so cast our current to that eventheader type
		EventHeader* eventHeader = reinterpret_cast<EventHeader*>(current);
		// get the event in front of the header, and cast it to event* which our onevent needs and call it
		Event* event = reinterpret_cast<Event*>(current + sizeof(EventHeader));

		// OnEvent(*event); // FIXME: uncomment once we implement this in the event.h
		//
		// move the current forward by eventheader size + the size of the current event, that we have the info inside the event header
		current += eventHeader->TotalStep;

	}
}

}
