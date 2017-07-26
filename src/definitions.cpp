#include "definitions.hh"

bool operator==(RGBA x, RGBA y) { 
	return x.r == y.r && x.g == y.g && x.b == y.b && x.a == y.a; 
}