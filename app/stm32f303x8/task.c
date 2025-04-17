#include "task.h"
#include <adapters.h>
#include <mq.h>
#include <sysclock.h>

void
task_handle_manual_control(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) >= 0)
    {
        uint16_t commands = adapters_control_parse(message.payload);

        // TODO: Handle failures
        (void)linebot_handle_manual_control(linebot, commands);
    }
}

void
task_handle_route_tracking(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_COORDS, &message) >= 0)
    {
        linebot_coords_t coords;

        // TODO: Handle failures
        (void)adapters_coords_parse(message.payload, &coords);
        (void)linebot_handle_route_tracking(linebot, coords);
        (void)linebot_coords_release(coords);
    }
}

void
task_handle_immediate_stop(linebot_t const linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) >= 0)
    {
        // TODO: Handle failures
        (void)linebot_handle_immediate_stop(linebot);
    }
}