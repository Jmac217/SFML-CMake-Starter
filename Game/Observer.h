#pragma once

#include "Message.h"

namespace Mac {

	struct Observer
	{
		virtual ~Observer() {}
		virtual void Notify(const Message& l_message) = 0;
	};

}