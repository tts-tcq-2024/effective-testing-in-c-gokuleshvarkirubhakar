#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

#define TEST_ENVIRONMENT

#ifdef TEST_ENVIRONMENT
// use stub in test environment
#define networkAlertCall    networkAlertStub
#else 
#define networkAlertCall    networkAlert
#endif

// Actual production code
int networkAlert(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    //........
    return 200;
}

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if (celcius > 100.0f) {
        return 500;
    }
    return 200;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertCall(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

int main() {
    alertFailureCount = 0;
    alertInCelcius(400.5);
    assert(alertFailureCount == 1);
    alertInCelcius(303.6);
    assert(alertFailureCount == 2);
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
