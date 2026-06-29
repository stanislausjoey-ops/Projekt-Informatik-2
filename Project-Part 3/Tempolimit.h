/*
 * Tempolimit.h
 *
 *  Created on: Dec 1, 2025
 *      Author: Joey
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_
#include <limits>

enum Tempolimit{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = std::numeric_limits<int>::max()
};



#endif /* TEMPOLIMIT_H_ */
