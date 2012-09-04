#include "chi-global.h"

#include <QtCore/QThread>

#include "QtSystem.h"

class I : public QThread {

public:

	static void sleep(unsigned long secs) {
		QThread::sleep(secs);
	}

	static void msleep(unsigned long msecs) {
		QThread::msleep(msecs);
	}

	static void usleep(unsigned long usecs) {
		QThread::usleep(usecs);
	}

};

namespace chi {

Factory<QtSystem> *QtSystem::factory = new Factory<QtSystem>;

void QtSystem::sleep(int ms) {
	I::msleep(ms);
}

}
