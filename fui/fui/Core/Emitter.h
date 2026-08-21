#pragma once

#include "Predef.h"
#include "Event.h"

class Emitter;

class Listener : public GcObj {
public:
	virtual void onListenerEvent(Event* event) {}

	virtual const char* getClassName() const { return "Listener"; }
};

class Emitter : public Listener {
public:
	Ref<GcList<Listener>> listeners{new GcList<Listener>(), this};
	Ref<Listener> listener{nullptr, this};
	Ref<Closure<void(Event*)>> cbOnEvent{nullptr, this};

	void addListenerOnce(Listener* l) {
		listeners->push_once(l);
	}
	void addListener(Listener* l) {
		listeners->push(l);
	}
	void removeListener(Listener* l) {
		listeners->remove(l);
	}

	virtual void onEvent(Event* event) {}

	void emit(Event* event) {
		if (cbOnEvent != nullptr) {
			cbOnEvent->invoke(event);
		}

		if (event->isStopPropagation == 2) return;

		onEvent(event);

		if (event->isStopPropagation == 2) return;

		if (listener != nullptr) {
			listener->onListenerEvent(event);
		}

		if (event->isStopPropagation == 2) return;

		Ref<GcList<Listener>> tmps{new GcList<Listener>()};
		tmps->push_all(listeners);

		for (int i = 0; i < tmps->size(); i++) {
			Listener* l = tmps->get(i);
			if (l) {
				l->onListenerEvent(event);
				if (event->isStopPropagation == 2) return;
			}
		}
	}

	virtual const char* getClassName() const { return "Emitter"; }
};

Emitter* useEbus();
