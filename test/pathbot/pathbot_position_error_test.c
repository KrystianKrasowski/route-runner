#include "fixtures.h"
#include <pathbot/api.h>
#include <pathbot/store.h>
#include <stdint.h>
#include <unity.h>
#include <unity_config.h>
#include <utils/stack.h>

static pathbot_store_t *p_store;

void
setUp(void)
{
    pathbot_store_init(NULL);
    p_store = pathbot_store_get();
}

void
tearDown(void)
{
}

void
should_compute_position_error(pathbot_coords_t coords, int8_t expexted_error)
{
    // given
    p_store->mode = PATHBOT_MODE_FOLLOWING;

    // when
    (void)pathbot_handle_coords(&coords);
    int8_t actual_error = stack_peek_or(&p_store->past_errors, -128);

    // then
    TEST_ASSERT_EQUAL(expexted_error, actual_error);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 0, 0, 0, 0, 0),
                   -100);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 10, 0, 0, 0, 0),
                   -94);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 20, 0, 0, 0, 0),
                   -90);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 30, 0, 0, 0, 0),
                   -86);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 40, 0, 0, 0, 0),
                   -82);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 50, 0, 0, 0, 0),
                   -80);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 60, 0, 0, 0, 0),
                   -77);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 70, 0, 0, 0, 0),
                   -75);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 80, 0, 0, 0, 0),
                   -73);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 90, 0, 0, 0, 0),
                   -71);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(100, 100, 0, 0, 0, 0),
                   -70);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(90, 100, 10, 0, 0, 0),
                   -66);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(80, 100, 20, 0, 0, 0),
                   -62);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(70, 100, 30, 0, 0, 0),
                   -58);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(60, 100, 40, 0, 0, 0),
                   -54);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(50, 100, 50, 0, 0, 0),
                   -50);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(40, 100, 60, 0, 0, 0),
                   -46);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(30, 100, 70, 0, 0, 0),
                   -42);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(20, 100, 80, 0, 0, 0),
                   -38);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(10, 100, 90, 0, 0, 0),
                   -34);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 100, 100, 0, 0, 0),
                   -30);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 90, 100, 10, 0, 0),
                   -27);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 80, 100, 20, 0, 0),
                   -24);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 70, 100, 30, 0, 0),
                   -21);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 60, 100, 40, 0, 0),
                   -18);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 50, 100, 50, 0, 0),
                   -15);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 40, 100, 60, 0, 0),
                   -12);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 30, 100, 70, 0, 0),
                   -9);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 20, 100, 80, 0, 0),
                   -6);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 10, 100, 90, 0, 0),
                   -3);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 100, 100, 0, 0),
                   0);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 90, 100, 10, 0),
                   3);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 80, 100, 20, 0),
                   6);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 70, 100, 30, 0),
                   9);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 60, 100, 40, 0),
                   12);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 50, 100, 50, 0),
                   15);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 40, 100, 60, 0),
                   18);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 30, 100, 70, 0),
                   21);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 20, 100, 80, 0),
                   24);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 10, 100, 90, 0),
                   27);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 100, 100, 0),
                   30);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 90, 100, 10),
                   34);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 80, 100, 20),
                   38);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 70, 100, 30),
                   42);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 60, 100, 40),
                   46);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 50, 100, 50),
                   50);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 40, 100, 60),
                   54);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 30, 100, 70),
                   58);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 20, 100, 80),
                   62);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 10, 100, 90),
                   66);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 100, 100),
                   70);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 90, 100),
                   71);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 80, 100),
                   73);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 70, 100),
                   75);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 60, 100),
                   77);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 50, 100),
                   80);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 40, 100),
                   82);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 30, 100),
                   86);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 20, 100),
                   90);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 10, 100),
                   94);

    RUN_PARAM_TEST(should_compute_position_error,
                   fixtures_coords6_of(0, 0, 0, 0, 0, 100),
                   100);

    return UNITY_END();
}
