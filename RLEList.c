#include <stdlib.h>
#include <stdio.h>
#include "RLEList.h"

struct RLEList_t{
    char ascii;
    int sequence_count;
    struct RLEList_t * link;
};

void RLEListDestroy(RLEList list)
{
    RLEList advance_ptr = list, delete_ptr = list;
    while(advance_ptr != NULL)
    {
        advance_ptr = advance_ptr->link;
        free(delete_ptr);
        delete_ptr = advance_ptr;
    }
}

int RLEListSize(RLEList list)
{
    int count = 0;
    RLEList ptr = list;
    while(ptr)
    {
        count += ptr->sequence_count;
        ptr = ptr->link;
    }
    return count;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if (RLEListSize(list) - 1 < index)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    int max_index = -1;
    RLEList ptr = list;
    while(ptr)
    {
        max_index+= ptr->sequence_count;
        if(max_index>=index)
        {
            *result = RLE_LIST_SUCCESS;
            return ptr->ascii;
        }
        ptr++;
    }
    *result = RLE_LIST_ERROR;
    return 0;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char* ascii_string = malloc(3*RLEListSize(list) + 1);
    if(ascii_string==NULL)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    RLEList ptr = list;
    int index = 0;
    while(ptr)
    {
        ascii_string[index++] = ptr->ascii;
        ascii_string[index++] = ptr->sequence_count;
        ascii_string[index] = '\n';
        ptr++;
    }
    *result=RLE_LIST_SUCCESS;
    return ascii_string;
}
