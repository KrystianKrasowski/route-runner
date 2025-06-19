#include <mappers/qtrhd06a_coords.h>
#include <pathbot/domain.h>
#include <unity.h>

#define COORDS_SIZE 6

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_normalize_sensor_values(void)
{
    // given
    uint8_t raw_coords[COORDS_SIZE] = {20, 18, 110, 105, 15, 21};

    // when
    pathbot_coords_t coords = {
        .weights = PATHBOT_COORDS6_WEIGHTS,
        .length  = COORDS_SIZE,
    };

    mapper_qtrhd06a_coords_read(raw_coords, COORDS_SIZE, &coords);

    // then
    uint8_t expected[COORDS_SIZE] = {0, 0, 90, 85, 0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, coords.coords, COORDS_SIZE);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_normalize_sensor_values);

    return UNITY_END();
}
