/**
 * @brief Linebot available commands
 * 
 */

#ifndef _LINEBOT_COMMAND_H
#define _LINEBOT_COMMAND_H

/**
 * @brief Linebot available commands
 * 
 * The commands are usually passed as uint16_t value which can be bitwise tested
 * using these enumeration constants
 * 
 */
typedef enum
{
    LINEBOT_COMMAND_NONE     = 0,
    LINEBOT_COMMAND_FORWARD  = 1,
    LINEBOT_COMMAND_BACKWARD = 2,
    LINEBOT_COMMAND_LEFT     = 4,
    LINEBOT_COMMAND_RIGHT    = 8,
    LINEBOT_COMMAND_BREAK    = 16,
    LINEBOT_COMMAND_FOLLOW   = 32,
} linebot_command_t;

#endif