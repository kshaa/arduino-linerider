// Silly drive function
// power  [0; 100]
// offset [-100; 100]
//    -100 is left
//    +100 is right
void drive(int power, int offset) {
  int offset

  // Approximate work voltages
  int minWorkVoltage = 200;
  int maxWorkVoltage = 255;

  // Steering
  int leftDrive;
  int rightReduction;
  if (offset < 0) {
    leftDrive = 100 - abs(offset);
    rightDrive = 100;
  } else if (offset > 0) {
    leftDrive = 100;
    rightDrive = 100 - abs(offset);
  } else {
    leftDrive = 100;
    rightDrive = 100;
  }
  
  int leftPercent = power
  int leftDrive   = map(offset, 0, 100, minWorkVoltage, maxWorkVoltage);
  int rightDrive  = map(offset, 0, 100, minWorkVoltage, maxWorkVoltage);

  analogWrite(drivePin1, leftDrive);
  analogWrite(drivePin2, rightDrive);
}