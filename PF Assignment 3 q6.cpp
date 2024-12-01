#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float temperature;
    float rainfall;
    float wind_speed;
} WeatherForecast;

typedef struct {
    char crop_type[50];
    char growth_stage[50];
    float expected_yield;
    WeatherForecast* weather_data;
} Crop;

typedef struct {
    char equipment_name[50];
    float fuel_level;
    int operational_status;
} Equipment;

typedef struct {
    float soil_ph;
    float nutrient_level;
    int pest_activity;
} Sensor;

typedef struct {
    float gps_latitude;
    float gps_longitude;
    float soil_moisture;
    float soil_health_metric;
    Crop* crops;
    Equipment* equipment;
    Sensor* sensors;
    int num_crops;
    int num_equipment;
    int num_sensors;
} Field;

WeatherForecast* create_weather_data() {
    WeatherForecast* weather = (WeatherForecast*)malloc(sizeof(WeatherForecast));
    if (!weather) {
        printf("Memory allocation failed for WeatherForecast.\n");
        exit(1);
    }

    printf("Enter weather data (temperature, rainfall, wind speed): ");
    scanf("%f %f %f", &weather->temperature, &weather->rainfall, &weather->wind_speed);
    return weather;
}

Crop* create_crops(int num_crops) {
    Crop* crops = (Crop*)malloc(num_crops * sizeof(Crop));
    if (!crops) {
        printf("Memory allocation failed for Crops.\n");
        exit(1);
    }

    for (int i = 0; i < num_crops; i++) {
        printf("\nEnter details for crop %d:\n", i + 1);
        printf("Crop type: ");
        scanf(" %[^\n]", crops[i].crop_type);
        printf("Growth stage: ");
        scanf(" %[^\n]", crops[i].growth_stage);
        printf("Expected yield: ");
        scanf("%f", &crops[i].expected_yield);

        printf("Enter weather data for crop %d:\n", i + 1);
        crops[i].weather_data = create_weather_data();
    }
    return crops;
}

Equipment* create_equipment(int num_equipment) {
    Equipment* equipment = (Equipment*)malloc(num_equipment * sizeof(Equipment));
    if (!equipment) {
        printf("Memory allocation failed for Equipment.\n");
        exit(1);
    }

    for (int i = 0; i < num_equipment; i++) {
        printf("\nEnter details for equipment %d:\n", i + 1);
        printf("Equipment name: ");
        scanf(" %[^\n]", equipment[i].equipment_name);
        printf("Fuel level: ");
        scanf("%f", &equipment[i].fuel_level);
        printf("Operational status (1 for active, 0 for inactive): ");
        scanf("%d", &equipment[i].operational_status);
    }
    return equipment;
}

Sensor* create_sensors(int num_sensors) {
    Sensor* sensors = (Sensor*)malloc(num_sensors * sizeof(Sensor));
    if (!sensors) {
        printf("Memory allocation failed for Sensors.\n");
        exit(1);
    }

    for (int i = 0; i < num_sensors; i++) {
        printf("\nEnter details for sensor %d:\n", i + 1);
        printf("Soil pH: ");
        scanf("%f", &sensors[i].soil_ph);
        printf("Nutrient level: ");
        scanf("%f", &sensors[i].nutrient_level);
        printf("Pest activity: ");
        scanf("%d", &sensors[i].pest_activity);
    }
    return sensors;
}

Field* create_field() {
    Field* field = (Field*)malloc(sizeof(Field));
    if (!field) {
        printf("Memory allocation failed for Field.\n");
        exit(1);
    }

    printf("\nEnter field details:\n");
    printf("GPS latitude: ");
    scanf("%f", &field->gps_latitude);
    printf("GPS longitude: ");
    scanf("%f", &field->gps_longitude);
    printf("Soil moisture: ");
    scanf("%f", &field->soil_moisture);
    printf("Soil health metric: ");
    scanf("%f", &field->soil_health_metric);

    printf("Number of crops: ");
    scanf("%d", &field->num_crops);
    field->crops = create_crops(field->num_crops);

    printf("Number of equipment: ");
    scanf("%d", &field->num_equipment);
    field->equipment = create_equipment(field->num_equipment);

    printf("Number of sensors: ");
    scanf("%d", &field->num_sensors);
    field->sensors = create_sensors(field->num_sensors);

    return field;
}

void display_field_info(const Field* field) {
    printf("\n--- Field Information ---\n");
    printf("GPS Coordinates: (%.4f, %.4f)\n", field->gps_latitude, field->gps_longitude);
    printf("Soil Moisture: %.2f\n", field->soil_moisture);
    printf("Soil Health Metric: %.2f\n", field->soil_health_metric);

    printf("\nCrops:\n");
    for (int i = 0; i < field->num_crops; i++) {
        printf("  Crop %d: %s\n", i + 1, field->crops[i].crop_type);
        printf("    Growth Stage: %s\n", field->crops[i].growth_stage);
        printf("    Expected Yield: %.2f\n", field->crops[i].expected_yield);
        printf("    Weather: Temp: %.2f, Rainfall: %.2f, Wind: %.2f\n",
            field->crops[i].weather_data->temperature,
            field->crops[i].weather_data->rainfall,
            field->crops[i].weather_data->wind_speed);
    }

    printf("\nEquipment:\n");
    for (int i = 0; i < field->num_equipment; i++) {
        printf("  Equipment %d: %s\n", i + 1, field->equipment[i].equipment_name);
        printf("    Fuel Level: %.2f\n", field->equipment[i].fuel_level);
        printf("    Operational Status: %s\n", field->equipment[i].operational_status ? "Active" : "Inactive");
    }

    printf("\nSensors:\n");
    for (int i = 0; i < field->num_sensors; i++) {
        printf("  Sensor %d: pH: %.2f, Nutrient Level: %.2f, Pest Activity: %d\n",
            i + 1, field->sensors[i].soil_ph, field->sensors[i].nutrient_level, field->sensors[i].pest_activity);
    }
    printf("--------------------------\n");
}

void free_field(Field* field) {
    for (int i = 0; i < field->num_crops; i++) {
        free(field->crops[i].weather_data);
    }
    free(field->crops);
    free(field->equipment);
    free(field->sensors);
    free(field);
}

int main() {
    printf("Welcome to the Agritech System for Precision Farming\n");

    Field* field = create_field(); 
    display_field_info(field);    

    free_field(field);            
    return 0;
}
