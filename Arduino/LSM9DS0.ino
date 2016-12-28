// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM9DSO
// This code is designed to work with the LSM9DS0_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM9DS0_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// LSM9DSO Gyro I2C address is 6A(106)
#define Addr_Gyro 0x6A
// LSM9DSO Accl I2C address is 1E(30)
#define Addr_Accl 0x1E

void setup() 
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr_Gyro);
  // Select control register 1
  Wire.write(0x20);
  // Data rate = 95Hz, X, Y, Z-Axis enabled, power on  
  Wire.write(0x0F);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr_Gyro);
  // Select control register 4
  Wire.write(0x23);
  // Full-scale 2000 dps, continuous update
  Wire.write(0x30);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr_Accl);
  // Select control register 1
  Wire.write(0x20);
  // Acceleration data rate = 100Hz, X, Y, Z-Axis enabled, power on
  Wire.write(0x67);
  // Stop I2C Transmission on the device
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr_Accl);
  // Select control register 2
  Wire.write(0x21);
  // Full scale selection +/- 16g
  Wire.write(0x20);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr_Accl);
  // Select control register 5
  Wire.write(0x24);
  // Magnetic high resolution, output data rate = 50Hz
  Wire.write(0x70);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr_Accl);
  // Select control register 6
  Wire.write(0x25);
  // Magnetic full-scale +/- 12 gauss
  Wire.write(0x60);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr_Accl);
  // Select control register 7
  Wire.write(0x26);
  // Normal mode, magnetic continuous conversion mode
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[6];
    
  for(int i = 0; i < 6; i++)
  {
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Gyro);
    // Select data register
    Wire.write((40+i));
    // Stop I2C Transmission
    Wire.endTransmission();

    // Request 1 byte of data
    Wire.requestFrom(Addr_Gyro, 1);
 
    // Read 6 bytes of data
    // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
    if(Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
   }

    // Convert the data
    int xGyro = ((data[1] * 256) + data[0]);
    int yGyro = ((data[3] * 256) + data[2]);
    int zGyro = ((data[5] * 256) + data[4]);

    for(int i = 0; i < 6; i++)
    {
      // Start I2C Transmission
      Wire.beginTransmission(Addr_Accl);
      // Select data register
      Wire.write((40+i));
      // Stop I2C Transmission
      Wire.endTransmission();

      // Request 1 byte of data
      Wire.requestFrom(Addr_Accl,1);

      // Read 6 bytes of data
      // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb
      // zAccl lsb, zAccl msb
      if(Wire.available() == 1)
      {
        data[i] = Wire.read();
      }
    }
    
    // Convert the data
    int xAccl = ((data[1] * 256) + data[0]);
    int yAccl = ((data[3] * 256) + data[2]);
    int zAccl = ((data[5] * 256) + data[4]);
    
    for(int i = 0; i < 6; i++)
    {
      // Start I2C Transmission
      Wire.beginTransmission(Addr_Accl);
      // Select data register
      Wire.write((8 + i));
      // Stop I2C Transmission
      Wire.endTransmission();

      // Request 1 byte of data
      Wire.requestFrom(Addr_Accl, 1);

      // Read 6 bytes of data
      // xMag lsb, xMag msb, yMag lsb, yMag msb
      // zMag lsb, zMag msb
      if(Wire.available() == 1)
      {
        data[i] = Wire.read();
      }
    }

    // Convert the data
    int xMag = ((data[1] * 256) + data[0]);
    int yMag = ((data[3] * 256) + data[2]);
    int zMag = ((data[5] * 256) + data[4]);

    
    // Output data to serial monitor
    Serial.print("X-Axis of rotation : ");
    Serial.println(xGyro);
    Serial.print("Y-Axis of rotation : ");
    Serial.println(yGyro);
    Serial.print("Z-Axis of rotation : ");
    Serial.println(zGyro);
    Serial.print("Acceleration in X-Axis : ");
    Serial.println(xAccl);
    Serial.print("Acceleration in Y-Axis : ");
    Serial.println(yAccl);
    Serial.print("Acceleration in Z-Axis : ");
    Serial.println(zAccl);
    Serial.print("Magnetic field in X-Axis : ");
    Serial.println(xMag);
    Serial.print("Magnetic field in Y-Axis : ");
    Serial.println(yMag);
    Serial.print("Magnetic filed in Z-Axis : ");
    Serial.println(zMag);
    delay(1000);
}
