#include <linebot/api.h>
#include <sysclock.h>
#include <tasks.h>

int
main(void)
{
    sysclock_init();
    tasks_init();
    linebot_init();

    linebot_coords_t coords;
    linebot_new_coords(0, 0, 0, 0, 0, 0, &coords);

    linebot_t linebot;
    linebot_new(LINEBOT_MODE_MANUAL, coords, 20, &linebot);

    while (1)
    {
        tasks_run(linebot);
    }
}