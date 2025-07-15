#pragma once

namespace linebot
{

class motion_port;

struct coordinates;

struct commands;

class motion_api
{
public:

    static motion_api&
    of(motion_port& port);

    void
    apply(commands remote_control);

    void
    apply(coordinates line_position);

private:

    motion_port& port_;

    motion_api(motion_port& port)
        : port_{port}
    {
    }
};

} // namespace linebot::api

