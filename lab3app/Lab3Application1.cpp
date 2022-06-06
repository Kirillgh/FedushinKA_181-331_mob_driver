#include <stdio.h>
#include <string.h>
#include <tchar.h>



//1. специфичные заголовки дл яиспользования анклава
#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Lab3AnklFedushin_u.h"
#define ENCLAVE_FILE _T("Lab3AnklFedushin.signed.dll")




#define BUF_LEN 100


int main()
{
    char buffer[BUF_LEN] = { 0 };

    //2. Активация анклава
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_SUCCESS;
    sgx_launch_token_t token = { 0 };
    int updated = 0;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("App: erore\n", ret);
        return -1;
    }




    while (true) {
        printf("Input index to rertrfifijij -1: \t");
        int idx = -1;
        scanf_s("%d", &idx);
        if (idx < 0) {
            return 0;
        }
        foo(eid, buffer, BUF_LEN, idx);
        printf("%s\n================\n\n", buffer);
    }


    //3. Выгрузить анклав
    if (SGX_SUCCESS != sgx_destroy_enclave(eid))
        return -1;
    return 0;

}


