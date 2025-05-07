#ifndef _ADAPTER_COORDS_QTRHD06A_H
#define _ADAPTER_COORDS_QTRHD06A_H

#include <devices/qtrhd06a.h>
#include <linebot/coords.h>

int
adapter_coords_qtrhd06a_read(device_qtrhd06a_t const h_device,
                             linebot_coords_t       *ph_coords);

#endif
