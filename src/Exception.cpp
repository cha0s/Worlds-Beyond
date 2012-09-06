#include "wb-global.h"

#include "Exception.h"

namespace chi {

Exception::Exception(const std::string& problem)
	: std::exception()
	, m_problem(problem)
{
}

Exception::Exception(const Exception& exception)
	: std::exception()
{
	m_problem = exception.m_problem;
}

Exception::~Exception() throw() {
}

const char* Exception::what() const throw() {
	return m_problem.c_str();
}

}

