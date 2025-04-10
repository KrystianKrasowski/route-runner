#include <linebot/api.h>
#include <linebot/port.h>
#include <mq.h>
#include <string.h>
#include <tasks.h>

static void
handle_control(linebot_t linebot);

static void
handle_coordinates(linebot_t linebot);

static void
handle_route_guard_timeout(linebot_t linebot);

void
tasks_init(void)
{
    mq_init();
}

void
tasks_run(linebot_t linebot)
{
    handle_control(linebot);
    handle_coordinates(linebot);
    handle_route_guard_timeout(linebot);
}

static void
handle_control(linebot_t linebot)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) == MQ_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t commands    = linebot_port_control_command_map(raw_command);

        linebot_change_mode_by_control(linebot, commands);
        linebot_apply_manual_motion(linebot, commands);
    }
}

static void
handle_coordinates(linebot_t linebot)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_COORDS, &message) == MQ_SUCCESS)
    {
        uint8_t         *raw_coords = message.payload.coords;
        linebot_coords_t coords     = linebot_port_coords_map(raw_coords);

        linebot_change_mode_by_coords(linebot, coords);
        linebot_apply_tracking_motion(linebot, coords);
        linebot_free_coords(coords);
    }
}

static void
handle_route_guard_timeout(linebot_t linebot)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) == MQ_SUCCESS)
    {
        linebot_stop(linebot);
    }
}