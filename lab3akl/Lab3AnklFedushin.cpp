#include "Lab3AnklFedushin_t.h"
#include "sgx_trts.h"
#include <string.h>

const char table[6][22] = {
	"111111111111111111111",
	"222222222222222222222",
	"333333333333333333333",
	"444444444444444444444",
	"555555555555555555555"
};

void foo(char* buf, size_t len, size_t idx)
{
	if (idx < 5) {
		const char* data_ptr = data_ptr = table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr + 1));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}