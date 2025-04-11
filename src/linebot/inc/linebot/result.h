#ifndef _LINEBOT_RESULT_H
#define _LINEBOT_RESULT_H

/**
 * @brief The result returned by api use cases
 *
 */
typedef enum
{
    LINEBOT_OK,
    LINEBOT_ERROR_OBJECT_POOL,
} linebot_result_t;

#endif