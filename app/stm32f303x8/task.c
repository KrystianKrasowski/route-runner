#include "task.h"
#include <adapters.h>
#include <mq.h>
#include <sysclock.h>

void
task_handle_manual_control(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) == MQ_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t commands    = adapters_control_map(raw_command);

        // TODO: Handle failures
        (void)linebot_handle_manual_control(linebot, commands);
    }
}

void
task_handle_route_tracking(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_COORDS, &message) == MQ_SUCCESS)
    {
        linebot_coords_t coords;
        uint8_t         *raw_coords = message.payload.coords;

        // TODO: Handle failures
        (void)adapters_coords_map(raw_coords, &coords);
        (void)linebot_handle_route_tracking(linebot, coords);
        (void)linebot_coords_release(coords);
    }
}

void
task_handle_immediate_stop(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) == MQ_SUCCESS)
    {
        // TODO: Handle failures
        (void)linebot_stop(linebot);
    }
}