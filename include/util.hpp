#ifndef UTIL_HPP
# define UTIL_HPP

# include <string>

enum FunctionReturn
{
	success = 0,
	failure = -1,
};

/* ========================================================================== */
/*                                  IOMANIP                                   */
/* ========================================================================== */

void		logDebug(const char *msg);
void		logError(const char *msg);
std::string	getFileContent(const char *file);


#endif // UTIL_HPP
