#ifndef _LINEBOT_RESULT_H
#define _LINEBOT_RESULT_H

/**
 * @brief The result returned by api use cases
 *
 */
typedef enum
{
    LINEBOT_OK,
    LINEBOT_ERR_POOL_EXCEEDED,
    LINEBOT_ERR_NULL_POINTER,
} linebot_result_t;

#endif