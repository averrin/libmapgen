#include <string>

using namespace std;

extern "C" {
	__declspec(dllexport) void getRegion(char*, int);
	__declspec(dllexport) int createMap(int);
}
