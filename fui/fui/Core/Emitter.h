#pragma once

#include "Predef.h"
#include "Event.h"

class Emitter;

class Listener : public GcObj {
public:
	virtual void onListenerEvent(Event* event) {}
};

class Emitter : public Listener {
public:
	Ref<GcList<Emitter>> listeners{new GcList<Emitter>(), this};
	Ref<Emitter> listener{nullptr, this};
	Ref<Closure<void(Event*)>> cbOnEvent{nullptr, this};

	void addListenerOnce(Emitter* l) {
		listeners->push_once(l);
	}
	void addListener(Emitter* l) {
		listeners->push(l);
	}
	void removeListener(Emitter* l) {
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

		Ref<GcList<Emitter>> tmps{new GcList<Emitter>()};
		tmps->push_all(listeners);

		for (int i = 0; i < tmps->size(); i++) {
			Emitter* l = tmps->get(i);
			if (l) {
				l->onListenerEvent(event);
				if (event->isStopPropagation == 2) return;
			}
		}
	}

	virtual const char* getClassName() const { return "Emitter"; }
};

Emitter* useEbus();
