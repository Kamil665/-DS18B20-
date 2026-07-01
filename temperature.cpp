#include <OneWire.h>
#include <DallasTemperature.h>

// Пины
const int ONE_WIRE_BUS = 2;    // Пин для DS18B20
const int relayPin = 3;        // Пин для реле

// Создаём объекты
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temperature = 0.0;

void setup() {
  Serial.begin(9600);
  sensors.begin();                    // Инициализация датчика DS18B20
  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);        // Реле выключено при старте
  
  Serial.println("=== Температурный контроллер запущен ===");
}

void loop() {
  sensors.requestTemperatures();              // Запрос температуры
  temperature = sensors.getTempCByIndex(0);   // Читаем температуру с первого датчика
  
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > 30.0) {
    digitalWrite(relayPin, HIGH);   // Включаем реле
    Serial.println("→ Реле ВКЛЮЧЕНО (температура > 30°C)");
  } 
  else {
    digitalWrite(relayPin, LOW);    // Выключаем реле
    Serial.println("→ Реле ВЫКЛЮЧЕНО");
  }

  delay(1000);  // Обновление каждую секунду
}
