#ifndef WB_EXCEPTION_H
#define WB_EXCEPTION_H

#include "wb-global.h"

#include <exception>
#include <string>

namespace chi {

/**
 * @addtogroup Exceptions
 * @{
 */

class Exception : public std::exception {

public:

	Exception(const std::string& problem);
	Exception(const Exception& exception);
	~Exception() throw();

	const char* what() const throw();

private:

	std::string m_problem;

};

/**
 * @}
 */

}

#endif // WB_EXCEPTION_H
