#include "pico/stdlib.h"
#include "servomotor.h"
#include "Ultrasonic.h"
#include "IRSensor.h"
#include "led.h"
#include "notification.h"  // Add the notification header

// WiFi credentials - replace with your actual values


absolute_time_t no_object_timer;
bool waiting_for_close = false;
absolute_time_t ultrasonic_cut_timer;
bool ultrasonic_was_cut = false;
bool notification_sent = false;  // Track if notification has been sent

int main() {
    stdio_init_all();

    servo_init();
    ultrasonic_init();
    ir_sensor_init();
    led_init();

    // Initialize WiFi and notification system
    if (!notification_init("XXXXXXXX", "********")) { // Use your own WiFi SSID and password
        printf("Failed to initialize notification system\n");
        // Continue anyway, as the core functionality should still work
    }

    while (true) {
        // Service the notification system
        notification_service();
        
        uint64_t duration = ultrasonic_get_pulse_duration();
        bool object_detected = ir_object_detected();
        
        // Servo control with delayed close
        if (object_detected) {
            led_green_toggle(true);
            servo_set_angle(270);
            waiting_for_close = false;
        } else {
            if (!waiting_for_close) {
                no_object_timer = make_timeout_time_ms(2000);
                waiting_for_close = true;
            }
            
            if (waiting_for_close && time_reached(no_object_timer)) {
                led_green_toggle(false);
                servo_set_angle(-80);
                waiting_for_close = false;
            }
        }
        
        // Ultrasonic sensor cut detection with notification
        float distance = duration * 0.01715;
        ultrasonic_interpret_readings(distance);
        
        if (distance > 0 && distance < 10) {
            if (!ultrasonic_was_cut) {
                ultrasonic_cut_timer = make_timeout_time_ms(5000);
                ultrasonic_was_cut = true;
            }
            
            if (ultrasonic_was_cut && time_reached(ultrasonic_cut_timer)) {
                led_red_toggle(true);
                
                // Send notification if we haven't already
                if (!notification_sent) {
                    printf("Bin full detected - sending notification\n");
                    send_bin_full_notification();
                    notification_sent = true;
                }
            }
        } else {
            led_red_toggle(false);
            // Reset notification state when bin is no longer full
            if (distance >= 10) {
                notification_sent = false;
                ultrasonic_was_cut = false;
            }
        }

        sleep_ms(50);  // Small delay to prevent tight looping
    }

    return 0;
}
