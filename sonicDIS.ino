#include <LiquidCrystal.h>// 包含lcd头文件
const int TrigPin = 6; //定义超声波发生器的引脚为6
const int EchoPin = 7; //定义超声波接收引脚为7
const int LaserPin = 8;//定义激光发生器引脚为8
float distance; //定义浮点型的距离变量
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//初始化lcd相关引脚
void setup() {
  pinMode(TrigPin, OUTPUT);  // 设置超声波发生器引脚为输出状态
  pinMode(EchoPin, INPUT); // 设置超声波接收引脚为输入状态
  pinMode(LaserPin, OUTPUT); // 设置激光发生器引脚为输出状态
  lcd.begin(16, 2);// 设置lcd有几行几列，1602LCD为16列2行
} 
void loop() {
  //输出低高低电平触发一个短时脉冲到超声波发生器引脚
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW); 
    // 接收脉冲宽度，通过公式将回波时间转化为距离
  distance = pulseIn(EchoPin, HIGH)/ 58.00;
  //如果得到的距离在正常范围内，lcd显示当前距离，否则提示错误
  if(distance<3000){
    digitalWrite(LaserPin, HIGH); //激光器输出高电平
    lcd.clear();// 清屏
    lcd.setCursor(0, 0);//lcd从第一列第一行开始
    lcd.print("Distance:");//第一行显示“距离：”
    lcd.setCursor(0, 1);//lcd从第二列第一行开始
    lcd.print(distance);//第二行显示“距离值”
    lcd.print("cm");//“距离值”后加上单位
    delay(1000);//延时一秒
    digitalWrite(LaserPin, LOW);  //激光器输出低电平
   }
   //正常范围外报错
  else {
    digitalWrite(LaserPin, HIGH);  //激光器输出高电平
    lcd.clear();// 清屏
    lcd.setCursor(0, 0);//lcd从第一列第一行开始
    lcd.print("ERROR:");//第一行显示“错误：”
    lcd.setCursor(0, 1);//lcd从第二列第一行开始
    lcd.print("aim your target!");//第二行显示“瞄准被测物”
    delay(1000);//延时一秒
    digitalWrite(LaserPin, LOW); //激光器输出低电平
  }
}
