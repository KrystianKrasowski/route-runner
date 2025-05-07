#ifndef _DEVICE_QTRHD06A_MOCK_H
#define _DEVICE_QTRHD06A_MOCK_H

void
device_qtrhd06a_mock_init(void);

void
device_qtrhd06a_mock_deinit(void);

void
device_qtrhd06a_mock_set_values(device_qtrhd06a_t const h_self,
                                uint8_t const           values[]);

void
device_qtrhd06a_mock_set_ready(device_qtrhd06a_t const h_self,
                               bool const              b_ready);

#endif
