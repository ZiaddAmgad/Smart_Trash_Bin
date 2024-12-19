#include "Ultrasonic.h"
#include <math.h>

void ultrasonic_init() {
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, false);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

uint64_t ultrasonic_get_pulse_duration() {
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);
    
    uint32_t timeout = 0;
    while(!gpio_get(ECHO_PIN) && timeout < 30000) {
        timeout++;
        sleep_us(1);
    }
    
    if(timeout >= 30000) return 0;
    
    uint64_t width = 0;
    timeout = 0;
    
    while(gpio_get(ECHO_PIN) && timeout < 30000) {
        width++;
        sleep_us(1);
        timeout++;
    }
    
    return (timeout >= 30000) ? 0 : width;
}

float ultrasonic_measure_distance() {
    gpio_put(TRIG_PIN, false);
    sleep_us(2);

    gpio_put(TRIG_PIN, true);
    sleep_us(10);
    gpio_put(TRIG_PIN, false);

    uint32_t start_time = 0;
    uint32_t end_time = 0;
    
    while (!gpio_get(ECHO_PIN)) {
        start_time = time_us_32();
        if (start_time > TIMEOUT_US) return -1.0;
    }

    while (gpio_get(ECHO_PIN)) {
        end_time = time_us_32();
        if (end_time - start_time > TIMEOUT_US) return -1.0;
    }

    float distance_cm = ((end_time - start_time) * 0.0343) / 2.0;

    return (distance_cm > 0 && distance_cm < MAX_DISTANCE_CM) ? distance_cm : -1.0;
}

void ultrasonic_interpret_readings(float distance) {
    if (distance < 0) {
        //printf("ERROR CONDITIONS:\n");
        //printf("- No echo received\n");
        //printf("- Object too far\n");
        //printf("- Sensor malfunction\n");
    } else if (distance < 2) {
        //printf("VERY CLOSE RANGE: Extremely near object\n");
    } else if (distance < 10) {
        //printf("CLOSE PROXIMITY: Object within 10cm\n");
    } else if (distance < 50) {
        //printf("MEDIUM RANGE: Object at %.2f cm\n", distance);
    } else if (distance < 200) {
        //printf("FAR RANGE: Distant object at %.2f cm\n", distance);
    } else {
        //printf("MAXIMUM RANGE: Clear path\n");
    }
}

float ultrasonic_advanced_measurement() {
    float distances[5] = {0};
    float total_distance = 0;
    
    for (int i = 0; i < 5; i++) {
        distances[i] = ultrasonic_measure_distance();
        total_distance += distances[i];
        sleep_ms(10);
    }
    
    float average_distance = total_distance / 5;
    
    float variance = 0;
    for (int i = 0; i < 5; i++) {
        variance += pow(distances[i] - average_distance, 2);
    }
    variance /= 5;
    float standard_deviation = sqrt(variance);
    
    //printf("MEASUREMENT DETAILS:\n");
    //printf("- Average Distance: %.2f cm\n", average_distance);
    //printf("- Measurement Variance: %.2f\n", standard_deviation);
    
    return average_distance;
}