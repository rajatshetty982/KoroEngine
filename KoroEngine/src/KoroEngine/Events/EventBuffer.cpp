#include "EventBuffer.h"
#include "Event.h"

namespace Koro {

void ProcessBuffer(EventBuffer& buffer, const std::function<void(Event&)>& callback)
{
	std::byte* current = buffer.GetStart();
	while (current < buffer.Gethead())
	{
		// theres a event header before every event, which has the needed info, so cast our current to that eventheader type
		EventHeader* eventHeader = reinterpret_cast<EventHeader*>(current);
		// get the event in front of the header, and cast it to event* which our onevent needs and call it
		Event* event = reinterpret_cast<Event*>(current + sizeof(EventHeader));

		callback(*event);

		// move the current forward by eventheader size + the size of the current event, that we have the info inside the event header
		current += eventHeader->TotalStep;

	}
}
}
